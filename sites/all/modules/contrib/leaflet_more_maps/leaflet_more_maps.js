(function ($) {

  Drupal.leaflet._create_layer_orig = Drupal.leaflet.create_layer;
  
  Drupal.leaflet.create_layer = function(layer, key) {
    if (layer.type != 'google') {
      return Drupal.leaflet._create_layer_orig(layer, key);
    }
    
    if (layer.options.detectRetina && L.Browser.retina) {
      layer.urlTemplate += '&style=high_dpi&w=512';
      layer.options.tileSize = 512;
    }
    var mapLayer = new L.TileLayer(layer.urlTemplate, layer.options);
    mapLayer._leaflet_id = key;
    return mapLayer;
  };
  
})(jQuery);


