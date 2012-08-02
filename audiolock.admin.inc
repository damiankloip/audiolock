<?php

/**
 * Admin settings form callback.
 */
function audiolock_admin_settings_form() {
  $form = array();

  $content_types = array_map('check_plain', node_get_types('names'));

  // API settings.
  $form['api'] = array(
    '#type' => 'fieldset',
    '#title' => t('API settings'),
    '#collapsible' => TRUE,
    '#collpased' => FALSE,
  );

  $form['api']['audiolock_api_key'] = array(
    '#type' => 'textfield',
    '#title' => t('API key'),
    '#size' => 80,
    '#description' => t('Enter your Audiolock API key here. Add more description....'),
    '#default_value' => variable_get('audiolock_api_key', ''),
  );
  $form['api']['audiolock_wsdl'] = array(
    '#type' => 'textfield',
    '#title' => t('WSDL URL'),
    '#description' => t('Enter Audiolock WSDL URL path here. Add more description....'),
    '#default_value' => variable_get('audiolock_wsdl', 'http://www.audiolock.net/soapServerv2.php?wsdl'),
  );

  // Content type settings.
  $form['content_type'] = array(
    '#type' => 'fieldset',
    '#title' => t('Content type settings'),
    '#collapsible' => TRUE,
    '#collpased' => FALSE,
  );

  $form['content_type']['audiolock_album_content_type'] = array(
    '#type' => 'radios',
    '#title' => t('Album content type'),
    '#options' => $content_types,
    '#default_value' => variable_get('audiolock_album_content_type', NULL),
  );

  $form['content_type']['audiolock_track_content_type'] = array(
    '#type' => 'radios',
    '#title' => t('Track content type'),
    '#options' => $content_types,
    '#default_value' => variable_get('audiolock_track_content_type', NULL),
  );

  // General settings.
  $form['general'] = array(
    '#type' => 'fieldset',
    '#title' => t('General settings'),
    '#collapsible' => TRUE,
    '#collpased' => FALSE,
  );

  $form['general']['audiolock_user_show_recipient_id'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show User\'s Audiolock recipient ID on their user page'),
    '#default_value' => variable_get('audiolock_user_show_recipient_id', TRUE),
  );

  if (module_exists('audiolock_album')) {
    $form['general']['audiolock_album_download_link_text'] = array(
      '#type' => 'textfield',
      '#title' => t('Text to show for album download link.'),
      '#default_value' => variable_get('audiolock_album_download_link_text', 'Download album'),
    );
  }

  return system_settings_form($form);
}
