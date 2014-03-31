<?php
/**
 * @file
 * archtlas_projects.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function archtlas_projects_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "ds" && $api == "ds") {
    return array("version" => "1");
  }
  if ($module == "file_entity" && $api == "file_default_displays") {
    return array("version" => "1");
  }
  if ($module == "flexslider" && $api == "flexslider_default_preset") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function archtlas_projects_node_info() {
  $items = array(
    'projects' => array(
      'name' => t('Projects'),
      'base' => 'node_content',
      'description' => t('Works and projects'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
