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
