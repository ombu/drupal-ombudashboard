<?php
/**
 * @file
 * Render OMBU toolbar
 *
 */
?>
<div id="toolbar" class="toolbar overlay-displace-top clearfix toolbar-processed" style="display: none;">
    <div class="toolbar-expanded-items clearfix">
        <div class="toolbar-menu clearfix">
          <?php print render($menu) ?>
        </div>
        <div class="toolbar-drawer clearfix">
            <div class="toolbar-shortcuts">
              <?php print render($drawer) ?>
            </div>
            <a href="#close" class="close-drawer">&otimes;</a>
        </div>
        <div class="shadow"></div>
    </div>
    <a class="toolbar-expand-button" title="Expand Toolbar" href="<?php print $curr_path ?>">&equiv;</a>
</div>
