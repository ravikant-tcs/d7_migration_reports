<?php


function migration_audit_field_report_data() {

  // Output into a csv file
  $fields = migration_get_fields();

  $filename = 'field_data.csv';
  header('Content-Type: text/csv; charset=utf-8');
  header('Content-Disposition: attachment; filename=' . $filename);
  $csv_file = fopen("php://output", "w");

  fputcsv($csv_file, $fields['header']);
  foreach($fields['data'] as $key => $record) {
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

function migration_get_fields() {
  $fields = [
    'field_config_instance' => [
      'entity_type',
      'bundle'
    ],
    'field_config' => [
      'type',
      'module',
      'active',
      'field_name'
    ]
  ];
  //Fetching Nodes
  $query = db_select('field_config_instance', 'fci');
  $query->leftjoin('field_config', 'fc', 'fci.field_id = fc.id');
  $query->fields('fci', $fields['field_config_instance']);
  $query->fields('fc', $fields['field_config'])
    ->execute();
  $result = $query->execute()->fetchAll();

  $header = [
    'entity_type' => 'Entity Type',
    'bundle' => 'Content Type',
    'type' => 'Field Type',
    'module' => 'Module',
    'active' => 'Active',
    'field_name' => 'Field Name'
  ];

  return ['header' => $header, 'data' => $result];
}
