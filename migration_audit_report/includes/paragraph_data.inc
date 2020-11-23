<?php


function migration_audit_file_paragraph_data() {

  // Output into a csv file
  $filename = 'paragraphs.csv';
  header('Content-Type: text/csv; charset=utf-8');
  header('Content-Disposition: attachment; filename=' . $filename);
  $csv_file = fopen("php://output", "w");

  $content_type = migration_get_paragraphs();

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

function migration_get_paragraphs() {
  $fields = [
    'paragraphs_bundle' => [
      'bundle',
      'name',
      'locked'
    ],
    'paragraphs_item' => [
      'item_id',
      'field_name',
      'archived',
    ]
  ];
  //Fetching Nodes
  $query = db_select('paragraphs_bundle', 'fci');
  $query->leftjoin('paragraphs_item', 'fc', 'fci.bundle = fc.bundle');
  $query->fields('fci', $fields['paragraphs_bundle']);
  $query->fields('fc', $fields['paragraphs_item'])
    ->execute();
  $result = $query->execute()->fetchAll();

  $header = [
    'bundle' => 'Paragraph Type',
    'name' => 'Name',
    'locked' => 'Is Locked',
    'item_id' => 'Paragraph ID',
    'field_name' => 'Field Name',
    'archived' => 'Archived'
  ];

  return array('header' => $header, 'data' => $result);
}

function export_paragraph_entity() {
  $content_type = migration_get_paragraphs();
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
