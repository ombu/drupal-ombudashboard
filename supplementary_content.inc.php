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
function ombudashboard_supplementary_form($form_state, $delta) {

    $list = module_invoke_all('supplementary_content', 'list', NULL, NULL);
    drupal_set_title($list[$delta]['title']);

    $form = module_invoke_all('supplementary_content', 'form', $delta, NULL);
    $form['#delta'] = $delta;
    $form = system_settings_form($form);
    unset($form['buttons']['reset']);
    $form['buttons']['submit']['#value'] = 'Save';
    $form['buttons']['#weight'] = 50;
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
