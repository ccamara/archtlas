/*
 * We are overriding a large part of the JS defined in leaflet (leaflet.drupal.js).
 * Not nice, but we can't do otherwise without refactoring code in Leaflet.
 */

(function ($) {

  Drupal.behaviors.leaflet = { // overrides same behavior in leaflet/leaflet.drupal.js
    attach: function(context, settings) {

      $(settings.leaflet).each(function () {
        // bail if the map already exists
        var container = L.DomUtil.get(this.mapId);
        if (container._leaflet) {
          return false;
        }

        // load a settings object with all of our map and markercluster settings
        var settings = {};
        for (var setting in this.map.settings) {
          settings[setting] = this.map.settings[setting];
        }

        // instantiate our new map
        var lMap = new L.Map(this.mapId, settings);

        // add map layers
        var layers = {}, overlays = {};
        var i = 0;
        for (var key in this.map.layers) {
          var layer = this.map.layers[key];
          var map_layer = Drupal.leaflet.create_layer(layer, key);

          layers[key] = map_layer;

          // add the layer to the map
          if (i >= 0) {
            lMap.addLayer(map_layer);
          }
          i++;
        }

        // @RdB create a marker cluster layer if leaflet.markercluster.js is included
        var cluster_layer = null;
        if (typeof L.MarkerClusterGroup != 'undefined') {
          // Note: only applicable settings will be used, remainder are ignored
          cluster_layer = new L.MarkerClusterGroup(settings);
          lMap.addLayer(cluster_layer);
        }

        // add features
        for (i = 0; i < this.features.length; i++) {
          var feature = this.features[i];
          var lFeature;

          // dealing with a layer group
          if (feature.group) {
            var lGroup = new L.LayerGroup();
            for (var groupKey in feature.features) {
              var groupFeature = feature.features[groupKey];
              lFeature = leaflet_create_feature(groupFeature);
              if (groupFeature.popup) {
                lFeature.bindPopup(groupFeature.popup);
              }
              lGroup.addLayer(lFeature);
            }

            // add the group to the layer switcher
            overlays[feature.label] = lGroup;

            lMap.addLayer(lGroup);
          }
          else {
            lFeature = leaflet_create_feature(feature);
            // @RdB add to cluster layer if one is defined, else to map
            if (cluster_layer) {
              cluster_layer.addLayer(lFeature);
            }
            else {
              lMap.addLayer(lFeature);
            }
            if (feature.popup) {
              lFeature.bindPopup(feature.popup, {autoPanPadding: L.point(25,25)});
            }
          }
        }

        // add layer switcher
        if (this.map.settings.layerControl) {
          lMap.addControl(new L.Control.Layers(layers, overlays));
        }

        // either center the map or set to bounds
        if (this.map.center) {
          lMap.setView(new L.LatLng(this.map.center.lat, this.map.center.lon), this.map.settings.zoom);
        }
        else {
          Drupal.leaflet.fitbounds(lMap);
        }

        // add attribution
        if (this.map.settings.attributionControl && this.map.attribution) {
          lMap.attributionControl.setPrefix(this.map.attribution.prefix);
          lMap.attributionControl.addAttribution(this.map.attribution.text);
        }

        // @pvhee: these events should somehow be triggered from within Drupal, or better we allow
        // for easy JS overrides

        // markers.on('clusterclick', function (a) {
        //   a.layer.spiderfy();
        // });
        //
        // markers.on('clustermouseover', function (a) {
        //   a.layer.spiderfy();
        // });
        //
        // markers.on('mouseover', function (a) {
        //   a.layer.openPopup();
        // });

        // add the leaflet map to our settings object to make it accessible
        this.lMap = lMap;
        // Destroy features so that an AJAX reload does not get parts of the old set.
        // Required when the View has "Use AJAX" set to Yes.
        this.features = null;
      });

      function leaflet_create_feature(feature) {
        var lFeature;
        switch (feature.type) {
          case 'point':
            lFeature = Drupal.leaflet.create_point(feature);
            break;
          case 'linestring':
            lFeature = Drupal.leaflet.create_linestring(feature);
            break;
          case 'polygon':
            lFeature = Drupal.leaflet.create_polygon(feature);
            break;
          case 'multipolygon':
          case 'multipolyline':
            lFeature = Drupal.leaflet.create_multipoly(feature);
            break;
          case 'json':
            lFeature = Drupal.leaflet.create_json(feature.json)
            break;
        }

        // assign our given unique ID, useful for associating nodes
        if (feature.leaflet_id) {
          lFeature._leaflet_id = feature.leaflet_id;
        }

        var options = {};
        if (feature.options) {
          for (var option in feature.options) {
            options[option] = feature.options[option];
          }
          lFeature.setStyle(options);
        }
        return lFeature;
      }

    }
  }

})(jQuery);
