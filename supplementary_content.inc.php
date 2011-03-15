<?php

/**
 * @file
 * Provides supplementary content hook functionality for ombudashboard
 *
 * Exposes a mechanism for supplying forms for supplementary content. All
 * values are saved as variables via system_settings_form().  If additional
 * processing is needed on form submissions, implement the 'save' operation.
 *
 * Parameters for hook_supplementary_content():
 *
 * @param $op string Three possible values:
 *   'list': Return an array of associative arrays in the form:
 *       array(
 *         '{delta}' => array(
 *           'title' => 'My Supplementary Content Title',
 *           'description' => 'My Description',
 *           'permission' => 'some permission'
 *         ),
 *       );
 *      '{delta}' needs to be a url-safe string.  Preferably only lower-case
 *      letters, numbers and dashes.
 *
 *      The 'permission' key is an optional permission to check before giving
 *      access to this supplementary content item.  All supplementary content
 *      items are first checked against the 'edit supplementary content'
 *      permission.
 *
 *   'form': Return the form for the given $delta value.
 *   'save': Optionally process the values in $edit for the given $delta.
 *
 * @param $delta string The specific content item being worked on. NULL when $op
 *   is 'list'.
 *
 * @param $edit array The array of form values for the given $delta when $op is
 *   'save'.  Used to perform any additional processing after form submission.
 *   Value is NULL unless 'op' is 'save'.
 */

/**
 * Returns an array ready for the dashboard's supplementary content block
 */
function ombudashboard_get_supplementary_content_list() {
    $list = module_invoke_all('supplementary_content', 'list', NULL, NULL);
    $items = array();
    foreach($list as $slug => $info) {

        if ($info['permission'] && !user_access($info['permission'])) {
            // Failed permission check
            continue;
        }

        $items[] = array(
            'title' => $info['title'],
            'description' => $info['description'],
            'href' => 'admin/dashboard/supplementary-content/'. $slug,
            'localized_options' => array(
                'query' => drupal_get_destination(),
            ),
        );
    }
    return $items;
}

/**
 * Callback for the given $delta. Presents the form to the user.
 */
function ombudashboard_supplementary_form($form, $form_state, $delta) {

    $list = module_invoke_all('supplementary_content', 'list', NULL, NULL);
    drupal_set_title($list[$delta]['title']);

    $form = module_invoke_all('supplementary_content', 'form', $delta, NULL);
    $form['#delta'] = $delta;
    // Check if supplementary content will handle own submission
    if (!isset($list[$delta]['handle own submission'])) {
      $form = system_settings_form($form);
    }
    $form['actions']['submit']['#value'] = 'Save';
    $form['actions']['#weight'] = 50;
    $form['#submit'][] = 'ombudashboard_supplementary_content_callback_save';
    return $form;
}

/**
 * Save callback for $form['#delta']
 */
function ombudashboard_supplementary_content_callback_save($form, $form_state) {
    $delta = $form['#delta'];
    module_invoke_all('supplementary_content', 'save', $delta, $form_state['values']);
}

/**
 * Implementation of hook_supplementary_content().
 *
 * Show simple edit form for blocks.  Blocks will be displayed if module/delta 
 * is set in the block_simple_ui variable.
 */
function ombudashboard_supplementary_content($op, $delta = NULL, $edit = NULL) {
  switch ($op) {
    case 'list':
      // Only show if blocks are set.
      if (variable_get('block_simple_ui', array())) {
        return array(
          'blocks' => array(
            'title' => t('Block Content'),
            'description' => t('Edit block content'),
            'permission' => 'administer blocks',
            'handle own submission' => TRUE,
          ),
        );
      }
      break;

    case 'form':
      switch ($delta) {
        case 'blocks':
          $form = array();
          $form['#tree'] = TRUE;
          $blocks = variable_get('block_simple_ui', array());
          module_load_include('inc', 'block', 'block.admin');
          foreach ($blocks as $block) {
            // Load block and block info
            $block = block_load($block['module'], $block['delta']);
            $info = module_invoke($block->module, 'block_info');

            // block form sets title, so we need to set it back
            $title = drupal_get_title();
            $block_form = drupal_get_form('block_admin_configure', $block->module, $block->delta);
            drupal_set_title($title);

            $form['blocks'][$block->module][$block->delta] = array(
              '#title' => $info[$block->delta]['info'],
              '#type' => 'fieldset',
              '#collapsible' => TRUE,
              '#collapsed' => TRUE,
            );

            $hide_fields = array('info');
            foreach ($hide_fields as $hide) {
              $block_form['settings'][$hide]['#access'] = FALSE;
            }

            foreach (element_children($block_form['settings']) as $field) {
              $block_form['settings'][$field]['#tree'] = TRUE;
              unset($block_form['settings'][$field]['#parents']);
            }
            unset($block_form['settings']['#parents']);

            // For some reason, format is showing above body by default.
            $block_form['settings']['body_field']['body']['format']['#weight'] = 100;

            $form['blocks'][$block->module][$block->delta] += $block_form['settings'];
          }
          $form['actions']['submit'] = array(
            '#type' => 'submit',
            '#value' => 'Save',
          );
          return $form;
          break;
      }
      break;

    case 'save':
      break;
  }
}
