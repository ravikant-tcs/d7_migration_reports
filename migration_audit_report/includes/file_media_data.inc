<?php


function migration_audit_file_media_data() {

  $modules = migration_get_files_details();

  // Output into a csv file
  $filename = 'files_data.csv';
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

function migration_get_files_details() {
  $private_path = variable_get('file_private_path');
  $public_path = variable_get('file_public_path');
  $tem_path = variable_get('file_temporary_path');

  $header = [
    'file_managed' => [
      'fid' => 'File Id',
      'uid' => 'User Id',
      'filename' => 'File Name',
      'uri' => 'File Path',
      'filemime' => 'File Type',
      'filesize' => 'File Size',
      'status' => 'Status',
      'timestamp' => 'Created Date',
    ],
    'file_usage' => [
      'module' => 'Module usage',
      'type' => 'Usage Entity Type',
      'id' => 'Entity Id',
      'count' => 'Count',
    ],
  ];

  $query = db_select('file_managed', 'fm');
  $query->leftjoin('file_usage', 'fu', 'fm.fid = fu.fid');
  $query->fields('fm', array_keys($header['file_managed']));
  $query->fields('fu', array_keys($header['file_usage']))
    ->execute();
  $result = $query->execute()->fetchAll();

  $header = array_values($header['file_managed']) + array_values($header['file_usage']);

  return array('header' => $header, 'data' => $result);
}
