<?php

/**
 * @file
 * Display Suite Small left column configuration.
 */

function ds_small_left_column() {
  return array(
    'label' => t('Small left column'),
    'regions' => array(
      'top' => t('Top'),
      'body' => t('Body'),
      'left' => t('Left'),
      'bottom' => t('Bottom'),
    ),
    // Uncomment if you want to include a CSS file for this layout (small_left_column.css)
    'css' => TRUE,
    // Uncomment if you want to include a preview for this layout (small_left_column.png)
    'image' => TRUE,
  );
}
