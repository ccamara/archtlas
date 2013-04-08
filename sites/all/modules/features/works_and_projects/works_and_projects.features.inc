<?php
/**
 * @file
 * works_and_projects.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function works_and_projects_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function works_and_projects_views_api() {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function works_and_projects_node_info() {
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
