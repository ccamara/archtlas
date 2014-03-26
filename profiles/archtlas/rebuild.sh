#!/bin/bash
rm -rf modules/contrib
rm -rf themes/contrib
rm -rf libraries/ckeditor
drush make --working-copy --no-core --contrib-destination=. archtlas.make .
drush updatedb -y && drush cc all
