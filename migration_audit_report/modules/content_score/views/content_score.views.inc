<?php

/**
 * @file
 * Content score.
 */

/**
 * Implements hook_views_data().
 */
function content_score_views_data() {
  $data = array();
  $data['content_score']['table']['group'] = t('Content score');
  $data['content_score']['table']['base'] = array(
    'field' => 'cid',
    'title' => t('Content score'),
    'weight' => -10,
  );
  $data['content_score']['title'] = array(
    'title' => t('Entity Title'),
    'help' => t('Provide a title of the content.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  $data['content_score']['entity_id'] = array(
    'title' => t('Entity Id'),
    'help' => t('Provide a ID of the content..'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  $data['content_score']['entity_type'] = array(
    'title' => t('Entity Type'),
    'help' => t('Just a plain text field.'),
    'field' => array(
      'handler' => 'views_handler_field',
      // This is use by the table display plugin.
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  $data['content_score']['error_type'] = array(
    'title' => t('Tag Type'),
    'help' => t('Just a plain text field.'),
    'field' => array(
      'handler' => 'views_handler_field',
      // This is use by the table display plugin.
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  $data['content_score']['total_count'] = array(
    'title' => t('Tag Total Count'),
    'help' => t('Just a plain text field.'),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument',
    ),
  );
  $data['content_score']['score'] = array(
    'title' => t('Content Score'),
    'help' => t('Just a plain text field.'),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument',
    ),
  );
  $data['content_score']['updated'] = array(
    'title' => t('Content score updated'),
    'help' => t('Just a timestamp field.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );
  $data['content_score']['edit_content'] = array(
    'field' => array(
      'title' => t('Edit link'),
      'help' => t('Provide a simple link to edit the content.'),
      'handler' => 'content_score_field_edit_link',
    ),
  );

  return $data;
}
