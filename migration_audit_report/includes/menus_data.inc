<?php


function migration_audit_menus_report_data() {

  // // Output into a csv file
  $filename = 'menu_data.csv';
  header('Content-Type: text/csv; charset=utf-8');
  header('Content-Disposition: attachment; filename=' . $filename);
  $csv_file = fopen("php://output", "w");

  $content_type = migration_get_menu_details();

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

function migration_get_menu_details() {
  $header = array(
    'menu_name' => 'Menu Name',
    'link_path' => 'Link Path',
    'router_path' => 'Router Path',
    'link_title' => 'Menu Title',
    'module' => 'Module',
    'hidden' => 'Hidden',
    'external' => 'External',
    'has_children' => 'Has Children',
    'expanded' => 'Extended',
    'depth' => 'Depth',
    'customized' => 'Customized',
  );

  // Fetching Nodes
  $query = db_select('menu_links', 'ml')
    ->fields('ml', array_keys($header))
    ->condition('ml.link_path', '%admin/%', 'NOT LIKE')
    ->condition('ml.module', 'system', '<>')
    ->execute()
    ->fetchAll();

  return array('header' => $header, 'data' => $query);
}
