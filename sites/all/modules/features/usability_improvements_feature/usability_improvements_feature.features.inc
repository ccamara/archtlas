<?php
/**
 * @file
 * usability_improvements_feature.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function usability_improvements_feature_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
