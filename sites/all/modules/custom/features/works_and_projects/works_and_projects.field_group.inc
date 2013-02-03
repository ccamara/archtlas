<?php
/**
 * @file
 * works_and_projects.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function works_and_projects_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_works_details|node|works|form';
  $field_group->group_name = 'group_works_details';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'works';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Work\'s details',
    'weight' => '3',
    'children' => array(
      0 => 'field_works_taxonomy',
      1 => 'field_works_area',
      2 => 'field_works_date',
      3 => 'field_works_budget',
      4 => 'field_client',
      5 => 'field_works_architecture',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_works_details|node|works|form'] = $field_group;

  return $export;
}
