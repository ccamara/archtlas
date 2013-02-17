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
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'leaflet';
  $handler->display->display_options['style_options']['data_source'] = 'field_geocode';
  $handler->display->display_options['style_options']['name_field'] = 'view_node';
  $handler->display->display_options['style_options']['description_field'] = 'field_media_main';
  $handler->display->display_options['style_options']['view_mode'] = 'teaser';
  $handler->display->display_options['style_options']['map'] = 'stamen-toner';
  $handler->display->display_options['style_options']['height'] = '300';
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

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
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
  $handler->display->display_options['fields']['field_media_main']['alter']['alter_text'] = TRUE;
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
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'grid';
  $handler->display->display_options['style_options']['columns'] = '3';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
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
  $handler->display->display_options['attachment_position'] = 'after';

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
  $export['works_and_projects'] = $view;

  return $export;
}
