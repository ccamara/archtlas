<?php
/**
 * @file
 * seo_feature.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function seo_feature_user_default_permissions() {
  $permissions = array();

  // Exported permission: administer pathauto.
  $permissions['administer pathauto'] = array(
    'name' => 'administer pathauto',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'pathauto',
  );

  return $permissions;
}
