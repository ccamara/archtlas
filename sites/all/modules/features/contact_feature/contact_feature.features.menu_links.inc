<?php
/**
 * @file
 * contact_feature.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function contact_feature_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: main-menu:contact
  $menu_links['main-menu:contact'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'contact',
    'router_path' => 'contact',
    'link_title' => 'Contact',
    'options' => array(
      'attributes' => array(
        'title' => 'Contact us',
      ),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 50,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Contact');


  return $menu_links;
}
