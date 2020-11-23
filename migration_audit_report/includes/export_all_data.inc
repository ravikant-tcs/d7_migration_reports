<?php

function migration_audit_report_export_all_data() {
  $export_list = REPORT_ENTITIES;

  unset($export_list['export_all']);
  $export_list = array_keys($export_list);

  module_load_include('inc', 'phpexcel');
  $library = libraries_load('PHPExcel');

  // Filename for download
  $site_name = trim(variable_get('site_name'));
  $site_name = str_replace(' ', '_', $site_name);
  $filename = $site_name . "_export_data_" . date('Ymd') . ".xls";

  $objPHPExcel = new PHPExcel();

  foreach ($export_list as $key => $entity_name) {
    module_load_include('inc', 'migration_audit_report', 'includes/' . $entity_name . '_data');
  }

  $data_in_aray = get_all_entity_data_in_array();

  $sheet_index = 0;
  foreach ($data_in_aray as $key => $value) {
    $objPHPExcel->setActiveSheetIndex($sheet_index);

    for ($i = 0; $i <= count($value['data']); $i++) {
      for($j = 0; $j <= $value['count']; $j++ ) {
        $objPHPExcel->getActiveSheet()->setCellValueByColumnAndRow($j, $i, $value['data'][$i][$j]);
      }
    }

    /*Rename sheet*/
    $objPHPExcel->getActiveSheet()->setTitle(ucwords($key));

    /* Create a new worksheet, after the default sheet*/
    $objPHPExcel->createSheet();
    $sheet_index++;
  }

  /* Redirect output to a client’s web browser (Excel5)*/
  header('Content-Type: application/vnd.ms-excel');
  header('Content-Disposition: attachment;filename=' . $filename);
  header('Cache-Control: max-age=0');
  $objWriter = PHPExcel_IOFactory::createWriter($objPHPExcel, 'Excel5');
  $objWriter->save('php://output');

  exit();
}

function get_all_entity_data_in_array() {
  // Node data.
  list($node, $column_count) = export_node_entity();
  $export_all_entities['node'] = [
    'count' => $column_count,
    'data' => $node,
  ];

  // Content Type data.
  list($file_data, $column_count) = export_node_type_entity();
  $export_all_entities['node_type'] = [
    'count' => $column_count,
    'data' => $file_data,
  ];

  // field data.
  list($field, $column_count) = export_field_entity();
  $export_all_entities['field'] = [
    'count' => $column_count,
    'data' => $field,
  ];

    // blocks data.
  list($blocks, $column_count) = export_blocks_entity();
  $export_all_entities['blocks'] = [
    'count' => $column_count,
    'data' => $blocks,
  ];

  // menus data.
  list($menus, $column_count) = export_menus_entity();
  $export_all_entities['menus'] = [
    'count' => $column_count,
    'data' => $menus,
  ];
  // taxonomy data.
  list($taxonomy, $column_count) = export_taxonomy_entity();
  $export_all_entities['taxonomy'] = [
    'count' => $column_count,
    'data' => $taxonomy,
  ];

  // views data.
  list($views, $column_count) = export_views_entity();
  $export_all_entities['views'] = [
    'count' => $column_count,
    'data' => $views,
  ];

  // users_roles data.
  list($users_roles, $column_count) = export_users_roles_entity();
  $export_all_entities['users_roles'] = [
    'count' => $column_count,
    'data' => $users_roles,
  ];

  // users data.
  list($users, $column_count) = export_users_entity();
  $export_all_entities['users'] = [
    'count' => $column_count,
    'data' => $users,
  ];

  // permissions data.
  list($permissions, $column_count) = export_permissions_entity();
  $export_all_entities['permissions'] = [
    'count' => $column_count,
    'data' => $permissions,
  ];

  // languages data.
  list($languages, $column_count) = export_languages_entity();
  $export_all_entities['languages'] = [
    'count' => $column_count,
    'data' => $languages,
  ];

  // modules data.
  list($modules, $column_count) = export_modules_entity();
  $export_all_entities['modules'] = [
    'count' => $column_count,
    'data' => $modules,
  ];

  // File data data.
  list($file_data, $column_count) = export_file_media_data_entity();
  $export_all_entities['file_data'] = [
    'count' => $column_count,
    'data' => $file_data,
  ];

  return $export_all_entities;
}
