/**
 * This is JS specific to the dashboard page. Should not be added in other places because it alters
 * default drupal behaviors.
 */

$(document).ready(function() {
	coreContentDropdown();
    $('#ombudashboard-find-node #edit-submit').addClass('disabled').attr('disabled', 'disabled');
    $('#ombudashboard-find-node').submit(function(e) {

        e.preventDefault();
        var v = $('#edit-nid').val().match(/^\d+$/);
        if(v) {
            window.location = '/node/' + v + '/edit';
        }
        return false;
    });

});

function coreContentDropdown() {

	var types = $('#core-content-operations dt');
	// break if there's only one type
	if (types.length < 2) {
	    return;
	}
	var operations = $('#core-content-operations dd');
	var s = document.createElement('select');
	s.className = "form-select";
	addOption(s, 'null', '-- Choose a type of content --');
	types.each( function(i) {
		addOption(s, i, $(this).html());
	});

	types.hide();
	operations.hide().children('a').addClass('button');

	$('#core-content-operations').prepend(s);

	$(s).change(function(ev){

		var i = ev.target.value;
		operations.hide();
		if(i == 'null') return;
		$(operations[i]).show(); // using eq() was resulting in unexpected behavior
	});

	$('#core-content-operations').addClass('processed');

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
Drupal.jsAC.prototype.select = function (node) {
    this.input.value = node.autocompleteValue;
    this.setId(node.autocompleteId);
};

Drupal.jsAC.prototype.hidePopup = function (keycode) {

    if(this.selected) {
        $('#ombudashboard-find-node #edit-submit').removeClass('disabled').removeAttr('disabled');
    }
    else {
        $('#ombudashboard-find-node #edit-submit').addClass('disabled').attr('disabled', 'disabled');
    }

    // Select item if the right key or mousebutton was pressed
    if (this.selected && ((keycode && keycode != 46 && keycode != 8 && keycode != 27) || !keycode)) {
        this.input.value = this.selected.autocompleteValue;
        this.setId(this.selected.autocompleteId);
    }
    // Hide popup
    var popup = this.popup;
    if (popup) {
        this.popup = null;
        $(popup).fadeOut('fast', function() { $(popup).remove(); });
    }
    this.selected = false;
};

Drupal.jsAC.prototype.found = function (matches) {
    // If no value in the textfield, do not show the popup.
    if (!this.input.value.length) {
        return false;
    }
    // Prepare matches
    var ul = document.createElement('ul');
    var ac = this;
    for (key in matches) {
        var li = document.createElement('li');
        $(li)
            .html('<div>'+ matches[key] +'</div>')
            .mousedown(function () { ac.select(this); })
            .mouseover(function () { ac.highlight(this); })
            .mouseout(function () { ac.unhighlight(this); });
        li.autocompleteValue = matches[key];
        li.autocompleteId = key;
        $(ul).append(li);
    }

    // Show popup with matches, if any
    if (this.popup) {
        if (ul.childNodes.length > 0) {
            $(this.popup).empty().append(ul).show();
        }
        else {
            $(this.popup).css({visibility: 'hidden'});
            this.hidePopup();
        }
    }
};

Drupal.jsAC.prototype.setId = function (id) {
    if (typeof this.idField == 'undefined') {
        this.inputId = $('#edit-nid')[0];
    }
    this.inputId.value = id;
}

