<?php

/**
 * @file
 * Definition of views_handler_field_locations_link_edit.
 */

/**
 * Field handler to present a term edit link.
 *
 * @ingroup views_field_handlers
 */
class content_score_field_edit_link extends views_handler_field {

  /**
   * {@inheritdoc}
   */
  public function construct() {
    parent::construct();
  }

  /**
   * {@inheritdoc}
   *
   * Perform any database or cache data retrieval here. In this example there is
   * none.
   */
  public function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  /**
   * {@inheritdoc}
   *
   * Called prior to the actual rendering.
   */
  public function pre_render(&$values) {
    foreach ($values as $key => $value) {
      $entity_type = $value->content_score_entity_type;
      if ($value->content_score_entity_type == 'bean') {
        $entity_type = 'block';
      }
      $edit_path = $entity_type . '/' . $value->content_score_entity_id . '/edit';
      $content_score_path = $entity_type . '/' . $value->content_score_entity_id . '/content-score';
      $values[$key]->edit_content_path = $edit_path;
      $values[$key]->scorecard_content_path = $content_score_path;
    }
  }

  /**
   * {@inheritdoc}
   *
   * Modify any end user views settings here. Debug $options to view the field
   * settings you can change.
   */
  public function option_definition() {
    $options = parent::option_definition();
    return $options;
  }

  /**
   * {@inheritdoc}
   *
   * Make changes to the field settings form seen by the end user when adding
   * your field.
   */
  public function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
  }

  /**
   * Render callback handler.
   *
   * Return the markup that will appear in the rendered field.
   */
  public function render($values) {
    $text = l(t('Edit'), $values->edit_content_path) . ' | ' . l(t('Scorecard'), $values->scorecard_content_path);
    return $text;
  }

}
