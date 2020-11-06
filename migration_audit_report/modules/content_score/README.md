content_score
=========================

Content Score Card Module

Description:
------------

This module helps to identify the hard-coded tags i.e. `<img>`, `<script>`
and `<style>` / `<link>` which are being used on the market level
contents / blocks. The module will calculate the score of all the
contents / blocks which are having above mentioned hard-coded tags.

Content Score Calculation:
--------------------------

 * One `<img>` tag will get 4 points.
 * One `<script>` tag will get 5 points.
 * One `<style>` / `<link>` tags which are considered as a CSS tags
will get 6 points.

On the basis of the above points each content / block will get a score.
The highest score will be considered as a poorest quality content.
To make the high quality / standard contents the score of it must be
as low as possible. If the content has no score / 0 score will be
qualified / marked as a good quality content.

Installation Instructions:
--------------------------

 * Enable the module.
 * Go to Administration > Configuration > Development > Performance
and clear the cache.
 * After that go to Administration > Reports > Content Score menu.
 * Content score page will come up with 2 tabs including the default page tab.
 * Go to the 'Score Refresh' tab page and click on the 'score refresh' button
which will perform the calculation on all the contents / blocks which are
present on the website. This is a one-time activity.
 * After doing above step all the contents with score will come up as
a detailed list on the main page of the module. Also this detailed list is
exportable as a .csv file.
 * Red Flag Score: above 200 | Yellow Flag Score: between 100 and 200 |
Green Flag Score: less than or equal to 100.
 * Any NEW / EDITED / DELETED content / block will be automatically calculated
to get its best suited score after doing all the above steps.
