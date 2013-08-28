<?php

/**
 * @file
 * Display Suite New custom layout configuration.
 */

function ds_new_custom_layout() {
  return array(
    'label' => t('New custom layout'),
    'regions' => array(
      'left' => t('Left'),
      'right' => t('Right'),
    ),
    // Uncomment if you want to include a CSS file for this layout (new_custom_layout.css)
    // 'css' => TRUE,
    // Uncomment if you want to include a preview for this layout (new_custom_layout.png)
    // 'image' => TRUE,
  );
}
