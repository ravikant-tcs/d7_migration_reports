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
