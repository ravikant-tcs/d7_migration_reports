<?php


function migration_audit_languages_data() {

  $languages = migration_get_languages();

  // Output into a csv file
  $filename = 'languages.csv';
  header('Content-Type: text/csv; charset=utf-8');
  header('Content-Disposition: attachment; filename=' . $filename);
  $csv_file = fopen("php://output", "w");
  
  fputcsv($csv_file, $languages['header']);

  foreach($languages['data'] as $key => $data) {
    if (is_object($data)) {
      $data = (array)$data;
    }

    if (!empty($data)) {
      fputcsv($csv_file, $data, ',', '"');
    }
  }

  fclose($csv_file);
  exit();
}

function migration_get_languages() {
  $languages = language_list();
  $default_lang = variable_get('language_default');
  $default_language = $default_lang->language;

  $header = [
    'language' => 'Language Code',
    'name' => 'Name',
    'native' => 'Native',
    'direction' => 'Direction',
    'enabled' => 'Enabled',
    'plurals' => 'Plurals',
    'formula' => 'Formmula',
    'domain' => 'Domain',
    'prefix' => 'Prefix',
    'weight' => 'Weight',
    'default' => 'Default',
  ];

  $result = [];
  foreach ($languages as $key => $language_obj) {
    $result[$key] = [
      'language' => $key,
      'name' => $language_obj->name,
      'native' => $language_obj->native,
      'direction' => $language_obj->direction,
      'enabled' => $language_obj->enabled,
      'plurals' => $language_obj->plurals,
      'formula' => $language_obj->formula,
      'domain' => $language_obj->domain,
      'prefix' => $language_obj->prefix,
      'weight' => $language_obj->weight,
    ];

    $result[$key]['default'] = '';
    if ($key == $default_language) {
      $result[$key]['default'] = 'Yes';
    }
  }

  return array('header' => $header, 'data' => $result);
}
