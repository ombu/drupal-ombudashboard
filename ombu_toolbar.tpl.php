<?php
/**
 * @file
 * Render OMBU toolbar
 *
 */
?>
<div class="navbar navbar-inverse navbar-fixed-top overlay-displace-top">
    <div class="navbar-inner">
        <!-- <div class="container"> Needed when going to a responsive navbar -->
            <a class="btn btn-navbar" data-toggle="collapse" data-targe=".nav-collapse">
                <span class="icon-bar"></span>
                <span class="icon-bar"></span>
                <span class="icon-bar"></span>
            </a>
            <a href="/" class="brand">Menu</a>
            <div class="nav-collapse">
              <?php print render($menu) ?>
              <?php print render($drawer) ?>
            </div>
        <!-- </div> -->
    </div>
</div>
