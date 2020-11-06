<?php

require_once DRUPAL_ROOT . '/classes/PHPExcel.php';

function migration_audit_report_export_all_data() {
  $export_list = REPORT_ENTITIES;
  unset($export_list['export_all']);
  $export_list = array_keys($export_list);

  foreach ($export_list as $export_file) {
    module_load_include('inc', 'migration_audit_report', 'includes/' . $export_file . '_data');
  }

  // Filename for download
  $site_name = trim(variable_get('site_name'));
  $site_name = str_replace(' ', '_', $site_name);
  $filename = $site_name . "_export_data_" . date('Ymd') . ".xls";

  // Write a code to merge all entity data into one excel file.

  exit();
}
