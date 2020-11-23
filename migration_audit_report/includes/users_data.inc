<?php


function migration_audit_users_data() {

  $users = migration_get_users();

  // Output into a csv file
  $filename = 'users.csv';
  header('Content-Type: text/csv; charset=utf-8');
  header('Content-Disposition: attachment; filename=' . $filename);
  $csv_file = fopen("php://output", "w");

  fputcsv($csv_file, $users['header']);
  foreach($users['data'] as $key => $record) {
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

function migration_get_users() {

  $fields = [
    'users' => [
      'uid' => 'User Id',
      'name' => 'User Name',
      'mail' => 'Mail',
      'theme' => 'Theme',
      'access' => 'Access',
      'status' => 'Status',
      'timezone' => 'Timezone',
      'language' => 'Language',
      'created' => 'Created By',
    ],
    'users_roles' => [
      'rid' => 'Role Id',
      'name' => 'Role Name',
    ]
  ];

  //Fetching Nodes
  $query = db_select('users', 'u');
  $query->leftjoin('users_roles', 'ur', 'u.uid = ur.uid');
  $query->leftjoin('role', 'r', 'ur.rid = r.rid');
  $query->fields('u', array_keys($fields['users']));
  $query->fields('r', array_keys($fields['users_roles']))
    ->execute();
  $result = $query->execute()->fetchAll();


  $header = $fields['users'] + $fields['users_roles'] + array('role_name' => 'Role Name');

  return array('header' => $header, 'data' => $result);
}

function export_users_entity() {
  $content_type = migration_get_users();
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
