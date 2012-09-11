/**
 * This is JS specific to the dashboard page. Should not be added in other places because it alters
 * default drupal behaviors.
 */

jQuery(document).ready(function() {
	coreContentDropdown();
    jQuery('#ombudashboard-find-node #edit-submit').addClass('disabled').attr('disabled', 'disabled');
    jQuery('#ombudashboard-find-node').submit(function(e) {
        e.preventDefault();
        var v = jQuery('#ombudashboard-find-node input[name="nid"]').val().match(/^\d+$/);
        if(v) {
            window.location = '/node/' + v + '/edit';
        }
        return false;
    });

});

function coreContentDropdown() {

	var types = jQuery('#core-content-operations dt');
	// break if there's only one type
	if (types.length < 2) {
	    return;
	}
	var operations = jQuery('#core-content-operations dd');
	var s = document.createElement('select');
	s.className = "form-select";
	addOption(s, 'null', '- Choose a type of content -');
	types.each( function(i) {
		addOption(s, i, jQuery(this).html());
	});

	types.hide();
	operations.hide().children('a').addClass('btn');

	jQuery('#core-content-operations').prepend(s);

	jQuery(s).change(function(ev){

		var i = ev.target.value;
		operations.hide();
		if(i == 'null') return;
		jQuery(operations[i]).show(); // using eq() was resulting in unexpected behavior
	});

	jQuery('#core-content-operations').addClass('processed');

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
}

/**
 * Autocomplete overrides to allow selecting & viewing node title and saving the node ID on a hidden field.
 * NOTE: This can break other autocompletes. SHOULD ONLY BE USED ON THE DASHBOARD PAGE
 */
if (Drupal.jsAC) {
    Drupal.jsAC.prototype.hidePopup = function (keycode) {
      if(this.selected) {
          jQuery('#ombudashboard-find-node #edit-submit').removeClass('disabled').removeAttr('disabled');
      }
      else {
          jQuery('#ombudashboard-find-node #edit-submit').addClass('disabled').attr('disabled', 'disabled');
      }
      // Select item if the right key or mousebutton was pressed.
      if (this.selected && ((keycode && keycode != 46 && keycode != 8 && keycode != 27) || !keycode)) {
        var nid = jQuery(this.selected).data('autocompleteValue');
        var title = jQuery(this.selected).data('autocompleteValueTitle');
        jQuery(this.input).val(title);
        jQuery('#ombudashboard-find-node input[name="nid"]').val(nid); // Sets the hidden input

      }
      // Hide popup.
      var popup = this.popup;
      if (popup) {
        this.popup = null;
        jQuery(popup).fadeOut('fast', function () {jQuery(popup).remove();});
      }
      this.selected = false;
      jQuery(this.ariaLive).empty();
    };

    Drupal.jsAC.prototype.found = function (matches) {
        // If no value in the textfield, do not show the popup.
        if (!this.input.value.length) {
          return false;
      }

      // Prepare matches.
      var ul = jQuery('<ul></ul>');
      var ac = this;
      for (key in matches) {
        jQuery('<li></li>')
          .html(jQuery('<div></div>').html(matches[key]))
          .mousedown(function () { ac.select(this); })
          .mouseover(function () { ac.highlight(this); })
          .mouseout(function () { ac.unhighlight(this); })
          .data('autocompleteValue', key)
          .data('autocompleteValueTitle', matches[key])
          .appendTo(ul);
      }

      // Show popup with matches, if any.
      if (this.popup) {
        if (ul.children().size()) {
          jQuery(this.popup).empty().append(ul).show();
          jQuery(this.ariaLive).html(Drupal.t('Autocomplete popup'));
        }
        else {
          jQuery(this.popup).css({ visibility: 'hidden' });
          this.hidePopup();
        }
      }
    };
}