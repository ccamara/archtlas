; ArchTLAS make file
core = "7.x"
api = "2"

;CORE
projects[drupal][type] = core
projects[drupal][version] = 7.26

; MODULES
;projects[context][version] = 3.1
;projects[context][subdir] = contrib

projects[ckeditor][version] = 1.13
projects[ckeditor][subdir] = contrib

projects[ctools][version] = 1.4
projects[ctools][subdir] =  contrib

projects[date][version] = 2.7
projects[date][subdir] =  contrib

projects[ds][version] = 2.6
projects[ds][subdir] =  contrib

projects[entity][version] = 1.2
projects[entity][subdir] =   contrib

projects[features][version] = 2.0
projects[features][subdir] =  contrib
projects[features][patch][766264] = http://drupal.org/files/766264-25-alter-override.patch

projects[getlocations][version] = 1.12
projects[getlocations][subdir] = contrib

projects[l10n_update][download][type] = git
projects[l10n_update][download][url] = git://drupalcode.org/project/l10n_update.git
projects[l10n_update][download][revision] = 20a80d1487dce4afad8b8b5a00b5aea5f2b9f2bc
projects[l10n_update][subdir] =  contrib

projects[libraries][version] = 2.2
projects[libraries][subdir] =  contrib

projects[linkit][version] = 3.1
projects[linkit][subdir] =  contrib

projects[media][download][type] = "git"
projects[media][download][url] = "git://drupalcode.org/project/media.git"
projects[media][download][revision] = "8fe0f7d6d3787995d84a8077eadfa755f0dd850d"
projects[media][destination] = modules
projects[media][directory_name] =  contrib/media
projects[media][patch][1802026] = http://drupal.org/files/issues/1802026-media-browser-keep-tab-42.patch
projects[media][patch][2126755] = http://drupal.org/files/issues/media-wysiwyg-improved-macro-2126755-55.patch

projects[media_youtube][version] = 2.0-rc4
projects[media_youtube][subdir] =  contrib
projects[media_youtube][patch][1551376] = http://drupal.org/files/youtube-next-previous-links-1551376-7.patch
projects[media_youtube][patch][1863788] = http://drupal.org/files/issues/media_youtube_install_file_displays-1863788-9.patch
projects[media_youtube][patch][2134485] = http://drupal.org/files/issues/media-youtube-preview-image-attributes-2134485-1.patch

projects[module_filter][version] = 2.0-alpha2
projects[module_filter][subdir] =  contrib

projects[strongarm][version] = 2.0
projects[strongarm][subdir] =  contrib

projects[views][version] = 3.7
projects[views][subdir] =  contrib

projects[zen][version] = 5.4
projects[zen][subdir] =  contrib

; Libraries

libraries[ckeditor][download][type] = get
libraries[ckeditor][download][url] = http://download.cksource.com/CKEditor/CKEditor/CKEditor%204.3.1/ckeditor_4.3.1_full.zip
libraries[ckeditor][destination] = contrib/ckeditor

; Translations for ArchTLAS install profile
; uncomment and modify following lines copied from openatrium drush.make file
;libraries[translations][download][type] = "get"
;libraries[translations][download][url] = "https://translate.openatrium.com/sites/translate.openatrium.com/files/atrium-installer-beta9.tar.gz"
;libraries[translations][directory_name] = "translations"
;libraries[translations][destination] = "."