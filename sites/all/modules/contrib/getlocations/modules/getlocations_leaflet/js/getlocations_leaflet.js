
/**
 * @file getlocations_leaflet.js
 * @author Bob Hutchinson http://drupal.org/user/52366
 * @copyright GNU GPL
 *
 * Javascript functions for getlocations_leaflet module for Drupal 7
 * this is for leaflet maps http://leafletjs.com/
 */

var getlocations_leaflet_map = [];
var getlocations_leaflet_markers = [];
var getlocations_leaflet_settings = [];
var getlocations_leaflet_overlays = [];
var getlocations_leaflet_layerscontrol = [];
var getlocations_leaflet_data = [];

(function ($) {
  Drupal.behaviors.getlocations_leaflet = {
    attach: function (context, settings) {

      // functions
      var getlocations_leaflet_dd_to_dms_lat = function(coord) {
        return getlocations_leaflet_dd_to_dms_do(coord, 'lat');
      };

      var getlocations_leaflet_dd_to_dms_lng = function(coord) {
        return getlocations_leaflet_dd_to_dms_do(coord, 'lng');
      };

      var getlocations_leaflet_dd_to_dms_do = function(coord, latlon) {
        if (latlon == 'lat') {
          coord = getlocations_leaflet_normalize_lat(coord);
          direction = (coord < 0) ? 'S' : 'N';
        }
        else {
          coord = getlocations_leaflet_normalize_lng(coord);
          direction = (coord < 0) ? 'W' : 'E';
        }
        coord = Math.abs(coord);
        degrees = Math.floor(coord);
        coord = (coord - degrees) * 60;
        minutes = Math.floor(coord);
        coord = (coord - minutes) * 60;
        seconds = Math.round(coord, 6);
        output = degrees + "&deg;&nbsp;" + minutes + "&#39;&nbsp;" + seconds + "&#34;&nbsp;" + direction;
        return output;
      };

      var getlocations_leaflet_dd_lat = function(coord) {
        coord = getlocations_leaflet_normalize_lat(coord);
        return coord.toFixed(6);
      };

      var getlocations_leaflet_dd_lng = function(coord) {
        coord = getlocations_leaflet_normalize_lng(coord);
        return coord.toFixed(6);
      };

      // normalize functions
      var getlocations_leaflet_normalize_lat = function(lat) {
        lat = parseFloat(lat);
        return Math.max(-90, Math.min(90, lat));
      };

      var getlocations_leaflet_normalize_lng = function(lng) {
        lng = parseFloat(lng);
        mod = lng % 360;
        if (mod == 180) {
          return 180;
        }
        return ((mod < -180) ? (lng + 360) : (mod > 180) ? (lng - 360) : lng);
      };

      function getlocations_leaflet_do_link(m, l) {
        m.on('click', function() {
          window.location = l;
        });
      }

      // work over all class 'getlocations_leaflet_canvas'
      $(".getlocations_leaflet_canvas", context).once('getlocations-leaflet-processed', function(index, element) {
        var elemID = $(element).attr('id');
        var key = elemID.replace(/^getlocations_leaflet_canvas_/, '');
        // is there really a map?
        if ( $("#getlocations_leaflet_canvas_" + key).is('div') ) {
          var map_settings = settings.getlocations_leaflet[key].map_settings;
          var map_opts = settings.getlocations_leaflet[key].map_opts;
          var map_layers = settings.getlocations_leaflet[key].map_layers;

          var icons = getlocations_leaflet_data[key].icons;
          var datanum = getlocations_leaflet_data[key].datanum;
          var latlons = getlocations_leaflet_data[key].latlons;
          var minmaxes = getlocations_leaflet_data[key].minmaxes;

          getlocations_leaflet_markers[key] = {};
          getlocations_leaflet_markers[key].coords = {};
          getlocations_leaflet_markers[key].lids = {};
          getlocations_leaflet_markers[key].cat = {};
          getlocations_leaflet_settings[key] = settings.getlocations_leaflet[key];
          getlocations_leaflet_overlays[key] = {};
          getlocations_leaflet_layerscontrol[key] = {};

          // get the map
          getlocations_leaflet_map[key] = L.map('getlocations_leaflet_canvas_' + key, map_opts);
          // another way
          //var map = L.map($(element).get(0), map_opts);
          //getlocations_leaflet_map[key] = map;

          // layers
          var layers = {};
          // do the default layer first and separately
          var default_layer_name = map_settings.default_layer_name;
          var default_layer_label = map_settings.default_layer_label;
          layers[default_layer_label] = L.tileLayer.provider(default_layer_name).addTo(getlocations_leaflet_map[key]);
          for (var lkey in map_layers) {
            if (lkey != default_layer_name) {
              var layer = map_layers[lkey];
              var map_layer = L.tileLayer.provider(lkey);
              map_layer._leaflet_id = lkey;
              if (layer.options) {
                for (var option in layer.options) {
                  map_layer.options[option] = layer.options[option];
                }
              }
              if (layer.type == 'base') {
                layers[layer.label] = map_layer;
              }
              else if (layer.type == 'overlay') {
                getlocations_leaflet_overlays[key][layer.label] = map_layer;
              }
            }
          }
          if (layers.length) {
            layers.addTo(getlocations_leaflet_map[key]);
          }

          // fullscreen control
          if (map_settings.fullscreen) {
            var fsopts = {};
            if (map_settings.fullscreenposition) {
              fsopts.position = map_settings.fullscreenposition;
            }
            fsopts.title = Drupal.t('Fullscreen');
            getlocations_leaflet_map[key].addControl(L.control.fullscreen(fsopts));
          }

          // pancontrol
          if (map_settings.leaflet_pancontrol) {
            var popts = {};
            if (map_settings.pancontrolposition) {
              popts.position = map_settings.pancontrolposition;
            }
            getlocations_leaflet_map[key].addControl(L.control.pan(popts));
          }

          // zoomslider
          if (map_settings.leaflet_zoomslider) {
            var popts = {};
            if (map_settings.zoomsliderposition) {
              popts.position = map_settings.zoomsliderposition;
            }
            getlocations_leaflet_map[key].addControl(L.control.zoomslider(popts));
          }

          // graticule
          if (map_settings.graticule) {
            var gropts = {};
            gropts.style = {};
            if (map_settings.graticule_color) {
              gropts.style.color = map_settings.graticule_color;
            }
            if (map_settings.graticule_opacity) {
              gropts.style.opacity = map_settings.graticule_opacity;
            }
            if (map_settings.graticule_weight) {
              gropts.style.weight = map_settings.graticule_weight;
            }
            if (map_settings.graticule_interval) {
              gropts.interval = parseInt(map_settings.graticule_interval);
            }
            L.graticule(gropts).addTo(getlocations_leaflet_map[key]);
          }

          // Zoom control
          if (map_settings.zoomControl) {
            var zoomopts = {};
            if (map_settings.zoomcontrolposition) {
              zoomopts.position = map_settings.zoomcontrolposition;
            }
            getlocations_leaflet_map[key].addControl(L.control.zoom(zoomopts));
          }

          // Attribution control
          if (map_settings.attributionControl && map_settings.attributioncontrolposition) {
            var attributionopts = {position: map_settings.attributioncontrolposition};
            var attribcontrol = L.control.attribution(attributionopts);
            getlocations_leaflet_map[key].addControl(attribcontrol);
            //attribcontrol.addAttribution(map_layers.earth.options.attribution);
          }

          // Mouseposition
          if (map_settings.mouseposition) {
            var mopts = {};
            mopts.emptystring = Drupal.t('Unavailable');
            if (map_settings.mouseposition_position) {
              mopts.position = map_settings.mouseposition_position;
            }
            if (map_settings.mouseposition_display_dms) {
              mopts.lngFormatter = getlocations_leaflet_dd_to_dms_lng;
              mopts.latFormatter = getlocations_leaflet_dd_to_dms_lat;
            }
            else {
              mopts.lngFormatter = getlocations_leaflet_dd_lng;
              mopts.latFormatter = getlocations_leaflet_dd_lat;
            }
            getlocations_leaflet_map[key].addControl(L.control.mousePosition(mopts));
          }

          // Scale control
          if (map_settings.scaleControl) {
            var scaleopts = {};
            if (map_settings.scalecontrolposition) {
              scaleopts.position = map_settings.scalecontrolposition;
            }
            if (map_settings.scalecontrolunits) {
              if (map_settings.scalecontrolunits == 'metric') {
                scaleopts.metric = true;
                scaleopts.imperial = false;
              }
              else if (map_settings.scalecontrolunits == 'imperial') {
                scaleopts.metric = false;
                scaleopts.imperial = true;
              }
            }
            getlocations_leaflet_map[key].addControl(L.control.scale(scaleopts));
          }

          // latlons data
          if (datanum > 0) {

            // categories
            var categories = {};
            if (map_settings.category_showhide_buttons) {
              categories = (map_settings.categories ? map_settings.categories : {});
            }

            // markers
            var Markers = [];
            if (map_settings.markercluster) {
              if (map_settings.category_showhide_buttons) {
                for (var c in categories) {
                  Markers[c] = L.markerClusterGroup(map_settings.markerclusteroptions);
                }
              }
              else {
                Markers['loc'] = L.markerClusterGroup(map_settings.markerclusteroptions);
              }
            }
            else {
              if (map_settings.category_showhide_buttons) {
                for (var c in categories) {
                  Markers[c] = L.layerGroup();
                }
              }
              else {
                Markers['loc'] = L.layerGroup();
              }
            }

            // loop over latlons
            for (var i = 0; i < latlons.length; i++) {
              var latlon = latlons[i];
              var lat           = latlon[0];
              var lon           = latlon[1];
              var entity_key    = latlon[2];
              var entity_id     = latlon[3];
              var glid          = latlon[4];
              var title         = latlon[5];
              var markername    = latlon[6];
              var vector        = latlon[7];
              var markeraction  = latlon[8];
              var cat           = latlon[9];
              var vicon = vector.data;
              var marker_type = vector.type;

              // check for duplicates
              var hash = lat + lon;
              if (getlocations_leaflet_markers[key].coords[hash] == null) {
                getlocations_leaflet_markers[key].coords[hash] = 1;
              }
              else {
                // we have a duplicate
                // 10000 constrains the max, 0.0001 constrains the min distance
                var m1 = (Math.random() /10000) + 0.0001;
                // randomise the operator
                var m2 = Math.random();
                if (m2 > 0.5) {
                  lat = parseFloat(lat) + m1;
                }
                else {
                  lat = parseFloat(lat) - m1;
                }
                m1 = (Math.random() /10000) + 0.0001;
                m2 = Math.random();
                if (m2 > 0.5) {
                  lon = parseFloat(lon) + m1;
                }
                else {
                  lon = parseFloat(lon) - m1;
                }
              }

              // make markers
              var latLng = L.latLng(lat, lon);

              var icon = '';
              if (markername) {
                icon = icons[markername];
              }
              if (icon || (vicon && map_settings.awesome)) {
                if (vicon && map_settings.awesome) {
                  // icon only
                  if (marker_type == 'i') {
                    var px = parseInt(vicon.px);
                    var diopts = {className: 'getlocations-leaflet-div-icon', iconSize: [px, px], html: vicon.html};
                    var thisVicon = L.divIcon(diopts);
                  }
                  else {
                    var thisVicon = L.AwesomeMarkers.icon(vicon);
                  }
                  var Marker = L.marker(latLng, {icon: thisVicon});

                }
                else if (icon) {
                  var thisIcon = L.icon({iconUrl: icon.iconUrl});
                  // override applicable marker defaults
                  if (icon.iconSize) {
                    thisIcon.options.iconSize = L.point(parseInt(icon.iconSize.x, 10), parseInt(icon.iconSize.y, 10));
                  }
                  if (icon.iconAnchor) {
                    thisIcon.options.iconAnchor = L.point(parseFloat(icon.iconAnchor.x, 10), parseFloat(icon.iconAnchor.y, 10));
                  }
                  if (icon.popupAnchor) {
                    thisIcon.options.popupAnchor = L.point(parseFloat(icon.popupAnchor.x, 10), parseFloat(icon.popupAnchor.y, 10));
                  }
                  if (icon.shadowUrl !== undefined) {
                    thisIcon.options.shadowUrl = icon.shadowUrl;
                    if (icon.shadowSize) {
                      thisIcon.options.shadowSize = L.point(parseInt(icon.shadowSize.x, 10), parseInt(icon.shadowSize.y, 10));
                    }
                    if (icon.shadowAnchor) {
                      thisIcon.options.shadowAnchor = L.point(parseInt(icon.shadowAnchor.x, 10), parseInt(icon.shadowAnchor.y, 10));
                    }
                  }
                  Marker = L.marker(latLng, {icon: thisIcon});
                }

              }
              else {
                // default leaflet marker
                Marker = L.marker(latLng);
              }

              // tooltip
              if (title) {
                Marker.options.title = title;
              }

              // markeraction
              if (markeraction && markeraction.type && markeraction.data) {
                if (markeraction.type == 'popup') {
                  Marker.bindPopup(markeraction.data);
                }
                else if (markeraction.type == 'link') {
                  getlocations_leaflet_do_link(Marker, markeraction.data);
                }
              }
              else {
                Marker.options.clickable = false;
              }

              // add the marker to the group(s)
              if (map_settings.category_showhide_buttons && cat) {
                for (var c in categories) {
                  if (cat == c) {
                    Markers[c].addLayer(Marker);
                  }
                }
              }
              else {
                Markers['loc'].addLayer(Marker);
              }

              // add marker to getlocations_leaflet_markers
              // still experimental
              getlocations_leaflet_markers[key].lids[glid] = Marker;

            } // end latlons

            // add the markers to the map
            if (map_settings.category_showhide_buttons) {
              for (var c in categories) {
                getlocations_leaflet_map[key].addLayer(Markers[c]);
              }
            }
            else {
              getlocations_leaflet_map[key].addLayer(Markers['loc']);
            }

            // set up overlays
            if (map_settings.category_showhide_buttons) {
              for (var c in categories) {
                getlocations_leaflet_overlays[key][categories[c]] = Markers[c];
              }
            }
            else if (map_settings.layercontrol_mark_ov) {
              getlocations_leaflet_overlays[key][map_settings.layercontrol_mark_ov_label] = Markers['loc'];
            }

          } // end datanum > 0

          // Layer control
          if (map_settings.layerControl) {
            var layeropts = {};
            if (map_settings.layercontrolposition) {
              layeropts.position = map_settings.layercontrolposition;
            }
            if (map_settings.minimap) {
              getlocations_leaflet_layerscontrol[key] = L.control.layers.minimap(layers, getlocations_leaflet_overlays[key], layeropts).addTo(getlocations_leaflet_map[key]);
            }
            else {
              getlocations_leaflet_layerscontrol[key] = L.control.layers(layers, getlocations_leaflet_overlays[key], layeropts).addTo(getlocations_leaflet_map[key]);
            }
          }

          // minmaxes will apply when there are more than one marker on the map
          if (datanum > 1) {
            if (minmaxes) {
              var mmarr = minmaxes.split(',');
              var sw = L.latLng(parseFloat(mmarr[2]), parseFloat(mmarr[3])),
                ne = L.latLng(parseFloat(mmarr[0]), parseFloat(mmarr[1])),
                bounds = L.latLngBounds(sw, ne).pad(0.1);
                getlocations_leaflet_map[key].fitBounds(bounds, {reset: true});
            }
          }

        } // end is there really a map?
      }); // end once
    } // end attach
  }; // end behaviors
})(jQuery);
