<?php

/**
 * @file
 * Profiler Builder API examples and documentation.
 */

/**
 * Implements hook_profiler_builder_modules_list_alter().
 */
function hook_profiler_builder_modules_list_alter(&$modules) {
  // remove the cdn module
  unset($modules['cdn']);
}

/**
 * Implements hook_profiler_builder_ignore_alter().
 */
function hook_profiler_builder_ignore_alter(&$ignore) {
  // ignore the cdn settings
  $ignore[] = 'cdn_settings';
}

/**
 * Implements hook_profiler_builder_variables_alter().
 */
function hook_profiler_builder_variables_alter(&$variables) {
  // variable values to change
  $change = array(
    'cdn_status' => 0,
  );
  // loop through and change only set values
  foreach ($change as $var => $val) {
    if (isset($variables[$var])) {
      $variables[$var] = $val;
    }
  }
}

/**
 * Implements hook_profiler_builder_info_include().
 *  key name needs to be unique
 *  name is a human readable name for this component
 *  callback is a function that will return text to place in the file
 * Items added must be available through the profiler API
 * If they aren't you can still add them but they won't do anything
 */
function hook_profiler_builder_info_include() {
  $includes = array(
    'keyname' => array(
      'name' => t('Variables'),
      'callback' => '_profiler_builder_export_variables',
    ),
    'modules' => array(
      'name' => t('Dependencies'),
      'callback' => '_profiler_builder_export_dependencies',
    ),
  );
  return $includes;
}

/**
 * Implements hook_profiler_builder_info_include_alter().
 */
function hook_profiler_builder_info_include(&$includes) {
  $includes['modules']['callback'] = 'my_new_callback_to_handle_modules';
}

/**
 * Implements hook_profiler_builder_patch_locations().
 */
function hook_profiler_builder_patch_locations() {
  $locations = array(
    'includes',
    'misc',
    'modules',
    'profiles',
  );
  return $locations;
}

/**
 * Implements hook_profiler_builder_patch_locations_alter().
 */
function hook_profiler_builder_patch_locations_alter(&$locations) {
  foreach ($locations as $key => $location) {
    // don't scan profiles directory for patches
    if ($location == 'profiles') {
      unset($locations[$key]);
    }
  }
}