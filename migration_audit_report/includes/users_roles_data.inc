<?php


function migration_audit_users_roles_data() {

  // Output into a csv file
  $filename = 'user_roles.csv';
  header('Content-Type: text/csv; charset=utf-8');
  header('Content-Disposition: attachment; filename=' . $filename);
  $csv_file = fopen("php://output", "w");

  $user_roles = migration_get_user_roles();

  fputcsv($csv_file, $user_roles['header']);
  foreach($user_roles['data'] as $key => $record) {
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

function migration_get_user_roles() {

  $header = array(
    'rid' => 'Role Id',
    'name' => 'Role Name',
    'weight' => 'Weight',
  );

  //Fetching Roles.
  $query = db_select('role', 'r')
    ->fields('r', array_keys($header))
    ->execute()
    ->fetchAll();

  return array('header' => $header, 'data' => $query);
}

function export_users_roles_entity() {
  $content_type = migration_get_user_roles();
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
