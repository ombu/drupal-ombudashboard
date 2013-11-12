<?php

/**
 * @file
 * Admin page callbacks for ombudashboard.
 */


/**
 * Callback for clearing cache.
 */
function ombudashboard_clear_caches($form, &$form_state) {
  return confirm_form($form,
    t('Are you sure you want to clear caches?'),
    'admin/dashboard',
    t('All page and site caches will be cleared.  This may take a few minutes.'),
    t('Clear caches')
  );
}

/**
 * Submit handler for clearing cache.
 */
function ombudashboard_clear_caches_submit($form, &$form_state) {
  $form_state['redirect'] = 'admin/dashboard';
  ombudashboard_batch_clear_caches();
}

/**
 * Submit a batch job to clear caches and index solr.
 */
function ombudashboard_batch_clear_caches() {
  $operations[] = array('ombudashboard_clear_cache', array());

  // Only index solr if module is active.
  if (module_exists('apachesolr')) {
    $operations[] = array('ombudashboard_index_batch_index_entities', array());
  }

  $operations[] = array('ombudashboard_run_cron', array());

  $batch = array(
    'operations' => $operations,
    'finished' => 'ombudashboard_batch_finished',
    'title' => t('Clearing'),
    'init_message' => t('Preparing to clear caches..'),
    'progress_message' => t('Clearing caches..'),
    'error_message' => t('There was a problem with clearing caches.'),
    'file' => drupal_get_path('module', 'ombudashboard') . '/ombudashboard.admin.inc',
  );
  batch_set($batch);

  // Rebuild xmlsitemap if needed.
  if (module_exists('xmlsitemap')) {
    // If there were no new or changed links, skip.
    if (!variable_get('xmlsitemap_regenerate_needed', FALSE)) {
      return;
    }

    // If the minimum sitemap lifetime hasn't been passed, skip.
    $lifetime = REQUEST_TIME - variable_get('xmlsitemap_generated_last', 0);
    if ($lifetime < variable_get('xmlsitemap_minimum_lifetime', 0)) {
      return;
    }

    module_load_include('inc', 'xmlsitemap', 'xmlsitemap.generate');
    $batch = xmlsitemap_regenerate_batch();
    batch_set($batch);
  }
}

/**
 * Batch callback, clear cache.
 */
function ombudashboard_clear_cache(&$context) {
  drupal_flush_all_caches();
  $context['message'] = 'Caches cleared';
}

/**
 * Batch callback, run solr indexing.
 */
function ombudashboard_index_batch_index_entities(&$context) {
  module_load_include('inc', 'apachesolr', 'apachesolr.admin');
  apachesolr_index_batch_index_entities('solr', $context);
}

/**
 * Batch callback, run cron.
 */
function ombudashboard_run_cron(&$context) {
  drupal_cron_run();
  $context['message'] = 'Cron run successfully';
}

/**
 * Batch 'finished' callback.
 */
function ombudashboard_batch_finished($success, $results, $operations) {
  if ($success) {
    $message = 'Caches successfully cleared.';
    $type = 'status';
  }
  else {
    $message = 'There was an error clearing caches';
    $type = 'error';
  }
  drupal_set_message($message, $type);
}
