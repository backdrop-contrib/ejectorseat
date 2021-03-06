Ejector Seat
============

Use Javascript (ajax) code to check periodically to see if a user is still logged in. If the user is NOT logged in, the current page is reloaded so that the user sees the page as an anonymous user.

This module will usually be used with either [Session Limit](https://github.com/backdrop-contrib/session_limit) or [Automated Logout](https://github.com/backdrop-contrib/autologout) in order to reload the current page for users who have been automatically logged out by logging in at another location.

Common use case: You have a private access website and you want to be sure that users are not sharing accounts. You can use Session Limit to ensure that each user can only be logged in from one location at a time. However, a user will not be logged out until they reload the page. Ejector Seat runs an ajax script on a configurable timer (every minute by default) to check to see if the user is still logged in. If they are not, the current page is reloaded and Session Limit displays a message telling the user that they have been logged out because someone else is using their account.

Another effect of this module is that if a user has multiple tabs open of the same Backdrop site, and they log out in one tab, they will be logged out in all tabs.

In order to improve performance, the ajax callback (and associated Backdrop bootstrap) only runs if the Backdrop page is in focus (the active front window). Once a window becomes active it will immediately do an ajax check if the script is overdue.

Current Maintainer
------------------

- None

Credits
-------

- Originally written for Drupal by Jeff Robbins (https://github.com/jjeff)
- Ported to Backdrop by David Norman (https://github.com/deekayen)

License
-------

This project is GPL v2 software. See the LICENSE.txt file in this directory for complete text.
