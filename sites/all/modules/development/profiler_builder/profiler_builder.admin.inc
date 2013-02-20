<?php

/**
 * @file
 * Administrative form / function processing to make profile package
 */

/**
 * Implements hook_settings().
 */
function _profiler_builder_settings() {
  drupal_add_js(drupal_get_path('module', 'profiler_builder') . '/js/profiler_builder.js');
  $form = array();
  $form['profile_info'] = array(
    '#description' => t('Details of the installation profile to build'),
    '#collapsed' => FALSE,
    '#type' => 'fieldset',
    '#collapsible' => FALSE,
    '#title' => t('Profile .info file'),
  );
  $form['profile_info']['name'] = array(
    '#title' => t('Name'),
    '#description' => t('Example: Studio Machine') . ' (' . t('Do not begin name with numbers.') . ')',
    '#type' => 'textfield',
    '#attributes' => array('class' => array('profile-name')),
    '#field_suffix' => '<span class="field-suffix"></span>',
    '#required' => TRUE,
    '#default_value' => variable_get('site_name', ''),
  );
  $form['profile_info']['profile_machine_name'] = array(
    '#type' => 'machine_name',
    '#maxlength' => 32,
    '#machine_name' => array(
      'exists' => 'profiler_builder_get_info',
    ),
    '#description' => t('Example: studio_machine') . '<br/>' . t('May only contain lowercase letters, numbers and underscores. <strong>Try to avoid conflicts with the names of existing Drupal projects.</strong>'),
    '#required' => TRUE,
  );
  $form['profile_info']['description'] = array(
    '#title' => t('Description'),
    '#description' => t('Provide a short description of what users should expect when they use this profile.'),
    '#type' => 'textfield',
    '#default_value' => variable_get('site_slogan', ''),
  );
  $form['profile_info']['exclusive'] = array(
    '#title' => t('Exclusive'),
    '#description' => t('Treat this installation profile as exclusive? See the !url for more details about this setting.', array('!url' => l(t('related drupal.org discussion'), 'http://drupal.org/node/1727430'))),
    '#type' => 'checkbox',
    '#default_value' => TRUE,
  );
  // allow for definitions of other things to export
  $profiler_includes = _profiler_builder_get_includes();
  foreach ($profiler_includes as $key => $include) {
    $includes[$key] = $include['name'];
  }
  $form['profile_info']['profiler_includes'] = array(
    '#title' => t('Profiler includes'),
    '#description' => t('Items to include in the creation of the profiler .info file that are supported by the profiler module.'),
    '#type' => 'checkboxes',
    '#options' => $includes,
    '#default_value' => array_keys($includes),
  );
  $form['profile_install'] = array(
    '#description' => t('These operations get performed after all modules have been added'),
    '#collapsed' => FALSE,
    '#type' => 'fieldset',
    '#collapsible' => FALSE,
    '#title' => t('Post install clean up (.install)'),
  );
  $form['profile_install']['create_admin'] = array(
    '#title' => t('Create an admin role'),
    '#description' => t('This creates an administrator role during installation. This is recommended as per the standard install profile but disable it if you are handling roles via Features / Ctools exports.'),
    '#type' => 'checkbox',
    '#default_value' => TRUE,
  );
  $form['profile_install']['standard_profile'] = array(
    '#title' => t('Create defaults like standard profile'),
    '#description' => t('This establishes the Page content type, RDF components, image field and associated taxonomy vocabulary Tags that were present in the "standard" drupal installation profile.'),
    '#type' => 'checkbox',
    '#default_value' => FALSE,
  );
  $form['drush_details'] = array(
    '#description' => t('Details of the drush make file to build'),
    '#collapsed' => FALSE,
    '#type' => 'fieldset',
    '#collapsible' => FALSE,
    '#title' => t('Drush make details'),
  );
  $form['drush_details']['local_dev'] = array(
    '#title' => t('Make file for local development'),
    '#description' => t('Check to build for local development, otherwise it will use the drupal.org distribution packaging format (minor difference).'),
    '#type' => 'checkbox',
    '#default_value' => TRUE,
  );
  // only list libraries capabilities if libraries module exists
  if (module_exists('libraries')) {
    // get all known libraries
    $libraries = libraries_get_libraries();
    // convert path locations to keys only
    foreach ($libraries as $key => $val) {
      $libraries[$key] = $key;
    }
    $form['drush_details']['libraries'] = array(
      '#title' => t('Libraries detected'),
      '#description' => t('Deselect to not include the library in drush make'),
      '#type' => 'checkboxes',
      '#options' => $libraries,
      '#multiple' => TRUE,
      '#default_value' => $libraries,
    );
  }
  $patches = array();
  // find .patch files in install
  $tmp = _profiler_builder_get_patches();
  // convert file array to patch array
  foreach ($tmp as $key => $patch) {
    $patch_project = '';
    $path_ary = explode('/', $key);
    foreach ($path_ary as $path_arg => $val) {
      // look for modules key in path, project name is next
      if (($val == 'modules' || $val == 'themes' || $val == 'libraries') && isset($path_ary[($path_arg+1)]) && $path_ary[($path_arg+1)] != $patch->filename) {
        $patch_project = $path_ary[($path_arg+1)];
      }
    }
    // make sure project was found
    if (empty($patch_project)) {
      // test for possible core patches
      $core_locations = array(
        'includes',
        'misc',
        'modules',
        'scripts',
        'themes',
      );
      // search for core patch in core directories
      foreach ($core_locations as $directory) {
        $patch_found = array();
        $patch_found = file_scan_directory('./' . $directory, '/.*\\' . $patch->filename . '$/');
        // if we found something this is a core patch
        if (!empty($patch_found)) {
          $patch_project = 'drupal core';
        }
      }
      // couldn't calculate accurately, set to key unless root
      if (empty($patch_project)) {
        if ($key == './' . $patch->filename) {
          $patch_project = 'drupal core';
        }
        else {
          $patch_project = $key;
        }
      }
    }
    $patches[$patch->name] = $patch_project . ' - ' . $patch->filename;
  }
  // no patches detected
  if (count($patches) > 0) {
    $form['drush_details']['patches'] = array(
      '#title' => t('Patches detected'),
      '#description' => t('Deselect to not include the patch in drush make'),
      '#type' => 'checkboxes',
      '#options' => $patches,
      '#default_value' => array_keys($patches),
    );
  }

  $form['buttons']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Download profile'),
    '#weight' => 10,
    '#submit' => array('_profiler_builder_settings_form_submit'),
  );
  return $form;
}

/**
 * Helper to remove unchecked values.
 */
function _profiler_builder_unchecked_array(&$ary) {
  foreach ($ary as $key => $val) {
    // remove unchecked items
    if ($val == '0') {
      unset($ary[$key]);
    }
  }
}
/**
 * Form submission handler for profiler_builder_export_form().
 */
function _profiler_builder_settings_form_submit($form, &$form_state) {
  $name = $form_state['values']['name'];
  $machine_name = $form_state['values']['profile_machine_name'];
  $description = $form_state['values']['description'];
  $exclusive = $form_state['values']['exclusive'];
  $profiler_includes = $form_state['values']['profiler_includes'];
  $local_dev = $form_state['values']['local_dev'];
  if (is_array($profiler_includes)) {
    _profiler_builder_unchecked_array($profiler_includes);
  }
  // add libraries if libraries API is installed
  if (isset($form_state['values']['libraries'])) {
    $libraries = $form_state['values']['libraries'];
    _profiler_builder_unchecked_array($libraries);
  }
  else {
    $libraries = array();
  }
  // add patches if any exist
  if (isset($form_state['values']['patches'])) {
    $patches = $form_state['values']['patches'];
    _profiler_builder_unchecked_array($patches);
  }
  else {
    $patches = array();
  }
  if (is_array($patches)) {
    _profiler_builder_unchecked_array($patches);
  }
  // check if we should use standard profile setup routine
  if ($form_state['values']['standard_profile']) {
    $standard_profile_default = _profiler_builder_standard_profile_default();
  }
  else {
    $standard_profile_default = '';
  }
  // check if we should create an admin role
  if ($form_state['values']['create_admin']) {
    $create_admin = _profiler_builder_create_admin();
  }
  else {
    $create_admin = '';
  }
  // values have been set, now do the processing
  _profiler_builder_build_profile($name, $machine_name, $description, $exclusive, $profiler_includes, $local_dev, $standard_profile_default, $create_admin, $libraries, $patches);
}

/**
 * Helper to build a profile
 */
function _profiler_builder_build_profile($name, $machine_name, $description, $exclusive, $profiler_includes, $local_dev, $standard_profile_default, $create_admin, $libraries, $patches) {
  // assemble profiler components
  $features = _profiler_builder_list_features();
  // build initial info file
  $info_file = _profiler_builder_info_file($name, $machine_name, $description, $exclusive);
  // pull in all includes
  $info_includes = _profiler_builder_get_includes();
  // build each part of the info file
  foreach ($info_includes as $key => $include) {
    // only render to the file if checked in the form
    if ($profiler_includes[$key]) {
      $component_name = $include['name'];
      // build include heading
      $info_file .= "; ----------\n";
      $info_file .= "; $component_name\n";
      $info_file .= "; ----------\n";
      // render information based on callback
      $info_file .= call_user_func($include['callback']);
      $info_file .= "\n";
    }
  }
  // drush setting for drupal.org distro or local
  if ($local_dev) {
    $drush_file_name = 'drush.make';
  }
  else {
    $drush_file_name = 'drupal-org.make';
  }
  // build drush file
  $drush_file = _profiler_builder_drush_file($name, $local_dev, $libraries, $patches);
  // build files array
  $files = array(
    $machine_name . '.info' => $info_file,
    $machine_name . '.install' => _profiler_builder_install_file($machine_name, array_keys($features), $standard_profile_default, $create_admin),
    $machine_name . '.profile' => _profiler_builder_profile_file($name, $machine_name),
    $drush_file_name => $drush_file,
  );
  // Generate download file name
  $filename =  $machine_name . '.tar';
  // Clear out output buffer to remove any garbage from tar output.
  if (ob_get_level()) {
    ob_end_clean();
  }
  // set headers for file download on submit, accounting for drush
  if (!function_exists('drush_main')) {
    drupal_add_http_header('Content-type', 'application/x-tar');
    drupal_add_http_header('Content-Disposition', 'attachment; filename="' . $filename . '"');
    drupal_send_headers();
  }
  $output = '';
  // loop through file array and add to package
  foreach ($files as $file_name => $file_contents) {
    // write file to tar package
    $output .= profiler_builder_tar_create("{$machine_name}/{$file_name}", $file_contents);
  }
  // end tar file output
  $output .= pack("a1024", "");
  if (!function_exists('drush_main')) {
    print $output;
    exit;
  }
  else {
    // drush is running, return values to drush to handle
    $drush_args = array(
      'tar' => $output,
      'tar_name' => $filename,
      'source_files' => $files,
    );
    return $drush_args;
  }
}

/**
 * Helper function to create .install file
 */
function _profiler_builder_install_file($machine_name, $features, $standard_profile_default, $create_admin) {
  $output = '<?php
  !function_exists(\'profiler_v2\') ? require_once(\'libraries/profiler/profiler.inc\') : FALSE;
  profiler_v2(\'' . $machine_name . '\');

/**
 * Implements hook_install().
 *
 * Perform actions to set up the site for this profile.
 */
function ' . $machine_name . '_install() {
  // Enable some ' . $machine_name . ' blocks.
  $default_theme = \'' . variable_get('theme_default', 'bartik') . '\';
  $admin_theme = \'' . variable_get('admin_theme', 'seven') . '\';
  // disable all themes
  db_update(\'system\')
    ->fields(array(\'status\' => 0))
    ->condition(\'type\', \'theme\')
    ->execute();
  // enable $default_theme
  db_update(\'system\')
    ->fields(array(\'status\' => 1))
    ->condition(\'type\', \'theme\')
    ->condition(\'name\', $default_theme)
    ->execute();
  // enable $admin_theme
  db_update(\'system\')
    ->fields(array(\'status\' => 1))
    ->condition(\'type\', \'theme\')
    ->condition(\'name\', $admin_theme)
    ->execute();
  variable_set(\'admin_theme\', $admin_theme);
  // activate admin theme when editing a node
  variable_set(\'node_admin_theme\', \'1\');
  $blocks = array(
    array(
      \'module\' => \'system\',
      \'delta\' => \'main\',
      \'theme\' => $default_theme,
      \'status\' => 1,
      \'weight\' => 0,
      \'region\' => \'content\',
      \'pages\' => \'\',
      \'cache\' => -1,
    ),
    array(
      \'module\' => \'user\',
      \'delta\' => \'login\',
      \'theme\' => $default_theme,
      \'status\' => 1,
      \'weight\' => 0,
      \'region\' => \'sidebar_first\',
      \'pages\' => \'\',
      \'cache\' => -1,
    ),
    array(
      \'module\' => \'system\',
      \'delta\' => \'help\',
      \'theme\' => $default_theme,
      \'status\' => 1,
      \'weight\' => -10,
      \'region\' => \'content\',
      \'pages\' => \'\',
      \'cache\' => -1,
    ),
    array(
      \'module\' => \'system\',
      \'delta\' => \'main\',
      \'theme\' => $admin_theme,
      \'status\' => 1,
      \'weight\' => 0,
      \'region\' => \'content\',
      \'pages\' => \'\',
      \'cache\' => -1,
    ),
    array(
      \'module\' => \'system\',
      \'delta\' => \'help\',
      \'theme\' => $admin_theme,
      \'status\' => 1,
      \'weight\' => 0,
      \'region\' => \'help\',
      \'pages\' => \'\',
      \'cache\' => -1,
    ),
  );
  // drop system / user blocks to ensure correct building
  db_delete(\'block\')->condition(\'module\', \'system\')->execute();
  db_delete(\'block\')->condition(\'module\', \'user\')->execute();
  // add in our blocks defined above
  $query = db_insert(\'block\')->fields(array(\'module\', \'delta\', \'theme\', \'status\', \'weight\', \'region\', \'pages\', \'cache\'));
  foreach ($blocks as $block) {
    $query->values($block);
  }
  $query->execute();
  ' . $standard_profile_default;
  // account for features being installed
  if (module_exists('features')) {
    $output .= '
  // revert features to ensure they are all installed
  $features = array(
    \'' . implode("',\n    '", $features) . '\'
  );
  features_revert($features);';
  }
  // account for shortcut module being installed
  if (module_exists('shortcut')) {
    $output .= '
  // From shortcut.install, add shortcuts to the default set on install
  $shortcut_set = shortcut_set_load(SHORTCUT_DEFAULT_SET_NAME);
  $shortcut_set->links = NULL;
  $shortcut_set->links = array(
    array(
      \'link_path\' => \'admin/appearance/settings\',
      \'link_title\' => st(\'Theme\'),
      \'weight\' => -17,
    ),
  );
  shortcut_set_save($shortcut_set);';
  }
  $output .= $create_admin . '
  // Update the menu router information.
  menu_rebuild();
  // ignore any rebuild messages
  node_access_needs_rebuild(FALSE);
  // ignore any other install messages
  drupal_get_messages();
}';
  return $output;
}

/**
 * Helper function to create .info file
 */
function _profiler_builder_info_file($name, $machine_name, $description, $exclusive) {
  $active_core = PROIFLER_BUILDER_ACTIVE_CORE;
  $output = "; Packaging information for $machine_name\n";
  $output .= "name = \"$name\"\n";
  $output .= "description = \"$description\"\n";
  // if exclusive flag set, include it
  if ($exclusive) {
    $output .= "exclusive = \"$exclusive\"\n";
  }
  $output .= "core = \"$active_core.x\"\n";
  return $output;
}

/**
 * Helper function to create .profile file
 */
function _profiler_builder_profile_file($name, $machine_name) {
  // assemble default output
  $output = '<?php
/**
 * Implements hook_form_FORM_ID_alter().
 *
 * Allows the profile to alter the site configuration form.
 */
function system_form_install_configure_form_alter(&$form, $form_state) {
  // Pre-populate the site name with the server name.
  $form[\'site_information\'][\'site_name\'][\'#default_value\'] = \'' . $name . '\';
}
/**
 * Implements hook_form_alter().
 */
function system_form_install_select_profile_form_alter(&$form, $form_state) {
  // select ' . $machine_name . ' install profile by default
  foreach ($form[\'profile\'] as $key => $element) {
    $form[\'profile\'][$key][\'#value\'] = \'' . $machine_name . '\';
  }
}';
  return $output;
}

/**
 * Helper to make .make file.
 */
function _profiler_builder_drush_file($name, $local, $libraries, $patches) {
  $active_core = PROIFLER_BUILDER_ACTIVE_CORE;
  $output = "; $name make file\n";
  $output .= "core = \"$active_core.x\"\n";
  $output .= "api = \"2\"\n";
  // change file based on local development or d.o.
  if ($local) {
    $output .= "; comment this out in to use on drupal.org\n";
    $output .= "projects[drupal][version] = \"$active_core.x\"\n";
  }
  else {
    $output .= "; comment this in to use in local development\n";
    $output .= "; projects[drupal][version] = \"$active_core.x\"\n";
  }
  // add drush project includes
  $system = array();
  $project_data = array();
  // build the array we need
  $result = db_select('system', 's')
  ->fields('s', array('status', 'type', 'name', 'info'))
  ->condition('s.status', 1, '=')
  ->condition('s.type', 'module', '=')
  ->execute();
  foreach ($result as $val) {
    $system[$val->name] = unserialize($val->info);
  }
  // remove install profile as it lists as a module
  if (isset($system[variable_get('install_profile', 'standard')])) {
    unset($system[variable_get('install_profile', 'standard')]);
  }
  // build the make file project data with everything
  foreach ($system as $module => $info) {
    // build projects array to exclude sub-modules
    if (isset($info['project'])) {
      $project_data[$info['package']][$info['project']] = $info['version'];
    }
    else {
      $project_data[$info['package']][$module] = $info['version'];
    }
  }
  // alphabetical order of project data / packages
  ksort($project_data);
  foreach ($project_data as $key => $package) {
    ksort($project_data[$key]);
  }
  // drush make file build via browser
  $output .= "\n; Modules\n";
  $no_version = '';
  foreach ($project_data as $package => $projects) {
    // skip core modules
    if ($package != 'Core') {
      foreach ($projects as $project => $version) {
        // if there's no version, add it to the end
        if (empty($version)) {
          $no_version .= "projects[$project][version] = \"\" ; TODO add version\n";
          $no_version .= "projects[$project][subdir] = \"custom\"\n\n";
        }
        else {
          $version = _profiler_builder_get_version($version);
          $output .= "projects[$project][version] = \"$version\"\n";
          $output .= "projects[$project][subdir] = \"contrib\"\n\n";
        }
      }
    }
  }
  if ($no_version != '') {
    $output .= "; TODO modules without versions\n" . $no_version;
  }
  // add all themes to drush file
  $output .= "\n; Themes\n";
  $result = db_select('system', 's')
  ->fields('s', array('info'))
  ->condition('s.type', 'theme', '=')
  ->orderBy('s.status', 'DESC')
  ->orderBy('s.name')
  ->execute();
  $themes = array();
  // add each theme regardless of active status
  foreach ($result as $theme) {
    $info = unserialize($theme->info);
    // ignore core themes
    if (isset($info['project']) && $info['project'] != 'drupal') {
      // ensures sub-themes don't get included
      $themes[$info['project']] = $info['version'];
    }
  }
  // write themes to file
  foreach ($themes as $project_name => $version) {
    $output .= "; $project_name\n";
    $output .= "projects[$project_name][type] = \"theme\"\n";
    // account for custom themes
    if (empty($version)) {
      $output .= "projects[$project_name][version] = \"\"; TODO add version\n";
      $output .= "projects[$project_name][subdir] = \"custom\"\n";
    }
    else {
      $version = _profiler_builder_get_version($version);
      $output .= "projects[$project_name][version] = \"$version\"\n";
      $output .= "projects[$project_name][subdir] = \"contrib\"\n";
    }
  }
  // add libraries
  $lib_output = '';
  foreach ($libraries as $key => $lib_name) {
    // always use profiler dev
    if ($key == 'profiler') {
      $dl_location = 'http://ftp.drupal.org/files/projects/profiler-7.x-2.x-dev.tar.gz';
    }
    else {
      $dl_location = '';
    }
    $lib_output .= "libraries[$key][directory_name] = \"$key\"\n";
    $lib_output .= "libraries[$key][type] = \"library\"\n";
    $lib_output .= "libraries[$key][destination] = \"libraries\"\n";
    $lib_output .= "libraries[$key][download][type] = \"get\"\n";
    $lib_output .= "libraries[$key][download][url] = \"$dl_location\"";
    // account for empty dl locations
    if (empty($dl_location)) {
      $lib_output .= " ; TODO add download URI";
    }
    $lib_output .= "\n\n";
  }
  // only add if there were libraries detected
  if (!empty($lib_output)) {
    $output .= "\n; Libraries\n" . $lib_output;
  }
  // add patches to end of file
  $patch_output = '';
  // list all patches again
  $tmp = _profiler_builder_get_patches();
  $active_patches = array();
  // convert to simplified checking for allowed patches
  foreach ($tmp as $key => $patch_info) {
    if (isset($patches[$patch_info->name])) {
      $patch_project = '';
      $path_ary = explode('/', $key);
      foreach ($path_ary as $path_arg => $val) {
        // look for modules key in path, project name is next
        if (($val == 'modules' || $val == 'themes' || $val == 'libraries') && isset($path_ary[($path_arg+1)]) && $patch_info->filename != $path_ary[($path_arg+1)]) {
          $patch_project = $path_ary[($path_arg+1)];
        }
      }
      // make sure project was found
      if (empty($patch_project)) {
        // test for possible core patches
        $core_locations = array(
          'includes',
          'misc',
          'modules',
          'scripts',
          'themes',
        );
        // search for core patch in core directories
        foreach ($core_locations as $directory) {
          $patch_found = array();
          $patch_found = file_scan_directory('./' . $directory, '/.*\\' . $patch_info->filename . '$/');
          // if we found something this is a core patch
          if (!empty($patch_found)) {
            $patch_project = 'drupal';
          }
        }
        // couldn't calculate accurately, set to key unless root
        if (empty($patch_project)) {
          if ($key == './' . $patch_info->filename) {
            $patch_project = 'drupal';
          }
          else {
            $patch_project = $key;
          }
        }
      }
      // account for multiple patches by treating as arrays
      $active_patches[$patch_project][] = $patch_info->filename;
    }
  }
  // render active patches to file
  foreach ($active_patches as $key => $patch_ary) {
    foreach ($patch_ary as $patch_path) {
      $errors = array();
      // test if patch lives on d.o.
      $request = drupal_http_request("http://drupal.org/files/$patch_path");
      // patch not on d.o. add error message
      if (isset($request->error)) {
        $errors[] = 'add path to patch';
      }
      else {
        $patch_path = "http://drupal.org/files/$patch_path";
      }
      // check if this key is not a project
      if (strrpos($key, '/')) {
        $errors[] = 'associate patch to a project';
      }
      $patch_output .= "projects[$key][patch][] = \"$patch_path\"";
      // if there were errors, add a message
      if (count($errors) > 0) {
        $patch_output .= ' ; TODO ' . implode(', ', $errors);
      }
      $patch_output .= "\n\n";
    }
  }
  if (!empty($patch_output)) {
    $output .= "\n; Patches\n" . $patch_output;
  }
  return $output;
}

/**
 * Helper to return standard profile default settings.
 */
function _profiler_builder_standard_profile_default() {
  $output = '
  // Insert default pre-defined node types into the database. For a complete
  // list of available node type attributes, refer to the node type API
  // documentation at: http://api.drupal.org/api/HEAD/function/hook_node_info.
  $types = array(
    array(
      \'type\' => \'page\',
      \'name\' => st(\'Page\'),
      \'base\' => \'node_content\',
      \'description\' => st("Use <em>pages</em> for basic page content."),
      \'custom\' => 1,
      \'modified\' => 1,
      \'locked\' => 0,
    ),
  );

  foreach ($types as $type) {
    $type = node_type_set_defaults($type);
    node_type_save($type);
    node_add_body_field($type);
  }

  // Insert default pre-defined RDF mapping into the database.
  $rdf_mappings = array(
    array(
      \'type\' => \'node\',
      \'bundle\' => \'page\',
      \'mapping\' => array(
        \'rdftype\' => array(\'foaf:Document\'),
      ),
    ),
  );
  foreach ($rdf_mappings as $rdf_mapping) {
    rdf_mapping_save($rdf_mapping);
  }

  // Default "Page" to not be promoted and have comments disabled.
  variable_set(\'node_options_page\', array(\'status\'));

  // Don\'t display date and author information for "Page" nodes by default.
  variable_set(\'node_submitted_page\', FALSE);

  // Create a default vocabulary named "Tags", enabled for the \'article\' content type.
  $description = st(\'Use tags to group articles on similar topics into categories.\');
  $help = st(\'Enter a comma-separated list of words to describe your content.\');
  $vocabulary = (object) array(
    \'name\' => st(\'Tags\'),
    \'description\' => $description,
    \'machine_name\' => \'tags\',
    \'help\' => $help,

  );
  taxonomy_vocabulary_save($vocabulary);

  $field = array(
    \'field_name\' => \'field_\' . $vocabulary->machine_name,
    \'type\' => \'taxonomy_term_reference\',
    // Set cardinality to unlimited for tagging.
    \'cardinality\' => FIELD_CARDINALITY_UNLIMITED,
    \'settings\' => array(
      \'allowed_values\' => array(
        array(
          \'vocabulary\' => $vocabulary->machine_name,
          \'parent\' => 0,
        ),
      ),
    ),
  );
  field_create_field($field);

  $instance = array(
    \'field_name\' => \'field_\' . $vocabulary->machine_name,
    \'entity_type\' => \'node\',
    \'label\' => \'Tags\',
    \'bundle\' => \'article\',
    \'description\' => $vocabulary->help,
    \'widget\' => array(
      \'type\' => \'taxonomy_autocomplete\',
      \'weight\' => -4,
    ),
    \'display\' => array(
      \'default\' => array(
        \'type\' => \'taxonomy_term_reference_link\',
        \'weight\' => 10,
      ),
      \'teaser\' => array(
        \'type\' => \'taxonomy_term_reference_link\',
        \'weight\' => 10,
      ),
    ),
  );
  field_create_instance($instance);


  // Create an image field named "Image", enabled for the \'article\' content type.
  // Many of the following values will be defaulted, they\'re included here as an illustrative examples.
  // See http://api.drupal.org/api/function/field_create_field/' . PROIFLER_BUILDER_ACTIVE_CORE . '

  $field = array(
    \'field_name\' => \'field_image\',
    \'type\' => \'image\',
    \'cardinality\' => 1,
    \'locked\' => FALSE,
    \'indexes\' => array(\'fid\' => array(\'fid\')),
    \'settings\' => array(
      \'uri_scheme\' => \'public\',
      \'default_image\' => FALSE,
    ),
    \'storage\' => array(
      \'type\' => \'field_sql_storage\',
      \'settings\' => array(),
    ),
  );
  field_create_field($field);

  // Many of the following values will be defaulted, they\'re included here as an illustrative examples.
  // See http://api.drupal.org/api/function/field_create_instance/' . PROIFLER_BUILDER_ACTIVE_CORE . '
  $instance = array(
    \'field_name\' => \'field_image\',
    \'entity_type\' => \'node\',
    \'label\' => \'Image\',
    \'bundle\' => \'article\',
    \'description\' => st(\'Upload an image to go with this article.\'),
    \'required\' => FALSE,

    \'settings\' => array(
      \'file_directory\' => \'field/image\',
      \'file_extensions\' => \'png gif jpg jpeg\',
      \'max_filesize\' => \'\',
      \'max_resolution\' => \'\',
      \'min_resolution\' => \'\',
      \'alt_field\' => TRUE,
      \'title_field\' => \'\',
    ),

    \'widget\' => array(
      \'type\' => \'image_image\',
      \'settings\' => array(
        \'progress_indicator\' => \'throbber\',
        \'preview_image_style\' => \'thumbnail\',
      ),
      \'weight\' => -1,
    ),

    \'display\' => array(
      \'default\' => array(
        \'label\' => \'hidden\',
        \'type\' => \'image\',
        \'settings\' => array(\'image_style\' => \'large\', \'image_link\' => \'\'),
        \'weight\' => -1,
      ),
      \'teaser\' => array(
        \'label\' => \'hidden\',
        \'type\' => \'image\',
        \'settings\' => array(\'image_style\' => \'medium\', \'image_link\' => \'content\'),
        \'weight\' => -1,
      ),
    ),
  );
  field_create_instance($instance);
  // Create a Home link in the main menu.
  $item = array(
    \'link_title\' => st(\'Home\'),
    \'link_path\' => \'<front>\',
    \'menu_name\' => \'main-menu\',
  );
  menu_link_save($item);';
  return $output;
}

/**
 * Helper function to create an admin in the .install file.
 */
function _profiler_builder_create_admin() {
  $output = '// Create a default role for site administrators, with all available permissions assigned.
  $admin_role = new stdClass();
  $admin_role->name = \'administrator\';
  $admin_role->weight = 10;
  user_role_save($admin_role);
  user_role_grant_permissions($admin_role->rid, array_keys(module_invoke_all(\'permission\')));
  // Set this as the administrator role.
  variable_set(\'user_admin_role\', $admin_role->rid);

  // Assign user 1 the "administrator" role.
  db_insert(\'users_roles\')
    ->fields(array(\'uid\' => 1, \'rid\' => $admin_role->rid))
    ->execute();';
  return $output;
}

/**
 * Helper function to find all patches in setup
 */
function _profiler_builder_get_patches() {
  // find server base path for this drupal instance
  $dir_base = './';
  // find all locations to search
  $search = module_invoke_all('profiler_builder_patch_locations');
  drupal_alter('profiler_builder_patch_locations', $search);
  $files = array();
  $tmp_files = array();
  // look for patches in hook defined directories
  foreach ($search as $directory) {
    $tmp_files = file_scan_directory($dir_base . $directory, '/.*\.patch$/');
    $files = array_merge($tmp_files, $files);
  }
  // look for patches just in document root in-case of core patch
  $tmp_files = file_scan_directory('.', '/.*\.patch$/', array('recurse' => FALSE));
  $files = array_merge($tmp_files, $files);
  return $files;
}