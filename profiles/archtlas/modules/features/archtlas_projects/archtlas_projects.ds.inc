<?php
/**
 * @file
 * archtlas_projects.ds.inc
 */

/**
 * Implements hook_ds_layout_settings_info().
 */
function archtlas_projects_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|projects|default';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'projects';
  $ds_layout->view_mode = 'default';
  $ds_layout->layout = 'ds_2col_stacked';
  $ds_layout->settings = array(
    'regions' => array(
      'left' => array(
        0 => 'field_projects_images',
        1 => 'body',
      ),
      'right' => array(
        2 => 'field_year',
        3 => 'field_projects_location',
        4 => 'field_projects_typology',
      ),
    ),
    'fields' => array(
      'field_projects_images' => 'left',
      'body' => 'left',
      'field_year' => 'right',
      'field_projects_location' => 'right',
      'field_projects_typology' => 'right',
    ),
    'classes' => array(),
    'wrappers' => array(
      'header' => 'div',
      'left' => 'div',
      'right' => 'div',
      'footer' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
  );
  $export['node|projects|default'] = $ds_layout;

  return $export;
}
