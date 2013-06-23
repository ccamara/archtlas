<?php
/**
 * @file
 * works_and_projects.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function works_and_projects_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'works_and_projects';
  $view->description = 'Map displaying works and projects';
  $view->tag = 'map';
  $view->base_table = 'node';
  $view->human_name = 'Works and Projects';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Works and Projects';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['autosubmit'] = TRUE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'grid';
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['hide_empty'] = TRUE;
  $handler->display->display_options['row_options']['default_field_elements'] = FALSE;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['label'] = 'Empty text';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = '<h2>This page has no content to display (yet)!</h2>
Please make sure to <b>create at least one Work or project</b> to be displayed in this fancy page. In order to do so, please <a href="node/add/works">click here</a> or visit <i>"Add content/works"</i> menu.
';
  $handler->display->display_options['empty']['area']['format'] = 'full_html';
  /* Field: Content: Link */
  $handler->display->display_options['fields']['view_node']['id'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['view_node']['field'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['label'] = '';
  $handler->display->display_options['fields']['view_node']['exclude'] = TRUE;
  $handler->display->display_options['fields']['view_node']['element_label_colon'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Media Main */
  $handler->display->display_options['fields']['field_media_main']['id'] = 'field_media_main';
  $handler->display->display_options['fields']['field_media_main']['table'] = 'field_data_field_media_main';
  $handler->display->display_options['fields']['field_media_main']['field'] = 'field_media_main';
  $handler->display->display_options['fields']['field_media_main']['label'] = '';
  $handler->display->display_options['fields']['field_media_main']['alter']['text'] = '<b>[title]</b>
[field_media_main]
';
  $handler->display->display_options['fields']['field_media_main']['alter']['path'] = '[view_node]';
  $handler->display->display_options['fields']['field_media_main']['alter']['absolute'] = TRUE;
  $handler->display->display_options['fields']['field_media_main']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_media_main']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_media_main']['type'] = 'file_rendered';
  $handler->display->display_options['fields']['field_media_main']['settings'] = array(
    'file_view_mode' => 'media_preview',
  );
  /* Field: Content: Geocode */
  $handler->display->display_options['fields']['field_geocode']['id'] = 'field_geocode';
  $handler->display->display_options['fields']['field_geocode']['table'] = 'field_data_field_geocode';
  $handler->display->display_options['fields']['field_geocode']['field'] = 'field_geocode';
  $handler->display->display_options['fields']['field_geocode']['label'] = '';
  $handler->display->display_options['fields']['field_geocode']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_geocode']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_geocode']['click_sort_column'] = 'wkt';
  $handler->display->display_options['fields']['field_geocode']['type'] = 'geofield_latlon';
  $handler->display->display_options['fields']['field_geocode']['settings'] = array(
    'data' => 'full',
    'format' => 'decimal_degrees',
    'labels' => 1,
  );
  /* Sort criterion: Content: Sticky */
  $handler->display->display_options['sorts']['sticky']['id'] = 'sticky';
  $handler->display->display_options['sorts']['sticky']['table'] = 'node';
  $handler->display->display_options['sorts']['sticky']['field'] = 'sticky';
  $handler->display->display_options['sorts']['sticky']['order'] = 'DESC';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'works' => 'works',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Search: Search Terms */
  $handler->display->display_options['filters']['keys']['id'] = 'keys';
  $handler->display->display_options['filters']['keys']['table'] = 'search_index';
  $handler->display->display_options['filters']['keys']['field'] = 'keys';
  $handler->display->display_options['filters']['keys']['group'] = 1;
  $handler->display->display_options['filters']['keys']['exposed'] = TRUE;
  $handler->display->display_options['filters']['keys']['expose']['operator_id'] = 'keys_op';
  $handler->display->display_options['filters']['keys']['expose']['operator'] = 'keys_op';
  $handler->display->display_options['filters']['keys']['expose']['identifier'] = 'keys';
  $handler->display->display_options['filters']['keys']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  /* Filter criterion: Content: Typology (field_works_taxonomy) */
  $handler->display->display_options['filters']['field_works_taxonomy_tid']['id'] = 'field_works_taxonomy_tid';
  $handler->display->display_options['filters']['field_works_taxonomy_tid']['table'] = 'field_data_field_works_taxonomy';
  $handler->display->display_options['filters']['field_works_taxonomy_tid']['field'] = 'field_works_taxonomy_tid';
  $handler->display->display_options['filters']['field_works_taxonomy_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_works_taxonomy_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_works_taxonomy_tid']['expose']['operator_id'] = 'field_works_taxonomy_tid_op';
  $handler->display->display_options['filters']['field_works_taxonomy_tid']['expose']['label'] = 'Typology';
  $handler->display->display_options['filters']['field_works_taxonomy_tid']['expose']['operator'] = 'field_works_taxonomy_tid_op';
  $handler->display->display_options['filters']['field_works_taxonomy_tid']['expose']['identifier'] = 'field_works_taxonomy_tid';
  $handler->display->display_options['filters']['field_works_taxonomy_tid']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_works_taxonomy_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  $handler->display->display_options['filters']['field_works_taxonomy_tid']['group_info']['label'] = 'Typology (field_works_taxonomy)';
  $handler->display->display_options['filters']['field_works_taxonomy_tid']['group_info']['identifier'] = 'field_works_taxonomy_tid';
  $handler->display->display_options['filters']['field_works_taxonomy_tid']['group_info']['remember'] = FALSE;
  $handler->display->display_options['filters']['field_works_taxonomy_tid']['group_info']['group_items'] = array(
    1 => array(),
    2 => array(),
    3 => array(),
  );
  $handler->display->display_options['filters']['field_works_taxonomy_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_works_taxonomy_tid']['vocabulary'] = 'typology';
  $handler->display->display_options['filters']['field_works_taxonomy_tid']['hierarchy'] = 1;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['exposed_block'] = TRUE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_wrapper_type'] = 'h4';
  /* Field: Content: Media Main */
  $handler->display->display_options['fields']['field_media_main']['id'] = 'field_media_main';
  $handler->display->display_options['fields']['field_media_main']['table'] = 'field_data_field_media_main';
  $handler->display->display_options['fields']['field_media_main']['field'] = 'field_media_main';
  $handler->display->display_options['fields']['field_media_main']['label'] = '';
  $handler->display->display_options['fields']['field_media_main']['alter']['text'] = '<b>[title]</b>
[field_media_main]
';
  $handler->display->display_options['fields']['field_media_main']['alter']['path'] = '[view_node]';
  $handler->display->display_options['fields']['field_media_main']['alter']['absolute'] = TRUE;
  $handler->display->display_options['fields']['field_media_main']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_media_main']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_media_main']['type'] = 'file_rendered';
  $handler->display->display_options['fields']['field_media_main']['settings'] = array(
    'file_view_mode' => 'media_preview',
  );
  /* Field: Content: Geocode */
  $handler->display->display_options['fields']['field_geocode']['id'] = 'field_geocode';
  $handler->display->display_options['fields']['field_geocode']['table'] = 'field_data_field_geocode';
  $handler->display->display_options['fields']['field_geocode']['field'] = 'field_geocode';
  $handler->display->display_options['fields']['field_geocode']['label'] = '';
  $handler->display->display_options['fields']['field_geocode']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_geocode']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_geocode']['click_sort_column'] = 'wkt';
  $handler->display->display_options['fields']['field_geocode']['type'] = 'geofield_latlon';
  $handler->display->display_options['fields']['field_geocode']['settings'] = array(
    'data' => 'full',
    'format' => 'decimal_degrees',
    'labels' => 1,
  );
  $handler->display->display_options['path'] = 'works-and-projects';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Works and Projects';
  $handler->display->display_options['menu']['description'] = 'A map displaying all the works and projects';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'main-menu';
  $handler->display->display_options['menu']['context'] = 0;

  /* Display: Attachment */
  $handler = $view->new_display('attachment', 'Attachment', 'attachment_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'leaflet';
  $handler->display->display_options['style_options']['data_source'] = 'field_geocode';
  $handler->display->display_options['style_options']['name_field'] = 'title';
  $handler->display->display_options['style_options']['description_field'] = 'title';
  $handler->display->display_options['style_options']['map'] = 'stamen-toner';
  $handler->display->display_options['style_options']['icon'] = array(
    'iconUrl' => '',
    'shadowUrl' => '',
    'iconSize' => array(
      'x' => '',
      'y' => '',
    ),
    'iconAnchor' => array(
      'x' => '',
      'y' => '',
    ),
    'shadowAnchor' => array(
      'x' => '',
      'y' => '',
    ),
    'popupAnchor' => array(
      'x' => '',
      'y' => '',
    ),
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['empty'] = FALSE;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Content: Sticky */
  $handler->display->display_options['sorts']['sticky']['id'] = 'sticky';
  $handler->display->display_options['sorts']['sticky']['table'] = 'node';
  $handler->display->display_options['sorts']['sticky']['field'] = 'sticky';
  $handler->display->display_options['sorts']['sticky']['order'] = 'DESC';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );
  $handler->display->display_options['inherit_exposed_filters'] = TRUE;

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Location';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'leaflet';
  $handler->display->display_options['style_options']['data_source'] = 'field_geocode';
  $handler->display->display_options['style_options']['name_field'] = 'view_node';
  $handler->display->display_options['style_options']['description_field'] = 'field_media_main';
  $handler->display->display_options['style_options']['view_mode'] = 'teaser';
  $handler->display->display_options['style_options']['map'] = 'stamen-toner';
  $handler->display->display_options['style_options']['height'] = '300';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['empty'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'grid';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'field_works_taxonomy',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_wrapper_type'] = 'h3';
  /* Field: Content: Media Main */
  $handler->display->display_options['fields']['field_media_main']['id'] = 'field_media_main';
  $handler->display->display_options['fields']['field_media_main']['table'] = 'field_data_field_media_main';
  $handler->display->display_options['fields']['field_media_main']['field'] = 'field_media_main';
  $handler->display->display_options['fields']['field_media_main']['label'] = '';
  $handler->display->display_options['fields']['field_media_main']['alter']['text'] = '<b>[title]</b>
[field_media_main]
';
  $handler->display->display_options['fields']['field_media_main']['alter']['path'] = '[view_node]';
  $handler->display->display_options['fields']['field_media_main']['alter']['absolute'] = TRUE;
  $handler->display->display_options['fields']['field_media_main']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_media_main']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_media_main']['type'] = 'file_rendered';
  $handler->display->display_options['fields']['field_media_main']['settings'] = array(
    'file_view_mode' => 'media_preview',
  );
  /* Field: Content: Geocode */
  $handler->display->display_options['fields']['field_geocode']['id'] = 'field_geocode';
  $handler->display->display_options['fields']['field_geocode']['table'] = 'field_data_field_geocode';
  $handler->display->display_options['fields']['field_geocode']['field'] = 'field_geocode';
  $handler->display->display_options['fields']['field_geocode']['label'] = '';
  $handler->display->display_options['fields']['field_geocode']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_geocode']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_geocode']['click_sort_column'] = 'wkt';
  $handler->display->display_options['fields']['field_geocode']['type'] = 'geofield_latlon';
  $handler->display->display_options['fields']['field_geocode']['settings'] = array(
    'data' => 'full',
    'format' => 'decimal_degrees',
    'labels' => 1,
  );
  /* Field: Content: Typology */
  $handler->display->display_options['fields']['field_works_taxonomy']['id'] = 'field_works_taxonomy';
  $handler->display->display_options['fields']['field_works_taxonomy']['table'] = 'field_data_field_works_taxonomy';
  $handler->display->display_options['fields']['field_works_taxonomy']['field'] = 'field_works_taxonomy';
  $handler->display->display_options['fields']['field_works_taxonomy']['label'] = '';
  $handler->display->display_options['fields']['field_works_taxonomy']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_works_taxonomy']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_works_taxonomy']['group_rows'] = FALSE;
  $handler->display->display_options['fields']['field_works_taxonomy']['delta_offset'] = '0';
  $handler->display->display_options['path'] = 'typologies';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Typologies';
  $handler->display->display_options['menu']['description'] = 'A map displaying all the works and projects';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'main-menu';
  $handler->display->display_options['menu']['context'] = 0;
  $translatables['works_and_projects'] = array(
    t('Master'),
    t('Works and Projects'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('Empty text'),
    t('<h2>This page has no content to display (yet)!</h2>
Please make sure to <b>create at least one Work or project</b> to be displayed in this fancy page. In order to do so, please <a href="node/add/works">click here</a> or visit <i>"Add content/works"</i> menu.
'),
    t('<b>[title]</b>
[field_media_main]
'),
    t('Typology'),
    t('Typology (field_works_taxonomy)'),
    t('Page'),
    t('Attachment'),
    t('Block'),
    t('Location'),
    t('All'),
  );
  $export['works_and_projects'] = $view;

  $view = new view();
  $view->name = 'works_and_projects_last_items';
  $view->description = 'List of latest works and projects';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Works and Projects: Last  items';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Works and Projects: Last  items';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'mini';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Media Main */
  $handler->display->display_options['fields']['field_media_main']['id'] = 'field_media_main';
  $handler->display->display_options['fields']['field_media_main']['table'] = 'field_data_field_media_main';
  $handler->display->display_options['fields']['field_media_main']['field'] = 'field_media_main';
  $handler->display->display_options['fields']['field_media_main']['label'] = '';
  $handler->display->display_options['fields']['field_media_main']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_media_main']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_media_main']['type'] = 'file_rendered';
  $handler->display->display_options['fields']['field_media_main']['settings'] = array(
    'file_view_mode' => 'media_preview',
  );
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'works' => 'works',
  );

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $translatables['works_and_projects_last_items'] = array(
    t('Master'),
    t('Works and Projects: Last  items'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('Block'),
  );
  $export['works_and_projects_last_items'] = $view;

  return $export;
}
