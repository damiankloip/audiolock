<?php

/**
 * Implementation of hook_node_info().
 */
function audiolock_content_types_node_info() {
  $items = array(
    'album' => array(
      'name' => t('Album'),
      'module' => 'features',
      'description' => t('An album acts as a container to reference tracks on the site.'),
      'has_title' => '1',
      'title_label' => t('Album title'),
      'has_body' => '1',
      'body_label' => t('Album description'),
      'min_word_count' => '0',
      'help' => '',
    ),
    'track' => array(
      'name' => t('Track'),
      'module' => 'features',
      'description' => t('Add a track to the site, this will be uploaded and integrated with audiolock.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Body'),
      'min_word_count' => '0',
      'help' => '',
    ),
  );
  return $items;
}
