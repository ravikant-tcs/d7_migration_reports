<?php


function migration_audit_taxonomy_data() {

  $taxonomy_voc = migration_get_taxonomy_voc_details();

  // Output into a csv file
  $filename = 'taxonomy_data.csv';
  header('Content-Type: text/csv; charset=utf-8');
  header('Content-Disposition: attachment; filename=' . $filename);
  $csv_file = fopen("php://output", "w");

  fputcsv($csv_file, $taxonomy_voc['header']);
  foreach($taxonomy_voc['data'] as $key => $record) {
    $data = [];
    if (is_object($record)) {
      $data = (array)$record;
    }

    if (!empty($data)) {
      fputcsv($csv_file, $data, ',', '"');
    }
  }

  fputcsv($csv_file, ['','','','','','','','','','','','','','','','',]);
  fputcsv($csv_file, ['','','','','','','','','','','','','','','','',]);

  // Get all terms for each vocabulary.
  $taxonomy = migration_get_taxonomy_details($taxonomy_voc);

  fputcsv($csv_file, $taxonomy['header']);
  foreach($taxonomy['data'] as $key => $taxonomy_tree) {
    foreach ($taxonomy_tree as $k => $record) {
      $data = $record;
      if (is_object($record)) {
        $data = (array)$record;
      }

      if (!empty($data)) {
        fputcsv($csv_file, $data, ',', '"');
      }
    }
  }

  fclose($csv_file);
  exit();
}

function migration_get_taxonomy_voc_details() {
  $header = array(
    'vid' => 'Vocabulary ID',
    'name' => 'Vocabulary Name',
    'machine_name' => 'Vocabulary Machine Name',
    'module' => 'Vocabulary Module',
  );

  // Fetching Nodes
  $query = db_select('taxonomy_vocabulary', 'tv')
    ->fields('tv', array_keys($header))
    ->execute()
    ->fetchAll();

  return array('header' => $header, 'data' => $query);
}

function migration_get_taxonomy_details($vocabulary_details) {

  $header = [
    'vname' => 'Vocabulary Name',
    'v_machine_name' => 'Vocabulary Machine Name',
    'vmodule' => 'Vocabulary Module',
    'vlanguage' => 'Vocabulary Language',
    'tid' => 'Term Id',
    'vid' => 'Vocabulary ID',
    'name' => 'Name',
    'description' => 'Description',
    'format' => 'Format',
    'weight' => 'Weight',
    'uuid' => 'UUID',
    'language' => 'Language',
    'i18n_tsid' => 'Multilingual Term ID',
    'depth' => 'Depth',
  ];

  $taxonomy_terms = [];
  foreach ($vocabulary_details['data'] as $voc) {
    $taxonomy_tree = taxonomy_get_tree($voc->vid);
    foreach ($taxonomy_tree as $key => $taxonomy_data) {
      $taxonomy_data = (array)$taxonomy_data;
      $vocabulary_data = [
        'vname' => $voc->name,
        'v_machine_name' => $voc->machine_name,
        'vmodule' => $voc->module,
        'vlanguage' => $voc->language,
      ];

      $taxonomy_terms[$voc->vid][$taxonomy_data['tid']] = $vocabulary_data + $taxonomy_data;
      unset($taxonomy_terms[$voc->vid][$taxonomy_data['tid']]['parents']);
    }
  }

  return array('header' => $header, 'data' => $taxonomy_terms);
}

function export_taxonomy_entity() {
  // Vocabulary Data.
  $voc = migration_get_taxonomy_voc_details();
  $count1 = count($voc['header']);
  $content_data = array(
    array_values($voc['header']),
    ['','','','Vocabulary data','','','','','','','','',],
    array_values($voc['header'])
  );
  foreach ($voc['data'] as $data_obj) {
    if (is_object($data_obj)) {
      $data_obj = (array)$data_obj;
    }
    array_push($content_data, array_values($data_obj));
  }

  array_push($content_data, ['','','','','','','','','','','','','','','','',]);
  array_push($content_data, ['','','','','','','','','','','','','','','','',]);
  array_push($content_data, ['','','','Terms data','','','','','','','','',]);
    // Terms Data.
  $term = migration_get_taxonomy_details($voc);
  $count2 = count($term['header']);
  array_push($content_data, array_values($term['header']));

  foreach ($term['data'] as $value) {
    foreach ($value as $key => $data_obj) {
      if (is_object($data_obj)) {
        $data_obj = (array)$data_obj;
      }
      array_push($content_data, array_values($data_obj));
    }
  }

  $count = ($count1 > $count2) ? $count1 : $count2;
  return array($content_data, $count);
}
