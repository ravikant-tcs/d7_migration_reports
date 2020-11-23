<?php

/**
 * @file
 * Contains pfizer-uuid-duplicate command implementation.
 */

/**
 * Implements hook_drush_command().
 */
function migration_audit_report_drush_command() {

  $items['migration-audit-report-export'] = array(
    'description' => 'Checks for webform components that should be encrypted.',
    'aliases' => array('audit-report-export'),
  );

  return $items;
}

/**
 * Callback for the migration-audit-report-export command.
 */
function drush_migration_audit_report_export() {
  printf("Migrating audit report exporting...");

  module_load_include('inc', 'migration_audit_report', 'includes/export_all_data');
  migration_audit_report_export_all_data();

  printf("Migrating audit report exported successfully...");
}
