<?php

/**
 * @file
 * Content score.
 */

/**
 * Implements hook_form().
 */
function content_score_reports_refresh_form($form, &$form_state) {
  $form = array();
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Score Refresh'),
  );
  return $form;
}

/**
 * Submit function of score report refresh.
 */
function content_score_reports_refresh_form_submit($form, &$form_state) {

  $entity = content_score_get_all_entities();

  foreach ($entity as $key => $value) {
    $operations[] = array(
      'content_score_batch_op',
      array(
        $value,
      ),
    );
  }

  $batch = array(
    'operations' => $operations,
    'finished' => 'content_score_batch_finished',
    'file' => drupal_get_path('module', 'content_score') . '/includes/content_score.admin.inc',
  );
  batch_set($batch);
}

/**
 * Batch callback.
 */
function content_score_batch_op($entity, &$context) {
  $entity_load = '';
  if ($entity->entity_type == 'node') {
    $entity_load = node_load($entity->nid);
  }
  elseif ($entity->entity_type == 'bean') {
    $entity_load = bean_load($entity->bid);
  }
  if ($entity_load) {
    $entity_wrapper = entity_metadata_wrapper($entity->entity_type, $entity_load);

    content_score_entity_data_save_details($entity_wrapper, $entity->entity_type);

    $context['results'][] = check_plain($entity_wrapper->label());
    $context['message'] = t('Loading "@title"', array('@title' => $entity_wrapper->label()));
  }
}

/**
 * Batch 'finished' callback.
 */
function content_score_batch_finished($success, $results, $operations) {
  if ($success) {
    drupal_set_message(t('@count results processed.', array(
      '@count' => count($results),
    )));
  }
  else {
    // An error occurred.
    // $operations contains the operations that remained unprocessed.
    $error_operation = reset($operations);
    drupal_set_message(t('An error occurred while processing @operation with arguments : @args', array(
      '@operation' => $error_operation[0],
      '@args' => print_r($error_operation[0], TRUE),
    )), 'error');
  }
}

/**
 * Export page callback.
 */
function content_score_reports_export() {
  // Export functionality.
  $result = db_select('content_score', 'cs')
    ->fields('cs')
    ->orderBy('score', 'desc')
    ->execute();

  $num_of_results = $result->rowCount();

  if ($num_of_results == 0) {
    drupal_set_message(t('There are no records to download.'));
    drupal_goto("admin/content-score");
  }

  $data = array();
  foreach ($result as $row) {
    if ($row->entity_type == 'node') {
      $path = $row->entity_type;
    }
    elseif ($row->entity_type == 'bean') {
      $path = 'block';
    }

    $edit_path = url($path . '/' . $row->entity_id . '/edit', array('absolute' => TRUE));
    $content_score_path = url($path . '/' . $row->entity_id . '/content-score', array('absolute' => TRUE));
    $data[] = array(
      $row->title,
      $row->entity_type,
      $row->error_type,
      $row->total_count,
      $row->score,
      $edit_path,
      $content_score_path,
    );
  }

  $filename = strtotime('now') . '.csv';
  $headers = array(
    'Label',
    'Entity type',
    'Tag Type',
    'Tag Total Count',
    'Score',
    'Edit Path',
    'Scorecard Path',
  );

  // Add HTTP headers for CSV file download.
  drupal_add_http_header('Content-Type', 'text/csv; utf-8');
  drupal_add_http_header('Content-Disposition', 'attachment; filename=' . $filename, TRUE);

  // Allow caching, otherwise IE users can't do over SSL.
  drupal_add_http_header('Cache-Control', 'max-age=300; must-revalidate');

  $f = fopen('php://output', 'w');
  foreach ($data as $key => $row) {
    if (!$key) {
      fputcsv($f, $headers);
    }
    fputcsv($f, $row);
  }
  fclose($f);
  exit();
}

/**
 * Helper function to get all the required entities.
 */
function content_score_get_all_entities() {
  $entity = array();
  $types = content_score_allowed_entities();

  foreach ($types as $type) {
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', $type);
    $result = $query->execute();

    foreach ($result[$type] as $row) {
      $row->entity_type = $type;
      $entity[] = $row;
    }
  }

  return $entity;
}
