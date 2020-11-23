<?php


function migration_audit_modules_data() {

  $modules = migration_get_module_details();

  // Output into a csv file
  $filename = 'menu_data.csv';
  header('Content-Type: text/csv; charset=utf-8');
  header('Content-Disposition: attachment; filename=' . $filename);
  $csv_file = fopen("php://output", "w");

  fputcsv($csv_file, $modules['header']);
  foreach($modules['data'] as $key => $record) {
    $data = $record;
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

function migration_get_module_details() {
  $header = array(
    'name' => 'Module Name',
    'filename' => 'Module type',
    'type' => 'Type',
    'status' => 'Status',
    'info' => 'Description',
  );

  // Fetching Nodes
  $query = db_select('system', 's')
    ->fields('s', array_keys($header))
    ->condition('s.filename', 'sites/default/%', 'LIKE')
    ->execute()
    ->fetchAll();

  $result = [];
  foreach ($query as $key => $data) {
    $info = unserialize($data->info);
    $result[$key] = (array)$data;

    $header['dependencies'] = 'Module Dependencies';
    $header['version'] = 'Current Version';
    $header['package'] = 'Package';

    $result[$key]['info'] = $info['description'];
    $result[$key]['dependencies'] = implode(', ', $info['dependencies']);
    $result[$key]['version'] = $info['version'];
    $result[$key]['package'] = $info['package'];
    $result[$key]['status'] = !empty($data->status) ? 'enable' : 'disable';
    $result[$key]['filename'] = (strpos($data->filename, 'custom/')) ? 'Site Custom' : 'Site Contrib';
  }

  return array('header' => $header, 'data' => $result);
}

function export_modules_entity() {
  $content_type = migration_get_module_details();
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
