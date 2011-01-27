<?php

/**
 * @todo Please document this function.
 * @see http://drupal.org/node/1354
 */
function ombudashboard_views_default_views() {

  $views = array();

  /***************************************************************************
   *  Manage Content
   **************************************************************************/
  $view = new view;
  $view->name = 'manage_content';
  $view->description = 'View, edit and delete your site\'s content.';
  $view->tag = '';
  $view->view_php = '';
  $view->base_table = 'node';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Defaults', 'default');
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
      'label' => 'Type',
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
      'exclude' => 1,
      'id' => 'type',
      'table' => 'node',
      'field' => 'type',
      'override' => array(
        'button' => 'Override',
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
      'label' => '',
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
  $handler->override_option('sorts', array(
    'changed' => array(
      'order' => 'DESC',
      'granularity' => 'second',
      'id' => 'changed',
      'table' => 'node',
      'field' => 'changed',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('arguments', array(
    'type' => array(
      'default_action' => 'ignore',
      'style_plugin' => 'default_summary',
      'style_options' => array(),
      'wildcard' => 'all',
      'wildcard_substitution' => 'All',
      'title' => '',
      'breadcrumb' => '',
      'default_argument_type' => 'fixed',
      'default_argument' => '',
      'validate_type' => 'none',
      'validate_fail' => 'not found',
      'id' => 'type',
      'table' => 'node',
      'field' => 'type',
      'validate_user_argument_type' => 'uid',
      'validate_user_roles' => array(
        '2' => 0,
        '3' => 0,
      ),
      'relationship' => 'none',
      'default_options_div_prefix' => '',
      'default_argument_user' => 0,
      'default_argument_fixed' => '',
      'default_argument_php' => '',
      'validate_argument_node_type' => array(
        'page' => 0,
        'pick' => 0,
        'picker' => 0,
        'portfolio' => 0,
      ),
      'validate_argument_node_access' => 0,
      'validate_argument_nid_type' => 'nid',
      'validate_argument_vocabulary' => array(
        '3' => 0,
        '2' => 0,
        '1' => 0,
      ),
      'validate_argument_type' => 'tid',
      'validate_argument_transform' => 0,
      'validate_user_restrict_roles' => 0,
      'validate_argument_php' => '',
    ),
  ));
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
  ));
  $handler->override_option('access', array(
    'type' => 'perm',
    'perm' => 'administer nodes',
  ));
  $handler->override_option('cache', array(
    'type' => 'none',
  ));
  $handler->override_option('title', 'Manage Content');
  $handler->override_option('empty', 'There are no objects satisfying the filter settings. Try changing them to get some results.');
  $handler->override_option('empty_format', '1');
  $handler->override_option('items_per_page', 35);
  $handler->override_option('use_pager', '1');
  $handler->override_option('style_plugin', 'bulk');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'override' => 1,
    'sticky' => 1,
    'order' => 'asc',
    'columns' => array(
      'title' => 'title',
      'type' => 'type',
      'status' => 'status',
      'edit_node' => 'edit_node',
    ),
    'info' => array(
      'title' => array(
        'sortable' => 1,
        'separator' => '&nbsp;',
      ),
      'type' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'status' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'edit_node' => array(
        'separator' => '',
      ),
    ),
    'default' => '-1',
    'execution_type' => '1',
    'display_type' => '0',
    'hide_select_all' => 0,
    'skip_confirmation' => 0,
    'display_result' => 1,
    'merge_single_action' => 0,
    'selected_operations' => array(
      'views_bulk_operations_delete_node_action' => 'views_bulk_operations_delete_node_action',
      'node_publish_action' => 'node_publish_action',
      'node_unpublish_action' => 'node_unpublish_action',
      'node_assign_owner_action' => 0,
      'node_mass_update:a27b9efabcd054685a549378b174ad11' => 0,
      'system_message_action' => 0,
      'views_bulk_operations_script_action' => 0,
      'node_export_node_bulk' => 0,
      'node_make_sticky_action' => 0,
      'node_make_unsticky_action' => 0,
      'node_mass_update:c4d3b28efb86fd703619a50b74d43794' => 0,
      'views_bulk_operations_fields_action' => 0,
      'views_bulk_operations_taxonomy_action' => 0,
      'views_bulk_operations_argument_selector_action' => 0,
      'node_promote_action' => 0,
      'node_mass_update:14de7d028b4bffdf2b4a266562ca18ac' => 0,
      'node_mass_update:9c585624b9b3af0b4687d5f97f35e047' => 0,
      'system_goto_action' => 0,
      'node_unpromote_action' => 0,
      'node_mass_update:8ce21b08bb8e773d10018b484fe4815e' => 0,
      'node_save_action' => 0,
      'system_send_email_action' => 0,
      'node_mass_update:0ccad85c1ebe4c9ceada1aa64293b080' => 0,
      'node_unpublish_by_keyword_action' => 0,
    ),
  ));
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->override_option('path', 'admin/dashboard/manage-content');
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

  $views[$view->name] = $view;



  $view = new view;
  $view->name = 'manage_users';
  $view->description = 'Manage Users';
  $view->tag = '';
  $view->view_php = '';
  $view->base_table = 'users';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('fields', array(
    'name' => array(
      'label' => 'Username',
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
      'link_to_user' => 1,
      'overwrite_anonymous' => 0,
      'anonymous_text' => '',
      'exclude' => 0,
      'id' => 'name',
      'table' => 'users',
      'field' => 'name',
      'relationship' => 'none',
    ),
    'status' => array(
      'label' => 'Active',
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
      'type' => 'yes-no',
      'not' => 0,
      'exclude' => 0,
      'id' => 'status',
      'table' => 'users',
      'field' => 'status',
      'relationship' => 'none',
    ),
    'rid' => array(
      'label' => 'Roles',
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
        'word_boundary' => 0,
        'ellipsis' => 0,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'type' => 'ul',
      'separator' => ', ',
      'exclude' => 0,
      'id' => 'rid',
      'table' => 'users_roles',
      'field' => 'rid',
      'relationship' => 'none',
    ),
    'created' => array(
      'label' => 'Member For',
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
        'word_boundary' => 0,
        'ellipsis' => 0,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'date_format' => 'raw time ago',
      'custom_date_format' => '',
      'exclude' => 0,
      'id' => 'created',
      'table' => 'users',
      'field' => 'created',
      'relationship' => 'none',
    ),
    'access' => array(
      'label' => 'Last Access',
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
        'word_boundary' => 0,
        'ellipsis' => 0,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'date_format' => 'raw time ago',
      'custom_date_format' => '',
      'exclude' => 0,
      'id' => 'access',
      'table' => 'users',
      'field' => 'access',
      'relationship' => 'none',
    ),
    'edit_node' => array(
      'label' => 'Operations',
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
        'word_boundary' => 0,
        'ellipsis' => 0,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'text' => '',
      'exclude' => 0,
      'id' => 'edit_node',
      'table' => 'users',
      'field' => 'edit_node',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('filters', array(
    'uid' => array(
      'operator' => 'in',
      'value' => '',
      'group' => '0',
      'exposed' => TRUE,
      'expose' => array(
        'use_operator' => 0,
        'operator' => 'uid_op',
        'identifier' => 'user',
        'label' => 'User:',
        'optional' => 1,
        'remember' => 0,
        'reduce' => 0,
      ),
      'id' => 'uid',
      'table' => 'users',
      'field' => 'uid',
      'relationship' => 'none',
    ),
    'uid_1' => array(
      'operator' => 'not in',
      'value' => array(
        '0' => 0,
        '1' => '1',
      ),
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => 'uid_1_op',
        'label' => 'User: Name',
        'use_operator' => FALSE,
        'identifier' => 'uid_1',
        'remember' => FALSE,
        'single' => TRUE,
        'optional' => TRUE,
        'reduce' => FALSE,
      ),
      'id' => 'uid_1',
      'table' => 'users',
      'field' => 'uid',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'perm',
    'perm' => 'administer users',
  ));
  $handler->override_option('cache', array(
    'type' => 'none',
  ));
  $handler->override_option('use_ajax', TRUE);
  $handler->override_option('items_per_page', 50);
  $handler->override_option('use_pager', '1');
  $handler->override_option('style_plugin', 'bulk');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'override' => 1,
    'sticky' => 1,
    'order' => 'desc',
    'columns' => array(
      'name' => 'name',
      'status' => 'status',
      'rid' => 'rid',
      'created' => 'created',
      'access' => 'access',
      'edit_node' => 'edit_node',
    ),
    'info' => array(
      'name' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'status' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'rid' => array(
        'separator' => '',
      ),
      'created' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'access' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'edit_node' => array(
        'separator' => '',
      ),
    ),
    'default' => 'created',
    'execution_type' => '1',
    'display_type' => '0',
    'hide_select_all' => 0,
    'skip_confirmation' => 0,
    'display_result' => 1,
    'merge_single_action' => 1,
    'selected_operations' => array(
      'user_user_operations_block' => 'user_user_operations_block',
      'views_bulk_operations_delete_user_action' => 'views_bulk_operations_delete_user_action',
      'evosus_user_add_video_access_action' => 'evosus_user_add_video_access_action',
      'evosus_user_remove_video_access_action' => 'evosus_user_remove_video_access_action',
      'user_user_operations_unblock' => 'user_user_operations_unblock',
      'user_block_ip_action' => 0,
      'user_block_user_action' => 0,
      'system_message_action' => 0,
      'views_bulk_operations_action' => 0,
      'views_bulk_operations_script_action' => 0,
      'views_bulk_operations_profile_action' => 0,
      'views_bulk_operations_user_roles_action' => 0,
      'views_bulk_operations_argument_selector_action' => 0,
      'system_goto_action' => 0,
      'system_send_email_action' => 0,
    ),
  ));
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->override_option('title', 'Users');
  $handler->override_option('header_format', '3');
  $handler->override_option('header_empty', 0);
  $handler->override_option('footer', '<a href="/admin/user/user/create">Add User</a>');
  $handler->override_option('footer_format', '3');
  $handler->override_option('footer_empty', 0);
  $handler->override_option('path', 'admin/dashboard/manage-users');
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


  $views[$view->name] = $view;


  return $views;
}
