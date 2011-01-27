<?php

function siteconfig_form() {
    // Let other modules define siteconfig elements
    $form = module_invoke_all('siteconfig', 'form', $form);

    // Will automatically save the values by their key
    // Use another submit function if more control is needed
    $form = system_settings_form($form);
    unset($form['buttons']['reset']);
    $form['buttons']['submit']['#value'] = 'Save';
    $form['buttons']['#weight'] = 50;
    $form['#submit'][] = 'siteconfig_form_submit';
    return $form;
}

function siteconfig_form_submit($form, &$form_state) {
    module_invoke_all('siteconfig', 'save', $form_state['values']);
}

/**
 * Implementation of hook_siteconfig()
 *
 * @param $op | only 'form' for now.  TODO: add a 'save' state for more complex saves
 * @param $form | form object to which elements should be added
 *
 * @return $form | must return the form object
 */
function ombudashboard_siteconfig($op, $form) {
    if ($op == 'form') {
        $form['baseinfo'] = array(
            '#type' => 'fieldset',
            '#title' => t('Basic Site Information'),
            '#collapsible' => TRUE,
            '#collapsed' => TRUE,
            '#weight' => -50,
        );
        $form['baseinfo']['site_name'] = array(
            '#title' => t('Site Title'),
            '#type' => 'textfield',
            '#default_value' => variable_get('site_name', ''),
            '#description' => 'The Site Title appears in the browser window and on email correspondence.',
        );
        $form['baseinfo']['site_mail'] = array(
            '#title' => t('Site Email Address'),
            '#type' => 'textfield',
            '#default_value' => variable_get('site_mail', ''),
            '#description' => 'This address is used for email correspondence. Please use a valid email address.',
        );

        // Google Analytics
        $form['analytics'] = array(
            '#type' => 'fieldset',
            '#title' => t('Google Analytics Key'),
            '#collapsible' => TRUE,
            '#collapsed' => TRUE,
        );
        $form['analytics']['google_analytics_key'] = array(
            '#type' => 'textfield',
            '#default_value' => variable_get('google_analytics_key', ''),
            '#description' => 'Google Analytics will be used if this key is provided. <em>Ex Key: "UA-1234567-89"</em>',
        );
        return $form;
    }
}
