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
