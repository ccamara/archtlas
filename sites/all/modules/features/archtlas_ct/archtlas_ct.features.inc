<?php
/**
 * @file
 * archtlas_ct.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function archtlas_ct_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function archtlas_ct_node_info() {
  $items = array(
    'works' => array(
      'name' => t('Works'),
      'base' => 'node_content',
      'description' => t('Portfolio content for architects: Information, pictures, videos... about works and projects'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
