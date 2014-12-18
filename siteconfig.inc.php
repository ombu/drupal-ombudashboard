<?php
/**
 * @file
 * Site config specific callbacks.
 */

/**
 * Form callback for siteconfig.
 */
function siteconfig_form() {
  // Let other modules define siteconfig elements.
  $form = array();
  $form = module_invoke_all('siteconfig', 'form', $form);

  // Will automatically save the values by their key Use another submit function
  // if more control is needed.
  $form = system_settings_form($form);
  unset($form['buttons']['reset']);
  $form['buttons']['submit']['#value'] = 'Save';
  $form['buttons']['#weight'] = 50;
  $form['#submit'][] = 'siteconfig_form_submit';
  return $form;
}

/**
 * Submit callback for siteconfig form.
 */
function siteconfig_form_submit($form, &$form_state) {
  module_invoke_all('siteconfig', 'save', $form_state['values']);
}

/**
 * Implements hook_siteconfig().
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

    // Email.
    if (module_exists('smtp')) {
      $form['email'] = array(
        '#type' => 'fieldset',
        '#title' => t('Email'),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
      );

      $form['email']['smtp_host'] = array(
        '#type'          => 'textfield',
        '#title'         => t('SMTP server'),
        '#default_value' => variable_get('smtp_host', ''),
        '#description'   => t('The address of your outgoing SMTP server.'),
      );
      $form['email']['smtp_hostbackup'] = array(
        '#type'          => 'textfield',
        '#title'         => t('SMTP backup server'),
        '#default_value' => variable_get('smtp_hostbackup', ''),
        '#description'   => t("The address of your outgoing SMTP backup server. If the primary server can't be found this one will be tried. This is optional."),
      );
      $form['email']['smtp_port'] = array(
        '#type'          => 'textfield',
        '#title'         => t('SMTP port'),
        '#size'          => 6,
        '#maxlength'     => 6,
        '#default_value' => variable_get('smtp_port', '25'),
        '#description'   => t('The default SMTP port is 25, if that is being blocked try 80. Gmail uses 465. See !url for more information on configuring for use with Gmail.', array('!url' => l(t('this page'), 'http://gmail.google.com/support/bin/answer.py?answer=13287'))),
      );
      // Only display the option if openssl is installed.
      if (function_exists('openssl_open')) {
        $encryption_options = array(
          'standard' => t('No'),
          'ssl'      => t('Use SSL'),
          'tls'      => t('Use TLS'),
        );
        $encryption_description = t('This allows connection to an SMTP server that requires SSL encryption such as Gmail.');
      }
      // If openssl is not installed, use normal protocol.
      else {
        variable_set('smtp_protocol', 'standard');
        $encryption_options = array('standard' => t('No'));
        $encryption_description = t('Your PHP installation does not have SSL enabled. See the !url page on php.net for more information. Gmail requires SSL.', array('!url' => l(t('OpenSSL Functions'), 'http://php.net/openssl')));
      }
      $form['email']['smtp_protocol'] = array(
        '#type'          => 'select',
        '#title'         => t('Use encrypted protocol'),
        '#default_value' => variable_get('smtp_protocol', 'standard'),
        '#options'       => $encryption_options,
        '#description'   => $encryption_description,
      );

    }

    // Google Analytics.
    $form['services'] = array(
      '#type' => 'fieldset',
      '#title' => t('Services'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    $form['services']['google_analytics_key'] = array(
      '#title' => t('Google Analytics Key'),
      '#type' => 'textfield',
      '#default_value' => variable_get('google_analytics_key', ''),
      '#description' => 'Google Analytics will be used if this key is provided. <em>Ex Key: "UA-1234567-89"</em>',
    );
    $form['services']['google_site_verification_key'] = array(
      '#title' => t('Google Site Verification Key'),
      '#type' => 'textfield',
      '#default_value' => variable_get('google_site_verification_key', ''),
      '#description' => 'Paste your meta tag code from Google Webmaster Tools here. After your site is confirmed with Google, we recommend you delete this key.',
    );
    return $form;
  }
}
