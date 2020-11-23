<?php


function migration_audit_node_report_data() {

  // Output into a csv file
  $filename = 'contents.csv';
  header('Content-Type: text/csv; charset=utf-8');
  header('Content-Disposition: attachment; filename=' . $filename);
  $csv_file = fopen("php://output", "w");

  $content_type = migration_get_content_types();

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

function migration_get_content_types() {
  //Fetching Nodes
  $query = db_select('node', 'n')
    ->fields('n', array())
    ->execute()
    ->fetchAll();

  $header = array(
    'nid' => 'Node Id',
    'vid' => 'Version Id',
    'type' => 'Content Type',
    'language' => 'Content Language',
    'title' => 'Title',
    'uid' => 'User Id',
    'status' => 'Status',
    'created' => 'Created',
    'changed' => 'Changed',
    'comment' => 'Comment',
    'promote' => 'Promote',
    'sticky' => 'Sticky',
    'tnid' => 'Tnid',
    'translate' => 'Translate',
  );

  return array('header' => $header, 'data' => $query);
}

function export_node_entity() {
  $content_type = migration_get_content_types();
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
