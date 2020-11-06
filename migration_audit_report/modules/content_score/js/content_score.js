/**
 * @file
 * Content Score JS File.
 */

(function ($) {
  Drupal.behaviors.contentScore = {
    attach: function (context, settings) {
      var loc = window.location.href;
      $('.page-admin-reports-content-score .view-header a[href="' + loc + '"]').addClass("active");

      if (!$("body").hasClass('page-admin')) {
        if (!$('.score-container').hasClass('resp-vtabs')) {
          $('#content-score-main').easyResponsiveTabs({
            type: 'default', //Types: default, vertical, accordion
            width: 'auto', //auto or any width like 600px
            fit: true, // 100% fit in a container
            closed: 'accordion', // Start closed if in accordion view
            tabidentify: 'hor_1' // The tab groups identifier
          });
          $('.score-container').easyResponsiveTabs({
            type: 'vertical',
            width: 'auto',
            fit: true,
            tabidentify: 'ver_1', // The tab groups identifier
            activetab_bg: '#fff', // background color for active tabs in this group
            inactive_bg: '#F5F5F5', // background color for inactive tabs in this group
            active_border_color: '#5ab1d0', // border color for active tabs heads in this group
            active_content_border_color: '#5AB1D0' // border color for active tabs contect in this group so that it matches the tab head border
          });
        }
      }
    }
  };
}(jQuery));
