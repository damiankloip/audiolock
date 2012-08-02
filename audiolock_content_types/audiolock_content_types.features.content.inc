<?php

/**
 * Implementation of hook_content_default_fields().
 */
function audiolock_content_types_content_default_fields() {
  $fields = array();

  // Exported field: field_track_reference
  $fields['album-field_track_reference'] = array(
    'field_name' => 'field_track_reference',
    'type_name' => 'album',
    'display_settings' => array(
      'label' => array(
        'format' => 'above',
        'exclude' => 0,
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'nodereference',
    'required' => '0',
    'multiple' => '1',
    'module' => 'nodereference',
    'active' => '1',
    'referenceable_types' => array(
      'track' => 'track',
      'album' => 0,
      'page' => 0,
      'story' => 0,
    ),
    'advanced_view' => '--',
    'advanced_view_args' => '',
    'widget' => array(
      'autocomplete_match' => 'contains',
      'size' => '60',
      'default_value' => array(
        '0' => array(
          'nid' => NULL,
          '_error_element' => 'default_value_widget][field_track_reference][0][nid][nid',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Tracks',
      'weight' => '-4',
      'description' => '',
      'type' => 'nodereference_autocomplete',
      'module' => 'nodereference',
    ),
  );

  // Exported field: field_audiolock_upload
  $fields['track-field_audiolock_upload'] = array(
    'field_name' => 'field_audiolock_upload',
    'type_name' => 'track',
    'display_settings' => array(
      'label' => array(
        'format' => 'above',
        'exclude' => 0,
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'audiolock',
    'required' => '1',
    'multiple' => '0',
    'module' => 'audiolock',
    'active' => '1',
    'audiolock_uid' => '',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'audiolock' => array(
            'audiolock_file' => '',
            'track' => array(
              'track_artist' => '',
              'track_name' => '',
              'track_uid' => '',
            ),
          ),
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Audiolock upload',
      'weight' => '-4',
      'description' => '',
      'type' => 'audiolock_widget',
      'module' => 'audiolock',
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Audiolock upload');
  t('Tracks');

  return $fields;
}
