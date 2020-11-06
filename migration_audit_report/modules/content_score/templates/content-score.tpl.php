<?php

/**
 * @file
 * Theme implementation for content score.
 */
if ($search_text) : ?>
  <?php $total_score = 0; ?>
  <?php foreach ($search_text as $field) : ?>
    <?php foreach ($field['data'] as $field_name => $field_value) : ?>
     <?php if(isset($field_value['data'])) { ?>
      <?php $total_score = $total_score + $field_value['score']; ?>
     <?php } ?>
    <?php endforeach; ?>
  <?php endforeach; ?>
  <div class='score'>
    <p><strong><?php print 'Total Content Score: ' . $total_score; ?></strong></p>
  </div>
  <!--Horizontal Tab-->
  <div id="content-score-main">
    <ul class="resp-tabs-list hor_1">
      <?php foreach ($search_text as $field) : ?>
        <li><label>Field name : <?php print $field['label']; ?></label></li>
      <?php endforeach; ?>
    </ul>

    <?php foreach ($search_text as $field) : ?>
      <div class="resp-tabs-container hor_1">
        <div>
          <!--vertical Tabs-->
          <div class="score-container">
            <ul class="resp-tabs-list ver_1">
              <?php foreach ($field['data'] as $item) : ?>
                <li><?php print $item['message']; ?>(Score - <?php print $item['score']; ?>)</li>
              <?php endforeach; ?>
            </ul>
            <div class="resp-tabs-container ver_1">
              <?php foreach ($field['data'] as $item) : ?>
                <?php if(isset($item['data'])) { ?>
                  <div>
                    <?php foreach ($item['data'] as $value) : ?>
                      <pre><?php print $value; ?></pre>
                    <?php endforeach; ?>
                <?php } ?>
                  </div>
              <?php endforeach; ?>
              </div>
            </div>
          </div>
        </div>
    <?php endforeach; ?>
    </div>
    <?php else : ?>
      <h2>Content looks correct.</h2>
    <?php endif; ?>
