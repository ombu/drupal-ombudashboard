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
        $('#toolbar').show();

        // Initial collapsed/expanded State
        if ( Drupal.settings.frontend && Drupal.dashboardToolbar.util.readCookie('dashboardToolbar.collapsed') == 1 ) {
            $('.toolbar-collapsed-items').css('display', 'block');
            $(window).trigger('toolbar.close', {init: true});
        } else {
            $('.toolbar-expanded-items').css('display', 'block');
            $(window).trigger('toolbar.open', {init: true});
            $('html').addClass('dashboardToolbar');
        }

        if (Drupal.settings.backend) {
            $('#toolbar .toolbar-collapse-button').hide();
        }

        // Set Drawer close timer on toolbar hover
        $('#toolbar:not(.toolbar-hover-processed)')
            .hover(
                Drupal.dashboardToolbar.cancelDrawerTimer,
                Drupal.dashboardToolbar.startDrawerTimer
            )
            .addClass('toolbar-hover-processed');

        // Open Drawer when a toolbar link with corresponding drawer is hovered
        //   (known by .drawer-link class)
        $('.toolbar-menu .drawer-link:not(.drawer-link-processed)')
            .hover(
                Drupal.dashboardToolbar.openDrawer,
                function(e) {}
            )
            .addClass('drawer-link-processed');

        // Bind closeDrawer to the drawers' close button
        $('.toolbar-drawer .close-drawer:not(.drawer-close-processed)')
            .click( Drupal.dashboardToolbar.closeDrawer )
            .addClass('drawer-close-processed');

        // Bind Toolbar collapsed/expanded state to collapse/expand buttons
        $('.toolbar-collapse-button:not(.toolbar-collapse-processed), .toolbar-expand-button:not(.toolbar-collapse-processed)')
            .click( Drupal.dashboardToolbar.collapseToggle )
            .addClass('toolbar-collapse-processed');

        // Setup content management picker
        if ($('.toolbar-shortcuts .core-content').length > 0) {

            var items = $('.toolbar-shortcuts .core-content li');
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
                addOption(s, i, $('.operation-object', this).text().replace(':', ''));
                $('.operation-object', this).hide();
            });

            items.hide();

            $('<li class="leaf first operation-controller operations"></li>')
                .prependTo('.toolbar-shortcuts .core-content')
                .append(s);

            $(s)
                .change(function(ev){
                    var i = ev.target.value;
                    items.hide();
                    if(i == 'null') return;
                    $(items[i]).show();
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

        $('.toolbar-menu .drawer-link').blur();

        var id = $(this).focus().attr('href').split('#').pop();

        $('.toolbar-drawer .drawer')
            .hide()
            .filter('#'+id)
            .show();

        $('.toolbar-drawer .close-drawer').show();
        $(window).trigger('toolbar.drawerOpen');
    },

    closeDrawer: function(e) {

        if (e) { e.preventDefault(); }

        $('.toolbar-drawer .close-drawer').hide();
        $('.toolbar-drawer .drawer').slideUp(100);
        $('.toolbar-menu .drawer-link').blur();

        Drupal.dashboardToolbar.cancelDrawerTimer();
        $(window).unbind('click.dashboardToolbar');
        $(window).trigger('toolbar.drawerClose');
    },

    startDrawerTimer: function() {

        if (Drupal.dashboardToolbar.noTimer) {
            Drupal.dashboardToolbar.noTimer = false;
            return;
        }

        // Set Click handler
        $(window).bind('click.dashboardToolbar', Drupal.dashboardToolbar.clickHandler);

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

        if ( !$(e.target).hasParent('#toolbar') ) {

            Drupal.dashboardToolbar.closeDrawer();

        }
    },

    collapseToggle: function(e) {

        if (e) { e.preventDefault(); }

        // Collapse Toolbar
        if ( $('.toolbar-expanded-items').is(':visible') ) {

            $('.toolbar-expanded-items').slideUp(200, function() {

                $('.toolbar-collapsed-items').slideDown(200);
                $('html').removeClass('dashboardToolbar');
                $(window).trigger('toolbar.close', {init: false});

            });

            Drupal.dashboardToolbar.util.createCookie('dashboardToolbar.collapsed', 1);

        // Expand Toolbar
        } else {

            $('.toolbar-collapsed-items').slideUp(200, function() {

                $('.toolbar-expanded-items').slideDown(200);
                $('html').addClass('dashboardToolbar');
                $(window).trigger('toolbar.open', {init: false});

            });

            Drupal.dashboardToolbar.util.createCookie('dashboardToolbar.collapsed', 0);

        }

    },

    util: {

        createCookie: function(name, value ,days) {

            if (days) {
                var date = new Date();
                date.setTime(date.getTime()+(days*24*60*60*1000));
                var expires = "; expires="+date.toGMTString();
            }
            else var expires = "";
            document.cookie = name+"="+value+expires+"; path=/";

        },

        readCookie: function(name) {

            var nameEQ = name + "=";
            var ca = document.cookie.split(';');
            for(var i=0;i < ca.length;i++) {
                var c = ca[i];
                while (c.charAt(0)==' ') c = c.substring(1,c.length);
                if (c.indexOf(nameEQ) == 0) return c.substring(nameEQ.length,c.length);
            }
            return null;

        },

        eraseCookie: function(name) {

            Drupal.dashboardToolbar.util.createCookie(name,"",-1);

        }

    }

};


Drupal.behaviors.dashboardToolbar = function(context) {

    if ( $('#toolbar.dashboardToolbarProcessed').length > 0 ) { return; }

    Drupal.dashboardToolbar.init();

    $('#toolbar').addClass('dashboardToolbarProcessed');

}

/*
	* Test whether argument elements are parents
	* of the first matched element
	* @return boolean
	* @param objs
	* 	a jQuery selector, selection, element, or array of elements
*/
$.fn.hasParent = function(objs) {
	// ensure that objs is a jQuery array
	objs = $(objs); var found = false;
	$(this[0]).parents().andSelf().each(function() {
		if ($.inArray(this, objs) != -1) {
			found = true;
			return false; // stops the each...
		}
	});
	return found;
}
