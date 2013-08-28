<?php

$view = new view;
$view->name = 'manage_content';
$view->description = 'View, edit and delete your site\'s content.';
$view->tag = '';
$view->base_table = 'node';
$view->human_name = '';
$view->core = 0;
$view->api_version = '3.0-alpha1';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Defaults */
$handler = $view->new_display('default', 'Defaults', 'default');
$handler->display->display_options['title'] = 'Manage Content';
$handler->display->display_options['access']['type'] = 'perm';
$handler->display->display_options['access']['perm'] = 'administer nodes';
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['query']['options']['query_comment'] = FALSE;
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['pager']['type'] = 'full';
$handler->display->display_options['pager']['options']['items_per_page'] = 35;
$handler->display->display_options['style_plugin'] = 'table';
/* No results behavior: Global: Text area */
$handler->display->display_options['empty']['text']['id'] = 'area';
$handler->display->display_options['empty']['text']['table'] = 'views';
$handler->display->display_options['empty']['text']['field'] = 'area';
$handler->display->display_options['empty']['text']['empty'] = FALSE;
$handler->display->display_options['empty']['text']['content'] = 'There are no objects satisfying the filter settings. Try changing them to get some results.';
$handler->display->display_options['empty']['text']['format'] = '1';
/* Field: Content: Bulk */
$handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
$handler->display->display_options['fields']['views_bulk_operations']['table'] = 'node';
$handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
$handler->display->display_options['fields']['views_bulk_operations']['label'] = '';
$handler->display->display_options['fields']['views_bulk_operations']['alter']['alter_text'] = 0;
$handler->display->display_options['fields']['views_bulk_operations']['alter']['make_link'] = 0;
$handler->display->display_options['fields']['views_bulk_operations']['alter']['absolute'] = 0;
$handler->display->display_options['fields']['views_bulk_operations']['alter']['external'] = 0;
$handler->display->display_options['fields']['views_bulk_operations']['alter']['replace_spaces'] = 0;
$handler->display->display_options['fields']['views_bulk_operations']['alter']['trim_whitespace'] = 0;
$handler->display->display_options['fields']['views_bulk_operations']['alter']['nl2br'] = 0;
$handler->display->display_options['fields']['views_bulk_operations']['alter']['word_boundary'] = 1;
$handler->display->display_options['fields']['views_bulk_operations']['alter']['ellipsis'] = 1;
$handler->display->display_options['fields']['views_bulk_operations']['alter']['strip_tags'] = 0;
$handler->display->display_options['fields']['views_bulk_operations']['alter']['trim'] = 0;
$handler->display->display_options['fields']['views_bulk_operations']['alter']['html'] = 0;
$handler->display->display_options['fields']['views_bulk_operations']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['views_bulk_operations']['element_default_classes'] = 1;
$handler->display->display_options['fields']['views_bulk_operations']['hide_empty'] = 0;
$handler->display->display_options['fields']['views_bulk_operations']['empty_zero'] = 0;
$handler->display->display_options['fields']['views_bulk_operations']['hide_alter_empty'] = 0;
$handler->display->display_options['fields']['views_bulk_operations']['vbo']['entity_load_capacity'] = '10';
$handler->display->display_options['fields']['views_bulk_operations']['vbo']['operations'] = array(
  'node_assign_owner_action' => array(
    'selected' => 0,
    'use_queue' => 0,
    'skip_confirmation' => 0,
    'override_label' => 1,
    'label' => '',
  ),
  'views_bulk_operations_delete_item' => array(
    'selected' => 1,
    'use_queue' => 0,
    'skip_confirmation' => 0,
    'override_label' => 0,
    'label' => '',
  ),
  'system_message_action' => array(
    'selected' => 0,
    'use_queue' => 0,
    'skip_confirmation' => 0,
    'override_label' => 1,
    'label' => '',
  ),
  'views_bulk_operations_script_action' => array(
    'selected' => 0,
    'use_queue' => 0,
    'skip_confirmation' => 0,
    'override_label' => 1,
    'label' => '',
  ),
  'node_make_sticky_action' => array(
    'selected' => 0,
    'use_queue' => 0,
    'skip_confirmation' => 0,
    'override_label' => 1,
    'label' => '',
  ),
  'node_make_unsticky_action' => array(
    'selected' => 0,
    'use_queue' => 0,
    'skip_confirmation' => 0,
    'override_label' => 1,
    'label' => '',
  ),
  'views_bulk_operations_argument_selector_action' => array(
    'selected' => 0,
    'skip_confirmation' => 0,
    'override_label' => 1,
    'label' => '',
  ),
  'node_promote_action' => array(
    'selected' => 0,
    'use_queue' => 0,
    'skip_confirmation' => 0,
    'override_label' => 1,
    'label' => '',
  ),
  'node_publish_action' => array(
    'selected' => 1,
    'use_queue' => 0,
    'skip_confirmation' => 0,
    'override_label' => 1,
    'label' => '',
  ),
  'system_goto_action' => array(
    'selected' => 0,
    'use_queue' => 0,
    'skip_confirmation' => 0,
    'override_label' => 1,
    'label' => '',
  ),
  'node_unpromote_action' => array(
    'selected' => 0,
    'use_queue' => 0,
    'skip_confirmation' => 0,
    'override_label' => 1,
    'label' => '',
  ),
  'node_save_action' => array(
    'selected' => 0,
    'use_queue' => 0,
    'skip_confirmation' => 0,
    'override_label' => 1,
    'label' => '',
  ),
  'system_send_email_action' => array(
    'selected' => 0,
    'use_queue' => 0,
    'skip_confirmation' => 0,
    'override_label' => 1,
    'label' => '',
  ),
  'node_unpublish_action' => array(
    'selected' => 1,
    'use_queue' => 0,
    'skip_confirmation' => 0,
    'override_label' => 1,
    'label' => '',
  ),
  'node_unpublish_by_keyword_action' => array(
    'selected' => 0,
    'use_queue' => 0,
    'skip_confirmation' => 0,
    'override_label' => 1,
    'label' => '',
  ),
);
$handler->display->display_options['fields']['views_bulk_operations']['vbo']['display_type'] = '0';
$handler->display->display_options['fields']['views_bulk_operations']['vbo']['display_result'] = 1;
$handler->display->display_options['fields']['views_bulk_operations']['vbo']['merge_single_action'] = 0;
$handler->display->display_options['fields']['views_bulk_operations']['vbo']['force_single'] = 0;
/* Field: Content: Title */
$handler->display->display_options['fields']['title']['id'] = 'title';
$handler->display->display_options['fields']['title']['table'] = 'node';
$handler->display->display_options['fields']['title']['field'] = 'title';
$handler->display->display_options['fields']['title']['link_to_node'] = 1;
/* Field: Content: Type */
$handler->display->display_options['fields']['type']['id'] = 'type';
$handler->display->display_options['fields']['type']['table'] = 'node';
$handler->display->display_options['fields']['type']['field'] = 'type';
$handler->display->display_options['fields']['type']['exclude'] = TRUE;
$handler->display->display_options['fields']['type']['alter']['alter_text'] = 0;
$handler->display->display_options['fields']['type']['alter']['make_link'] = 0;
$handler->display->display_options['fields']['type']['alter']['word_boundary'] = 1;
$handler->display->display_options['fields']['type']['alter']['ellipsis'] = 1;
$handler->display->display_options['fields']['type']['alter']['strip_tags'] = 0;
$handler->display->display_options['fields']['type']['alter']['trim'] = 0;
$handler->display->display_options['fields']['type']['alter']['html'] = 0;
$handler->display->display_options['fields']['type']['hide_empty'] = 0;
$handler->display->display_options['fields']['type']['empty_zero'] = 0;
$handler->display->display_options['fields']['type']['link_to_node'] = 0;
$handler->display->display_options['fields']['type']['machine_name'] = 0;
/* Field: Content: Published */
$handler->display->display_options['fields']['status']['id'] = 'status';
$handler->display->display_options['fields']['status']['table'] = 'node';
$handler->display->display_options['fields']['status']['field'] = 'status';
$handler->display->display_options['fields']['status']['not'] = 0;
/* Field: Content: Edit link */
$handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
$handler->display->display_options['fields']['edit_node']['table'] = 'node';
$handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
$handler->display->display_options['fields']['edit_node']['label'] = '';
/* Sort criterion: Content: Updated date */
$handler->display->display_options['sorts']['changed']['id'] = 'changed';
$handler->display->display_options['sorts']['changed']['table'] = 'node';
$handler->display->display_options['sorts']['changed']['field'] = 'changed';
$handler->display->display_options['sorts']['changed']['order'] = 'DESC';
/* Contextual filter: Content: Type */
$handler->display->display_options['arguments']['type']['id'] = 'type';
$handler->display->display_options['arguments']['type']['table'] = 'node';
$handler->display->display_options['arguments']['type']['field'] = 'type';
$handler->display->display_options['arguments']['type']['exception']['title_enable'] = 1;
$handler->display->display_options['arguments']['type']['title_enable'] = 1;
$handler->display->display_options['arguments']['type']['title'] = 'Manage %1 Content';
$handler->display->display_options['arguments']['type']['default_argument_type'] = 'fixed';
$handler->display->display_options['arguments']['type']['default_argument_skip_url'] = 0;
$handler->display->display_options['arguments']['type']['summary']['number_of_records'] = '0';
$handler->display->display_options['arguments']['type']['summary']['format'] = 'default_summary';
$handler->display->display_options['arguments']['type']['summary_options']['items_per_page'] = '25';
$handler->display->display_options['arguments']['type']['specify_validation'] = 1;
/* Filter criterion: Content: Title */
$handler->display->display_options['filters']['title']['id'] = 'title';
$handler->display->display_options['filters']['title']['table'] = 'node';
$handler->display->display_options['filters']['title']['field'] = 'title';
$handler->display->display_options['filters']['title']['operator'] = 'contains';
$handler->display->display_options['filters']['title']['exposed'] = TRUE;
$handler->display->display_options['filters']['title']['expose']['operator_id'] = 'title_op';
$handler->display->display_options['filters']['title']['expose']['label'] = 'Title contains';
$handler->display->display_options['filters']['title']['expose']['operator'] = 'title_op';
$handler->display->display_options['filters']['title']['expose']['identifier'] = 'title';
/* Filter criterion: Content: Published */
$handler->display->display_options['filters']['status']['id'] = 'status';
$handler->display->display_options['filters']['status']['table'] = 'node';
$handler->display->display_options['filters']['status']['field'] = 'status';
$handler->display->display_options['filters']['status']['value'] = 'All';
$handler->display->display_options['filters']['status']['exposed'] = TRUE;
$handler->display->display_options['filters']['status']['expose']['label'] = 'Published';
$handler->display->display_options['filters']['status']['expose']['identifier'] = 'status';
$handler->display->display_options['filters']['status']['expose']['required'] = FALSE;

/* Display: Page */
$handler = $view->new_display('page', 'Page', 'page');
$handler->display->display_options['path'] = 'admin/dashboard/manage-content';

/**
  * Generate view displays for node types grouped with ombulayouts
  */
if (module_exists('ombulayouts')) {
  foreach (variable_get('ombulayouts', array()) as $type) {
    if (empty($type)) {
      continue;
    }
    $node_types = array();
    foreach (ombulayouts_node_types_for_root($type) as $node_type) {
      $node_types[$node_type->type] = $node_type->type;
    }
    $handler = $view->new_display('page', 'Page for ombulayouts group: ' . $type, 'page_type_group_' . $type);
    $handler->override_option('fields', array(
      'title' => array(
        'label' => 'Title',
        'link_to_node' => 1,
        'exclude' => 0,
        'id' => 'title',
        'table' => 'node',
        'field' => 'title',
        'relationship' => 'none',
        'override' => array(
          'button' => 'Override',
        ),
      ),
      'type' => array(
        'label' => 'Layout',
        'alter' => array(
          'alter_text' => 0,
          'text' => '',
          'make_link' => 0,
          'path' => '',
          'link_class' => '',
          'alt' => '',
          'prefix' => '',
          'suffix' => '',
          'target' => '',
          'help' => '',
          'trim' => 0,
          'max_length' => '',
          'word_boundary' => 1,
          'ellipsis' => 1,
          'html' => 0,
          'strip_tags' => 0,
        ),
        'empty' => '',
        'hide_empty' => 0,
        'empty_zero' => 0,
        'link_to_node' => 0,
        'machine_name' => 0,
        'exclude' => 0,
        'id' => 'type',
        'table' => 'node',
        'field' => 'type',
        'override' => array(
          'button' => 'Use default',
        ),
        'relationship' => 'none',
      ),
      'status' => array(
        'label' => 'Published',
        'type' => 'yes-no',
        'not' => 0,
        'exclude' => 0,
        'id' => 'status',
        'table' => 'node',
        'field' => 'status',
        'override' => array(
          'button' => 'Override',
        ),
        'relationship' => 'none',
      ),
      'edit_node' => array(
        'label' => 'Edit',
        'text' => '',
        'exclude' => 0,
        'id' => 'edit_node',
        'table' => 'node',
        'field' => 'edit_node',
        'override' => array(
          'button' => 'Override',
        ),
        'relationship' => 'none',
      ),
    ));
    $handler->override_option('path', 'admin/dashboard/manage-content/' . $type);
    $handler->override_option('menu', array(
      'type' => 'none',
      'title' => '',
      'description' => '',
      'weight' => 0,
      'name' => 'navigation',
    ));
    $handler->override_option('tab_options', array(
      'type' => 'none',
      'title' => '',
      'description' => '',
      'weight' => 0,
      'name' => 'navigation',
    ));
    $handler->override_option('arguments', array());
    $handler->override_option('filters', array(
      'title' => array(
        'operator' => 'contains',
        'value' => '',
        'group' => '0',
        'exposed' => TRUE,
        'expose' => array(
          'use_operator' => 0,
          'operator' => 'title_op',
          'identifier' => 'title',
          'label' => 'Title contains',
          'optional' => 1,
          'remember' => 0,
        ),
        'case' => 0,
        'id' => 'title',
        'table' => 'node',
        'field' => 'title',
        'override' => array(
          'button' => 'Override',
        ),
        'relationship' => 'none',
      ),
      'status' => array(
        'operator' => '=',
        'value' => 'All',
        'group' => '0',
        'exposed' => TRUE,
        'expose' => array(
          'operator' => '',
          'identifier' => 'status',
          'label' => 'Published',
          'optional' => 1,
          'remember' => 0,
        ),
        'id' => 'status',
        'table' => 'node',
        'field' => 'status',
        'override' => array(
          'button' => 'Override',
        ),
        'relationship' => 'none',
      ),
      'type' => array(
        'operator' => 'in',
        'value' => $node_types,
        'group' => '0',
        'exposed' => FALSE,
        'expose' => array(
          'operator' => 'type_op',
          'label' => 'Type',
          'use_operator' => 0,
          'identifier' => 'type',
          'optional' => 1,
          'single' => 0,
          'remember' => 0,
          'reduce' => 0,
        ),
        'id' => 'type',
        'table' => 'node',
        'field' => 'type',
        'override' => array(
          'button' => 'Use default',
        ),
        'relationship' => 'none',
      ),
    ));
  }
}
