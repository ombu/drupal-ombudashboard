//----------------------------------------------------------------------------//
// Drupal Dashboard Toolbar
//
// Provides open/close functionality for the Toolbar
//
// Custom events fired:
//     - toolbar.open: Toolbar goes from collapsed to expanded state
//     - toolbar.close: Toolbar goes from expanded to collapsed state
//     - toolbar.drawerOpen: Toolbar's second-level opens
//     - toolbar.drawerClose: Toolbar's second-level closes
// The second argument passed when an event is fired is a data object that contains:
//     - init: true, if the toolbar is opening for the first time on page load
//----------------------------------------------------------------------------//
Drupal.dashboardToolbar = {

    noTimer: false,

    init: function() {

        // Show toolbar div
        // Was hidden to avoid a flash of it unstyled
        jQuery('#toolbar').show();

        // Initial collapsed/expanded State
        if ( Drupal.settings.frontend && jQuery.cookie('dashboardToolbar.collapsed') == 1 ) {
            jQuery('.toolbar-collapsed-items').css('display', 'block');
            jQuery(window).trigger('toolbar.close', {init: true});
        } else {
            jQuery('.toolbar-expanded-items').css('display', 'block');
            jQuery(window).trigger('toolbar.open', {init: true});
            jQuery('html').addClass('dashboardToolbar');
        }

        if (Drupal.settings.backend) {
            jQuery('#toolbar .toolbar-collapse-button').hide();
        } else {
            jQuery('#toolbar .visit-site').hide();
        }

        // Force dashboard link to open new page, instead of in overlay.
        jQuery('#toolbar a.dashboard').click(function() {
          document.location = this.href;
          return false;
        });

        // Set Drawer close timer on toolbar hover
        jQuery('#toolbar:not(.toolbar-hover-processed)')
            .hover(
                Drupal.dashboardToolbar.cancelDrawerTimer,
                Drupal.dashboardToolbar.startDrawerTimer
            )
            .addClass('toolbar-hover-processed');

        // Open Drawer when a toolbar link with corresponding drawer is hovered
        //   (known by .drawer-link class)
        jQuery('.toolbar-menu .drawer-link:not(.drawer-link-processed)')
            .hover(
                Drupal.dashboardToolbar.openDrawer,
                function(e) {}
            )
            .addClass('drawer-link-processed');

        // Bind closeDrawer to the drawers' close button
        jQuery('.toolbar-drawer .close-drawer:not(.drawer-close-processed)')
            .click( Drupal.dashboardToolbar.closeDrawer )
            .addClass('drawer-close-processed');

        // Bind Toolbar collapsed/expanded state to collapse/expand buttons
        jQuery('.toolbar-collapse-button:not(.toolbar-collapse-processed), .toolbar-expand-button:not(.toolbar-collapse-processed)')
            .click( Drupal.dashboardToolbar.collapseToggle )
            .addClass('toolbar-collapse-processed');

        // Setup content management picker
        if (jQuery('.toolbar-shortcuts .core-content').length > 0) {

            var items = jQuery('.toolbar-shortcuts .core-content li');
            // break if there's only one
            if (items.length < 2) {
                return;
            }

            function addOption(parent, value, text) {
                var o = document.createElement('option');
                o.value = value;
                o.text = text;
                try {
                    parent.add(o, null); // standards compliant
                } catch (ex) {
                    parent.add(o); // IE only
                }
            }

            var s = document.createElement('select');
            s.className = "form-select";
            addOption(s, 'null', '-- Choose a type of content --');
            items.each( function(i) {
                addOption(s, i, jQuery('.operation-object', this).text().replace(':', ''));
                jQuery('.operation-object', this).hide();
            });

            items.hide();

            jQuery('<li class="leaf first operation-controller operations"></li>')
                .prependTo('.toolbar-shortcuts .core-content')
                .append(s);

            jQuery(s)
                .change(function(ev){
                    var i = ev.target.value;
                    items.hide();
                    if(i == 'null') return;
                    jQuery(items[i]).show();
                })
                .hover(
                    function(e) {
                        Drupal.dashboardToolbar.cancelDrawerTimer();
                        Drupal.dashboardToolbar.noTimer = true;
                    },
                    function(e) {

                    }
                );

        }
    },

    openDrawer: function(e) {

        jQuery('.toolbar-menu .drawer-link').blur();

        var id = jQuery(this).focus().attr('href').split('#').pop();

        jQuery('.toolbar-drawer .drawer')
            .hide()
            .filter('#'+id)
            .show();

        jQuery('.toolbar-drawer .close-drawer').show();
        jQuery(window).trigger('toolbar.drawerOpen');
    },

    closeDrawer: function(e) {

        if (e) { e.preventDefault(); }

        jQuery('.toolbar-drawer .close-drawer').hide();
        jQuery('.toolbar-drawer .drawer').slideUp(100);
        jQuery('.toolbar-menu .drawer-link').blur();

        Drupal.dashboardToolbar.cancelDrawerTimer();
        jQuery(window).unbind('click.dashboardToolbar');
        jQuery(window).trigger('toolbar.drawerClose');
    },

    startDrawerTimer: function() {

        if (Drupal.dashboardToolbar.noTimer) {
            Drupal.dashboardToolbar.noTimer = false;
            return;
        }

        // Set Click handler
        jQuery(window).bind('click.dashboardToolbar', Drupal.dashboardToolbar.clickHandler);

        // Start Timer
        Drupal.dashboardToolbar.closeDrawerTimer = setTimeout("Drupal.dashboardToolbar.closeDrawer()", 500);

    },

    cancelDrawerTimer: function() {

        if ( Drupal.dashboardToolbar.closeDrawerTimer ) {

            clearTimeout( Drupal.dashboardToolbar.closeDrawerTimer );
            delete Drupal.dashboardToolbar.closeDrawerTimer;

        }

    },

    clickHandler: function(e) {

        if ( !jQuery(e.target).hasParent('#toolbar') ) {

            Drupal.dashboardToolbar.closeDrawer();

        }
    },

    collapseToggle: function(e) {

        if (e) { e.preventDefault(); }

        // Collapse Toolbar
        if ( jQuery('.toolbar-expanded-items').is(':visible') ) {

            jQuery('.toolbar-expanded-items').slideUp(200, function() {

                jQuery('.toolbar-collapsed-items').slideDown(200);
                jQuery('html').removeClass('dashboardToolbar');
                jQuery(window).trigger('toolbar.close', {init: false});

            });

            jQuery.cookie('dashboardToolbar.collapsed', 1);

        // Expand Toolbar
        } else {
            jQuery('.toolbar-collapsed-items').slideUp(200, function() {

                jQuery('.toolbar-expanded-items').slideDown(200);
                jQuery('html').addClass('dashboardToolbar');
                jQuery(window).trigger('toolbar.open', {init: false});

            });

            jQuery.cookie('dashboardToolbar.collapsed', null);
        }
    }
};


Drupal.behaviors.dashboardToolbar = {
  attach: function(context) {
    if ( jQuery('#toolbar.dashboardToolbarProcessed').length > 0 ) { return; }

    Drupal.dashboardToolbar.init();

    jQuery('#toolbar').addClass('dashboardToolbarProcessed');
  }
};

/*
	* Test whether argument elements are parents
	* of the first matched element
	* @return boolean
	* @param objs
	* 	a jQuery selector, selection, element, or array of elements
*/
jQuery.fn.hasParent = function(objs) {
	// ensure that objs is a jQuery array
	objs = jQuery(objs); var found = false;
	jQuery(this[0]).parents().andSelf().each(function() {
		if (jQuery.inArray(this, objs) != -1) {
			found = true;
			return false; // stops the each...
		}
	});
	return found;
}
