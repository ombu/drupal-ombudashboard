jQuery(document).ready(function() {
  jQuery('#ribbon').click(function(ev) {
    ev.preventDefault();
    var th = jQuery(this);
    if (th.hasClass('left')) {
      th.removeClass('left');
      th.addClass('right');
    }
    else if (th.hasClass('right')) {
      th.removeClass('right');
      th.addClass('left');
    }
  });
});
