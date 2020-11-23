<?php

function migration_audit_block_report_data() {

  // Block Data.
  $block_fields = migration_get_block_data();

  $filename = 'blocks_data.csv';
  header('Content-Type: text/csv; charset=utf-8');
  header('Content-Disposition: attachment; filename=' . $filename);
  $csv_file = fopen("php://output", "w");

  fputcsv($csv_file, $block_fields['header']);
  foreach($block_fields['data'] as $key => $record) {
    $data = [];
    if (is_object($record)) {
      $data = (array)$record;
    }

    if (!empty($data)) {
      fputcsv($csv_file, $data, ',', '"');
    }
  }

  // Custom_Block Data.
  $custom_block_fields = migration_get_block_custom_data();

  fputcsv($csv_file, ['','','','','','','','',]);
  fputcsv($csv_file, ['','','','','','','','',]);
  fputcsv($csv_file, ['','','','Custom Block Data','','','','',]);
  fputcsv($csv_file, $custom_block_fields['header']);

  foreach($custom_block_fields['data'] as $key => $record) {
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

function migration_get_block_data() {

  $fields = [
    'block' => [
      'module',
      'delta',
      'theme',
      'status',
      'region',
      'visibility',
    ]
  ];

  //Fetching Nodes
  $query = db_select('block', 'b')
    ->fields('b', $fields['block'])
    ->execute()
    ->fetchAll();

  $block_header = [
    'module' => 'Module',
    'delta' => 'Delta',
    'theme' => 'Theme',
    'status' => 'Status',
    'region' => 'Region',
    'visibility' => 'Visibility'
  ];

  return ['header' => $block_header, 'data' => $query];
}

function migration_get_block_custom_data() {

  // block_custom data.
  $block_custom_fields = [
    'block_custom' => [
      'body',
      'info',
      'format',
    ],
  ];

  // Fetching Nodes
  $query = db_select('block_custom', 'bc');
  $query->fields('bc', $block_custom_fields['block_custom'])
    ->execute();
  $result = $query->execute()->fetchAll();

  $block_custom_header = [
    'body' => 'Body',
    'info' => 'Info',
    'format' => 'Format',
  ];

  return ['header' => $block_custom_header, 'data' => $result];
}

function export_blocks_entity() {
  // Add block data.
  $block_data = migration_get_block_data();
  $count1 = count($block_data['header']);
  $content_data = array(
    array_values($block_data['header']),
    array_values($block_data['header'])
  );
  foreach ($block_data['data'] as $data_obj) {
    if (is_object($data_obj)) {
      $data_obj = (array)$data_obj;
    }
    array_push($content_data, array_values($data_obj));
  }

  array_push($content_data, ['','','','','','','','',]);
  array_push($content_data, ['','','','','','','','',]);
  array_push($content_data, ['','','','Custom Block Data','','','','',]);
  // Custom block data.
  $custom_block = migration_get_block_custom_data();
  $count2 = count($custom_block['header']);
  array_push($content_data, array_values($custom_block['header']));

  foreach ($custom_block['data'] as $data_obj) {
    if (is_object($data_obj)) {
      $data_obj = (array)$data_obj;
    }
    array_push($content_data, array_values($data_obj));
  }

  $count = ($count1 > $count2) ? $count1 : $count2;
  return array($content_data, $count);
}
