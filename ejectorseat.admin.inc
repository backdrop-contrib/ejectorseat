<?php

/**
 * @file
 * Configuration settings for Ejector Seat.
 */

/**
 * Admin settings form.
 */
function ejectorseat_settings($form, &$form_state) {
  $form = array();
  $period = array(0 => t('disable')) + backdrop_map_assoc(array(15, 30, 60, 120, 180, 300, 600, 1200, 1800, 3600), 'format_interval');
  $form['ejectorseat_interval'] = array(
    '#type' => 'select',
    '#title' => t('AJAX check rate'),
    '#options' => $period,
    '#description' => t("How often should Ejector Seat check to see if a user has been logged out? Lower rates may affect site performance."),
    '#default_value' => config_get('ejectorseat.settings', 'ejectorseat_interval'),
  );
  $form['ejectorseat_background'] = array(
    '#type' => 'radios',
    '#title' => t('Run AJAX check in background'),
    '#options' => array(
      0 => t('<strong>FALSE:</strong> Only run the AJAX check when the browser window or tab is active. (better performance)'),
      1 => t('<strong>TRUE:</strong> Run the AJAX check even if the browser window or tab is in the background. (better security, CONSIDERABLY worse performance)'),
    ),
    '#default_value' => config_get('ejectorseat.settings', 'ejectorseat_background'),
  );

  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
    '#submit' => array('ejectorseat_settings_submit'),
  );
  return $form;
}

/**
 * Submit handler ejectorseat configuration form.
 */
function ejectorseat_settings_submit($form, &$form_state) {
  config('ejectorseat.settings')
    ->set('ejectorseat_background', $form_state['values']['ejectorseat_background'])
    ->set('ejectorseat_interval', $form_state['values']['ejectorseat_interval'])
    ->save();

  watchdog('ejectorseat', 'Ejector seat settings modified.', array(), WATCHDOG_INFO);
}
