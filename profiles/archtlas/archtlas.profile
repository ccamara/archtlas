<?php
/**
 * @file
 * Enables modules and site configuration for a site installation using archtlas profile.
 */

/**
 * Implements archtlas_init().
 */


/**
 * Implements hook_install_tasks_alter().
 */
function archtlas_install_tasks_alter(&$tasks, $install_state) {
  // set a custom theme for the installation
  global $theme_key;
  $theme_key = 'archtlas_install';
  $install_state['parameters']['profile'] = 'archtlas';
}


/**
 * Implements hook_form_FORM_ID_alter() for install_configure_form().
 *
 * Allows the profile to alter the site configuration form.
 */
function archtlas_form_install_configure_form_alter(&$form, $form_state) {
  // Pre-populate the site name with the server name.
  $form['site_information']['site_name']['#default_value'] = $_SERVER['SERVER_NAME'];
}
