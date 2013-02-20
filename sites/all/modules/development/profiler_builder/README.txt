Profiler Builder
===========================================
Install this module and then go to:  admin/config/development/profiler_builder
Run through the form and hit download to get your installation profile and associated make file.  open the .make file and search for the word TODO.

If you don't find it then it didn't create with any errors and you are good to test out your distribution!

If you don't have the profiler library in your distribution / library files you'll want to download that from drupal.org/project/profiler and put it in your libraries folder of the distribution you are making so that /profiles/{newdistroname}/libraries/profiler exists.

Also there is a drush command so drush distro coolstuff --untar will automatically build the file structure in your profiles directory (if it has permission).