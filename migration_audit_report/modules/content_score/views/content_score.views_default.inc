<?php

/**
 * @file
 * Content score.
 */

/**
 * Implements hook_views_default_views().
 */
function content_score_views_default_views() {

  $view = new view();
  $view->name = 'content_score';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'content_score';
  $view->human_name = 'Content score';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Content score';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer content score';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button'] = TRUE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '100';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'entity_id' => 'entity_id',
    'title' => 'title',
    'entity_type' => 'entity_type',
    'error_type' => 'error_type',
    'total_count' => 'total_count',
    'score' => 'score',
    'edit_content' => 'edit_content',
  );
  $handler->display->display_options['style_options']['default'] = 'score';
  $handler->display->display_options['style_options']['info'] = array(
    'entity_id' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'entity_type' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'error_type' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'total_count' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'score' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'edit_content' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['label'] = 'New Header';
  $handler->display->display_options['header']['area']['empty'] = TRUE;
  $handler->display->display_options['header']['area']['format'] = 'filtered_html';
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'No faulty content found';
  $handler->display->display_options['empty']['area']['format'] = 'filtered_html';
  /* Field: Content score: Entity Id */
  $handler->display->display_options['fields']['entity_id']['id'] = 'entity_id';
  $handler->display->display_options['fields']['entity_id']['table'] = 'content_score';
  $handler->display->display_options['fields']['entity_id']['field'] = 'entity_id';
  $handler->display->display_options['fields']['entity_id']['exclude'] = TRUE;
  /* Field: Content score: Entity Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'content_score';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Title/Label';
  /* Field: Content score: Entity Type */
  $handler->display->display_options['fields']['entity_type']['id'] = 'entity_type';
  $handler->display->display_options['fields']['entity_type']['table'] = 'content_score';
  $handler->display->display_options['fields']['entity_type']['field'] = 'entity_type';
  /* Field: Content score: Tag Type */
  $handler->display->display_options['fields']['error_type']['id'] = 'error_type';
  $handler->display->display_options['fields']['error_type']['table'] = 'content_score';
  $handler->display->display_options['fields']['error_type']['field'] = 'error_type';
  /* Field: Content score: Tag Total Count */
  $handler->display->display_options['fields']['total_count']['id'] = 'total_count';
  $handler->display->display_options['fields']['total_count']['table'] = 'content_score';
  $handler->display->display_options['fields']['total_count']['field'] = 'total_count';
  /* Field: Content score: Content Score */
  $handler->display->display_options['fields']['score']['id'] = 'score';
  $handler->display->display_options['fields']['score']['table'] = 'content_score';
  $handler->display->display_options['fields']['score']['field'] = 'score';
  $handler->display->display_options['fields']['score']['label'] = 'Content Score (*All Tags Included)';
  /* Field: Content score: Edit link */
  $handler->display->display_options['fields']['edit_content']['id'] = 'edit_content';
  $handler->display->display_options['fields']['edit_content']['table'] = 'content_score';
  $handler->display->display_options['fields']['edit_content']['field'] = 'edit_content';
  $handler->display->display_options['fields']['edit_content']['label'] = 'Action';
  $handler->display->display_options['fields']['edit_content']['element_label_colon'] = FALSE;
  /* Sort criterion: Content score: Content Score */
  $handler->display->display_options['sorts']['score']['id'] = 'score';
  $handler->display->display_options['sorts']['score']['table'] = 'content_score';
  $handler->display->display_options['sorts']['score']['field'] = 'score';
  $handler->display->display_options['sorts']['score']['order'] = 'DESC';
  /* Filter criterion: Content score: Entity Title */
  $handler->display->display_options['filters']['title']['id'] = 'title';
  $handler->display->display_options['filters']['title']['table'] = 'content_score';
  $handler->display->display_options['filters']['title']['field'] = 'title';
  $handler->display->display_options['filters']['title']['operator'] = 'contains';
  $handler->display->display_options['filters']['title']['exposed'] = TRUE;
  $handler->display->display_options['filters']['title']['expose']['operator_id'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['label'] = 'Title/Label';
  $handler->display->display_options['filters']['title']['expose']['operator'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['identifier'] = 'title';
  $handler->display->display_options['filters']['title']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  /* Filter criterion: Content score: Entity Type */
  $handler->display->display_options['filters']['entity_type']['id'] = 'entity_type';
  $handler->display->display_options['filters']['entity_type']['table'] = 'content_score';
  $handler->display->display_options['filters']['entity_type']['field'] = 'entity_type';
  $handler->display->display_options['filters']['entity_type']['exposed'] = TRUE;
  $handler->display->display_options['filters']['entity_type']['expose']['operator_id'] = 'entity_type_op';
  $handler->display->display_options['filters']['entity_type']['expose']['label'] = 'Entity Type';
  $handler->display->display_options['filters']['entity_type']['expose']['operator'] = 'entity_type_op';
  $handler->display->display_options['filters']['entity_type']['expose']['identifier'] = 'entity_type';
  $handler->display->display_options['filters']['entity_type']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['entity_type']['group_info']['label'] = 'Entity Type';
  $handler->display->display_options['filters']['entity_type']['group_info']['identifier'] = 'entity_type';
  $handler->display->display_options['filters']['entity_type']['group_info']['group_items'] = array(
    1 => array(
      'title' => 'Node',
      'operator' => '=',
      'value' => 'node',
    ),
    2 => array(
      'title' => 'Block',
      'operator' => '=',
      'value' => 'bean',
    ),
    3 => array(
      'title' => '',
      'operator' => '=',
      'value' => '',
    ),
  );
  /* Filter criterion: Content score: Tag Type */
  $handler->display->display_options['filters']['error_type']['id'] = 'error_type';
  $handler->display->display_options['filters']['error_type']['table'] = 'content_score';
  $handler->display->display_options['filters']['error_type']['field'] = 'error_type';
  $handler->display->display_options['filters']['error_type']['exposed'] = TRUE;
  $handler->display->display_options['filters']['error_type']['expose']['operator_id'] = 'error_type_op';
  $handler->display->display_options['filters']['error_type']['expose']['label'] = 'Tag Type';
  $handler->display->display_options['filters']['error_type']['expose']['operator'] = 'error_type_op';
  $handler->display->display_options['filters']['error_type']['expose']['identifier'] = 'error_type';
  $handler->display->display_options['filters']['error_type']['expose']['autocomplete_field'] = 'error_type';
  $handler->display->display_options['filters']['error_type']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['error_type']['group_info']['label'] = 'Tag Type';
  $handler->display->display_options['filters']['error_type']['group_info']['identifier'] = 'error_type';
  $handler->display->display_options['filters']['error_type']['group_info']['group_items'] = array(
    1 => array(
      'title' => 'Image',
      'operator' => '=',
      'value' => 'img',
    ),
    2 => array(
      'title' => 'Script',
      'operator' => '=',
      'value' => 'script',
    ),
    3 => array(
      'title' => 'Style',
      'operator' => '=',
      'value' => 'style',
    ),
  );

  /* Display: Overview Page */
  $handler = $view->new_display('page', 'Overview Page', 'page_1');
  $handler->display->display_options['path'] = 'admin/content-score';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Content Score';
  $handler->display->display_options['menu']['description'] = 'Listing of content score card';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $handler->display->display_options['tab_options']['type'] = 'normal';
  $handler->display->display_options['tab_options']['title'] = 'Content score';
  $handler->display->display_options['tab_options']['weight'] = '0';

  /* Display: Listing Page */
  $handler = $view->new_display('page', 'Listing Page', 'page');
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content score: Entity Id */
  $handler->display->display_options['fields']['entity_id']['id'] = 'entity_id';
  $handler->display->display_options['fields']['entity_id']['table'] = 'content_score';
  $handler->display->display_options['fields']['entity_id']['field'] = 'entity_id';
  $handler->display->display_options['fields']['entity_id']['exclude'] = TRUE;
  /* Field: Content score: Entity Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'content_score';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Title/Label';
  /* Field: Content score: Entity Type */
  $handler->display->display_options['fields']['entity_type']['id'] = 'entity_type';
  $handler->display->display_options['fields']['entity_type']['table'] = 'content_score';
  $handler->display->display_options['fields']['entity_type']['field'] = 'entity_type';
  /* Field: Content score: Tag Type */
  $handler->display->display_options['fields']['error_type']['id'] = 'error_type';
  $handler->display->display_options['fields']['error_type']['table'] = 'content_score';
  $handler->display->display_options['fields']['error_type']['field'] = 'error_type';
  /* Field: Content score: Tag Total Count */
  $handler->display->display_options['fields']['total_count']['id'] = 'total_count';
  $handler->display->display_options['fields']['total_count']['table'] = 'content_score';
  $handler->display->display_options['fields']['total_count']['field'] = 'total_count';
  /* Field: Content score: Content Score */
  $handler->display->display_options['fields']['score']['id'] = 'score';
  $handler->display->display_options['fields']['score']['table'] = 'content_score';
  $handler->display->display_options['fields']['score']['field'] = 'score';
  $handler->display->display_options['fields']['score']['label'] = 'Content Score (*All Tags Included)';
  /* Field: Content score: Edit link */
  $handler->display->display_options['fields']['edit_content']['id'] = 'edit_content';
  $handler->display->display_options['fields']['edit_content']['table'] = 'content_score';
  $handler->display->display_options['fields']['edit_content']['field'] = 'edit_content';
  $handler->display->display_options['fields']['edit_content']['label'] = 'Action';
  $handler->display->display_options['fields']['edit_content']['element_label_colon'] = FALSE;
  $handler->display->display_options['path'] = 'admin/content-score/listing';
  $handler->display->display_options['menu']['type'] = 'default tab';
  $handler->display->display_options['menu']['title'] = 'Content Score';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $handler->display->display_options['tab_options']['title'] = 'Content score';
  $handler->display->display_options['tab_options']['weight'] = '0';

  $views[$view->name] = $view;
  return $views;
}
