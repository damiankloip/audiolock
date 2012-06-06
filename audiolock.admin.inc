<?php

/**
 * Admin settings form callback.
 */
function audiolock_admin_settings_form() {
  $form = array();

  $form['api'] = array(
    '#type' => 'fieldset',
    '#title' => t('API settings'),
    '#collapsible' => TRUE,
    '#collpased' => FALSE,
  );

  $form['api']['audiolock_api_key'] = array(
    '#type' => 'textfield',
    '#title' => t('API key'),
    '#description' => t('Enter your Audiolock API key here. Add more description....'),
    '#default_value' => variable_get('audiolock_api_key', ''),
  );
  $form['api']['audiolock_wsdl'] = array(
    '#type' => 'textfield',
    '#title' => t('WSDL URL'),
    '#description' => t('Enter Audiolock WSDL URL path here. Add more description....'),
    '#default_value' => variable_get('audiolock_wsdl', 'http://www.audiolock.net/soapServerv2.php?wsdl'),
  );

  return system_settings_form($form);
}
