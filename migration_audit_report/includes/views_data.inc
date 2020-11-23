<?php

function migration_audit_views_data() {

  // Output into a csv file
  $filename = 'views_data.csv';
  header('Content-Type: text/csv; charset=utf-8');
  header('Content-Disposition: attachment; filename=' . $filename);
  $csv_file = fopen("php://output", "w");

  $views_data = migration_get_views_data();
  fputcsv($csv_file, $views_data['header']);
  foreach($views_data['data'] as $key => $record) {
    $data = [];
    if (is_object($record)) {
      $data = (array)$record;
    }

    if (!empty($data)) {
      fputcsv($csv_file, $data, ',', '"');
    }
  }

  fputcsv($csv_file, ['','','','','','','','',]);
  fputcsv($csv_file, ['','','','','','','','',]);
  fputcsv($csv_file, ['','','','','','','','',]);

  $views_display = migration_get_views_display($views_data);
  fputcsv($csv_file, $views_display['header']);
  foreach($views_display['data'] as $key => $record) {
    $data = [];
    if (is_object($record)) {
      $data = (array)$record;
    }

    if (!empty($data)) {
      fputcsv($csv_file, $data, ',', '"');
    }
  }

  fclose($csv_file);
  exit();
}

function migration_get_views_data() {

  $header = [
    'vid' => 'Views ID',
    'name' => 'Views Name',
    'description' => 'Description',
    'tag' => 'Tags',
    'base_table' => 'Base Table',
    'human_name' => 'Human Name',
    'core' => 'Core',
  ];

  //Fetching views data
  $query = db_select('views_view', 'v')
    ->fields('v', array_keys($header))
    ->execute()
    ->fetchAll();

  return array('header' => $header, 'data' => $query);
}

function migration_get_views_display($views_data) {

  $header = [
    'vid' => 'Views ID',
    'id' => 'Id',
    'display_title' => 'Display Title',
    'display_plugin' => 'Display Plugin',
    'position' => 'Position',
    'display_options' => 'Display Options',
  ];

  //Fetching views data
  foreach ($views_data['data'] as $view) {
    $query = db_select('views_display', 'v')
      ->fields('v', array_keys($header))
      ->condition('v.vid', $view->vid, '=')
      ->execute()
      ->fetchAll();
  }

  return array('header' => $header, 'data' => $query);
}

function export_views_entity() {
  // Views Data.
  $views = migration_get_views_data();
  $count1 = count($views['header']);
  $content_data = array(
    array_values($views['header']),
    ['','','','Views data','','','','','','','','',],
    array_values($views['header'])
  );
  foreach ($views['data'] as $data_obj) {
    if (is_object($data_obj)) {
      $data_obj = (array)$data_obj;
    }
    array_push($content_data, array_values($data_obj));
  }

  array_push($content_data, ['','','','','','','','','','','','',]);
  array_push($content_data, ['','','','','','','','','','','','',]);
  array_push($content_data, ['','','','Views Display','','','','','','','','',]);
    // Views Display Data.
  $views_display = migration_get_views_display($views);
  $count2 = count($views_display['header']);
  array_push($content_data, array_values($views_display['header']));

  foreach ($views_display['data'] as $data_obj) {
    if (is_object($data_obj)) {
      $data_obj = (array)$data_obj;
    }
    array_push($content_data, array_values($data_obj));
  }

  $count = ($count1 > $count2) ? $count1 : $count2;
  return array($content_data, $count);
}
