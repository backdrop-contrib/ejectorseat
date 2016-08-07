/**
 * @file
 * Ejector seat Javascript functions.
 *
 * Poll a Backdrop site via AJAX at a specified interval to determine if the user
 * currently accessing the site still has an active session and reload the page
 * if they don not. Effectively logging the user out of the site.
 */
(function ($) {

  Backdrop.behaviors.ejectorseat = {
    attach: function (context, settings) {
      Backdrop.ejectorSeat = {
        windowFocus: true,
        overdue: false
      };
      var ejectorInterval = settings.ejectorSeat.interval ? settings.ejectorSeat.interval * 1000 : 60000;
      var intervalId;
      $(window)
        .blur(function(){
          Backdrop.ejectorSeat.windowFocus = false;
        })
        .focus(function(){
          Backdrop.ejectorSeat.windowFocus = true;
          if (Backdrop.ejectorSeat.overdue) {
            Backdrop.ejectorSeat.overdue = false;
            ejectorCheck();
            restartTimer();
          }
        });

      function ejectorCheck() {
        var ignoreFocus = settings.ejectorSeat.ignoreFocus;
        
        if (Backdrop.ejectorSeat.windowFocus || ignoreFocus) {
          // Do the AJAX test.
          $.get(settings.ejectorSeat.url, function(data){
            // If the test returns 0 the user's session has ended so refresh the
            // page.
            if (data === '0') {
              window.location.reload(true);
            }
          });
        }
        else {
          Backdrop.ejectorSeat.overdue = true;
        }
      }

      function startTimer() {
        intervalId = setInterval(ejectorCheck, ejectorInterval);
      }

      function restartTimer() {
        clearInterval(intervalId);
        startTimer();
      }

      startTimer();
    }
  };

}(jQuery));
