<?php


function migration_audit_node_type_report_data() {

  // // Output into a csv file
  $filename = 'node_type.csv';
  header('Content-Type: text/csv; charset=utf-8');
  header('Content-Disposition: attachment; filename=' . $filename);
  $csv_file = fopen("php://output", "w");

  $content_type = migration_get_content_type_details();

  fputcsv($csv_file, $content_type['header']);
  foreach($content_type['data'] as $key => $record) {
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

function migration_get_content_type_details() {
  $header = array(
    'type' => 'type',
    'name' => 'Name',
    'base' => 'Base',
    'module' => 'Module',
    'description' => 'Description',
    'title_label' => 'Title Label',
    'custom' => 'Is Custom',
    'modified' => 'Modified',
    'locked' => 'Locaked',
    'disabled' => 'Status',
    'orig_type' => 'Orig Type',
  );

  // Fetching Nodes
  $query = db_select('node_type', 'nt')
    ->fields('nt', array_keys($header))
    ->execute()
    ->fetchAll();

  return array('header' => $header, 'data' => $query);
}

function export_node_type_entity() {
  $content_type = migration_get_content_type_details();
  $count = count($content_type['header']);
  $content_data = array(
    array_values($content_type['header']),
    array_values($content_type['header'])
  );
  foreach ($content_type['data'] as $data_obj) {
    if (is_object($data_obj)) {
      $data_obj = (array)$data_obj;
    }
    array_push($content_data, array_values($data_obj));
  }

  return array($content_data, $count);
}
