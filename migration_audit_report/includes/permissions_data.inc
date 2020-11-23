<?php


function migration_audit_permissions_data() {

  $user_perm = migration_get_user_permissions();

  $role_list = user_roles();
  $permissions = user_permission_get_modules();
  // Output into a csv file
  $filename = 'permissions.csv';
  header('Content-Type: text/csv; charset=utf-8');
  header('Content-Disposition: attachment; filename=' . $filename);
  $csv_file = fopen("php://output", "w");

  $result = [[''] + $role_list];

  $count = 1;
  foreach ($permissions as $perm => $module) {
    $result[$count][] = $perm;
    foreach($role_list as $rid => $name) {
      $result[$count][$rid] = '';
      foreach ($user_perm['data'] as $perm_details) {
        if ($perm_details->permission == $perm) {
          $result[$count][$perm_details->rid] = 'Yes';
        }
      }
    }
    $count++;
  }

  foreach ($result as $row) {
    ksort($row);
    fputcsv($csv_file, $row, ',', '"');
  }

  fclose($csv_file);
  exit();
}

function migration_get_user_permissions() {

  $header = array(
    'rid' => 'Role Id',
    'permission' => 'Permissions',
    'module' => 'Module',
    'name' => 'Role Name',
  );

  //Fetching Nodes
  $query = db_select('role_permission', 'rp');
  $query->leftjoin('role', 'r', 'rp.rid = r.rid');
  $query->fields('rp', ['rid', 'permission', 'module']);
  $query->fields('r', ['name'])
    ->execute();
  $result = $query->execute()->fetchAll();

  return array('header' => $header, 'data' => $result);
}

function export_permissions_entity() {
  $content_type = migration_get_user_permissions();
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
