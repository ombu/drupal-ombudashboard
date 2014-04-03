(function($) {
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
        this.$toolbar = $('#toolbar');
        this.$expandButton = $('.toolbar-expand-button', this.$toolbar);


        // Store the height
        this.$toolbar
          .css('top', '-999em')
          .show();
        var toolbarHeight = this.$toolbar.height();
        this.$toolbar.data('toolbarHeight', toolbarHeight);


        // Initial collapsed/expanded State
        if (Drupal.settings.frontend && $.cookie('dashboardToolbar.open') == 0) {
          this.toolbarClose(true);
        } else {
          this.toolbarOpen(true);
        }


        // Hide/show buttons based on front/back end
        if (Drupal.settings.backend) {
          $('.toolbar-collapse-button', this.$toolbar).hide();
        } else {
          $('.visit-site', this.$toolbar).hide();
        }


        // Bind Event Handlers, duh
        this.bindEventHandlers();
        this.resize();

        // Turn content links into a select list.
        this.initContentManagementPicker();

    },

    bindEventHandlers: function() {
      // Force dashboard link to open new page, instead of in overlay.
      $('a.dashboard', this.$toolbar).click(function() {
        document.location = this.href;
        return false;
      });

      // Set Drawer close timer on toolbar hover
      this.$toolbar
        .hover(
          Drupal.dashboardToolbar.cancelDrawerTimer,
          Drupal.dashboardToolbar.startDrawerTimer
        );

      // Open Drawer when a toolbar link with corresponding drawer is hovered
      //   (known by .drawer-link class)
      $('.toolbar-menu .drawer-link')
        .hover(
          Drupal.dashboardToolbar.openDrawer,
          function(e) {}
        );

      // Bind closeDrawer to the drawers' close button
      $('.toolbar-drawer .close-drawer')
        .click(Drupal.dashboardToolbar.closeDrawer);

      // Bind Toolbar collapsed/expanded state to collapse/expand buttons
      $('.toolbar-collapse-button', this.$toolbar)
        .click($.proxy(Drupal.dashboardToolbar.toolbarCloseClick, this));

      this.$expandButton
        .click($.proxy(Drupal.dashboardToolbar.toolbarOpenClick, this));

      $(window).resize(debounce($.proxy(Drupal.dashboardToolbar.resize, this)));
    },

    initContentManagementPicker: function() {
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
            s.id = "core-content-select";
            addOption(s, 'null', '- Choose a type of content -');
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

    toolbarOpenClick: function(e) {
      if (e) { e.preventDefault(); }
      this.toolbarOpen();
    },

    toolbarCloseClick: function(e) {
      if (e) { e.preventDefault(); }
      this.toolbarClose();
    },

    toolbarOpen: function(noAnimation) {
      var opts = {
            toolbar: {
              top: 0
            },
            html: {}
          };
      if (Drupal.settings.ombutoolbar.top_padding) {
        opts.html['padding-top'] = this.$toolbar.data('toolbarHeight')+'px';
      }
      if (noAnimation) {
        this.$toolbar.css(opts.toolbar);
        $('html').css(opts.html);
        this.$expandButton.hide();
      }
      else {
        this.$toolbar.animate(opts.toolbar, 'fast');
        $('html').animate(opts.html, 'fast');
        this.$expandButton.fadeOut('fast');
      }
      $(window).trigger('toolbar.open', {init: false});
      $.cookie('dashboardToolbar.open', 1, {path: '/'});
      $('html').addClass('toolbar-open');
    },

    toolbarClose: function(noAnimation) {
      var opts = {
            toolbar: {
              top: '-'+this.$toolbar.data('toolbarHeight')+'px'
            },
            html: {}
          };
      if (Drupal.settings.ombutoolbar.top_padding) {
        opts.html['padding-top'] = 0;
      }
      if (noAnimation) {
        this.$toolbar.css(opts.toolbar);
        $('html').css(opts.html);
        this.$expandButton.show();
      }
      else {
        $('html').animate(opts.html, 'fast');
        this.$toolbar.animate(opts.toolbar, 'fast');
        this.$expandButton.fadeIn('fast');
      }
      $(window).trigger('toolbar.close', {init: false});
      $.cookie('dashboardToolbar.open', 0, {path: '/'});
      $('html').removeClass('toolbar-open');
      this.closeDrawer();
    },

    resize: function() {

      // Retract the toolbar if the window is resized to less than the
      // smartphone landscape threshold, so that it will gracefully resume
      // accessibility if the window width is increased back to the desktop
      // threshold.  This accompanies styles in toolbar.css.
      if ($(window).outerWidth() <= 1024) {
        this.toolbarClose();
      }

      if (Drupal.settings.ombutoolbar.top_padding) {
        var toolbarHeight = this.$toolbar.height();
        this.$toolbar.data('toolbarHeight', toolbarHeight)

        if ($.cookie('dashboardToolbar.open') == 0) {
          this.$toolbar.css('top', '-' + toolbarHeight + 'px');
        }
        else {
          $('html').css('padding-top', toolbarHeight+'px');
        }
      }
    }

};


Drupal.behaviors.dashboardToolbar = {
  attach: function(context) {
    if ( $('#toolbar.dashboardToolbarProcessed').length > 0 ) { return; }

    Drupal.dashboardToolbar.init();

    $('#toolbar').addClass('dashboardToolbarProcessed');
  }
};

function debounce(func, threshold, execAsap) {
  var timeout;

  return function debounced () {
    var obj = this, args = arguments;
    function delayed () {
      if (!execAsap) {
        func.apply(obj, args);
      }
      timeout = null;
    };

    if (timeout) {
      clearTimeout(timeout);
    }
    else if (execAsap) {
      func.apply(obj, args);
    }

    timeout = setTimeout(delayed, threshold || 100);
  };
}

})(jQuery);

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
