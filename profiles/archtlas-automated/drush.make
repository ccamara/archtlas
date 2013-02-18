; ArchTLAS make file
core = "7.x"
api = "2"
; comment this out in to use on drupal.org
projects[drupal][version] = "7.x"

; Modules
;projects[ctools][version] = "1.2"
projects[ctools][subdir] = "contrib"

;projects[features][version] = "1.0"
projects[features][subdir] = "contrib"

;projects[addressfield][version] = "1.0-beta3"
projects[addressfield][subdir] = "contrib"

;projects[field_group][version] = "1.1"
projects[field_group][subdir] = "contrib"

;projects[geofield][version] = "1.1"
projects[geofield][subdir] = "contrib"

;projects[media][version] = "1.2"
projects[media][subdir] = "contrib"

;projects[media_youtube][version] = "1.0-beta3"
projects[media_youtube][subdir] = "contrib"

;projects[l10n_client][version] = "1.1"
projects[l10n_client][subdir] = "contrib"

;projects[l10n_update][version] = "1.0-beta3"
projects[l10n_update][subdir] = "contrib"

;projects[i18n][version] = "1.8"
projects[i18n][subdir] = "contrib"

;projects[i18nviews][version] = "3.x-dev"
projects[i18nviews][subdir] = "contrib"

;projects[backup_migrate][version] = "2.4"
projects[backup_migrate][subdir] = "contrib"

;projects[colorbox][version] = "1.4"
projects[colorbox][subdir] = "contrib"

;projects[entity][version] = "1.0"
projects[entity][subdir] = "contrib"

;projects[filter_tips_dialog][version] = "1.x-dev"
;projects[filter_tips_dialog][subdir] = "contrib"

;projects[geocoder][version] = "1.2"
projects[geocoder][subdir] = "contrib"

;projects[geophp][version] = "1.7"
projects[geophp][subdir] = "contrib"

;projects[leaflet][version] = "1.0-beta2"
projects[leaflet][subdir] = "contrib"

;projects[leaflet_more_maps][version] = "1.2"
projects[leaflet_more_maps][subdir] = "contrib"

;projects[libraries][version] = "2.0"
projects[libraries][subdir] = "contrib"

;projects[media_colorbox][version] = "1.0-rc3"
projects[media_colorbox][subdir] = "contrib"

;projects[pathauto][version] = "1.2"
projects[pathauto][subdir] = "contrib"

;projects[rotating_banner][version] = "2.x-dev"
projects[rotating_banner][subdir] = "contrib"

;projects[token][version] = "1.4"
projects[token][subdir] = "contrib"

;projects[transliteration][version] = "3.1"
projects[transliteration][subdir] = "contrib"

;projects[globalredirect][version] = "1.5"
projects[globalredirect][subdir] = "contrib"

;projects[works_and_projects][version] = "1.0"
projects[works_and_projects][subdir] = "contrib"

;projects[taxonomy_manager][version] = "1.0-rc1"
projects[taxonomy_manager][subdir] = "contrib"

;projects[addanother][version] = "2.1"
projects[addanother][subdir] = "contrib"

;projects[dialog][version] = "1.x-dev"
projects[dialog][subdir] = "contrib"

;projects[wysiwyg][version] = "2.2"
projects[wysiwyg][subdir] = "contrib"

;projects[variable][version] = "2.2"
projects[variable][subdir] = "contrib"

;projects[i18_page_views][version] = "1.1"
projects[i18_page_views][subdir] = "contrib"

;projects[views][version] = "3.5"
projects[views][subdir] = "contrib"


; Themes
; blossom-admin
projects[blossom-admin][type] = "theme"
projects[blossom-admin][version] = "1.0"
projects[blossom-admin][subdir] = "contrib"

; Libraries
libraries[colorbox][directory_name] = "colorbox"
libraries[colorbox][type] = "library"
libraries[colorbox][destination] = "libraries"
libraries[colorbox][download][type] = "get"
libraries[colorbox][download][url] = "" ; TODO add download URI

libraries[ckeditor][directory_name] = "ckeditor"
libraries[ckeditor][type] = "library"
libraries[ckeditor][destination] = "libraries"
libraries[ckeditor][download][type] = "get"
libraries[ckeditor][download][url] = "" ; TODO add download URI

libraries[leaflet][directory_name] = "leaflet"
libraries[leaflet][type] = "library"
libraries[leaflet][destination] = "libraries"
libraries[leaflet][download][type] = "get"
libraries[leaflet][download][url] = "" ; TODO add download URI

libraries[leaflet_markercluster][directory_name] = "leaflet_markercluster"
libraries[leaflet_markercluster][type] = "library"
libraries[leaflet_markercluster][destination] = "libraries"
libraries[leaflet_markercluster][download][type] = "get"
libraries[leaflet_markercluster][download][url] = "" ; TODO add download URI


; Patches
projects[drupal][patch][] = "http://drupal.org/files/compatibility_media_1-1539528-1.patch"

projects[contrib][patch][] = "http://drupal.org/files/compatibility_media_1-1539528-1.patch"
