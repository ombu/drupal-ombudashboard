/**
 * This is JS specific to the dashboard page.
 */

jQuery(document).ready(function() {
  coreContentDropdown();
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
    operations.css('display','none'); 
    if(i == 'null') return;
    jQuery(operations[i]).css('display','inline-block'); // using eq() was resulting in unexpected behavior
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
