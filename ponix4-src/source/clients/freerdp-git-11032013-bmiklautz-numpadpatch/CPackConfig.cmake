# This file will be configured to contain variables for CPack. These variables
# should be set in the CMake list file of the project before CPack module is
# included. The list of available CPACK_xxx variables and their associated
# documentation may be obtained using
#  cpack --help-variable-list
#
# Some variables are common to all generators (e.g. CPACK_PACKAGE_NAME)
# and some are specific to a generator
# (e.g. CPACK_NSIS_EXTRA_INSTALL_COMMANDS). The generator specific variables
# usually begin with CPACK_<GENNAME>_xxxx.


SET(CPACK_BINARY_BUNDLE "")
SET(CPACK_BINARY_CYGWIN "")
SET(CPACK_BINARY_DEB "OFF")
SET(CPACK_BINARY_DRAGNDROP "")
SET(CPACK_BINARY_NSIS "OFF")
SET(CPACK_BINARY_OSXX11 "")
SET(CPACK_BINARY_PACKAGEMAKER "")
SET(CPACK_BINARY_RPM "OFF")
SET(CPACK_BINARY_STGZ "ON")
SET(CPACK_BINARY_TBZ2 "OFF")
SET(CPACK_BINARY_TGZ "ON")
SET(CPACK_BINARY_TZ "ON")
SET(CPACK_BINARY_ZIP "")
SET(CPACK_CMAKE_GENERATOR "Unix Makefiles")
SET(CPACK_COMPONENTS_ALL "Unspecified;headers;libraries")
SET(CPACK_COMPONENT_UNSPECIFIED_HIDDEN "TRUE")
SET(CPACK_COMPONENT_UNSPECIFIED_REQUIRED "TRUE")
SET(CPACK_DEBIAN_ARCHITECTURE "i686")
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "marcandre.moreau@gmail.com")
SET(CPACK_GENERATOR "STGZ;TGZ;TZ")
SET(CPACK_INSTALL_CMAKE_PROJECTS "/source/clients/freerdp-git-11032013-bmiklautz-numpadpatch;FreeRDP;ALL;/")
SET(CPACK_INSTALL_PREFIX "/")
SET(CPACK_MODULE_PATH "/source/clients/freerdp-git-11032013-bmiklautz-numpadpatch/cmake/")
SET(CPACK_NSIS_DISPLAY_NAME "FreeRDP")
SET(CPACK_NSIS_INSTALLER_ICON_CODE "")
SET(CPACK_NSIS_INSTALLER_MUI_ICON_CODE "")
SET(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES")
SET(CPACK_NSIS_MODIFY_PATH "ON")
SET(CPACK_NSIS_MUI_ICON "/source/clients/freerdp-git-11032013-bmiklautz-numpadpatch/resources\\FreeRDP_Icon_96px.ico")
SET(CPACK_NSIS_MUI_UNICON "/source/clients/freerdp-git-11032013-bmiklautz-numpadpatch/resource\\FreeRDP_Icon_96px.ico")
SET(CPACK_NSIS_PACKAGE_NAME "FreeRDP")
SET(CPACK_OUTPUT_CONFIG_FILE "/source/clients/freerdp-git-11032013-bmiklautz-numpadpatch/CPackConfig.cmake")
SET(CPACK_PACKAGE_CONTACT "Marc-Andre Moreau")
SET(CPACK_PACKAGE_DEFAULT_LOCATION "/")
SET(CPACK_PACKAGE_DESCRIPTION_FILE "/source/clients/freerdp-git-11032013-bmiklautz-numpadpatch/LICENSE")
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "FreeRDP: A Remote Desktop Protocol Implementation")
SET(CPACK_PACKAGE_EXECUTABLES "xfreerdp")
SET(CPACK_PACKAGE_FILE_NAME "freerdp-1.1.0-dev-Linux-i686")
SET(CPACK_PACKAGE_ICON "/source/clients/freerdp-git-11032013-bmiklautz-numpadpatch/resources\\FreeRDP_Install.bmp")
SET(CPACK_PACKAGE_INSTALL_DIRECTORY "FreeRDP")
SET(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "FreeRDP")
SET(CPACK_PACKAGE_NAME "FreeRDP")
SET(CPACK_PACKAGE_RELOCATABLE "true")
SET(CPACK_PACKAGE_VENDOR "FreeRDP")
SET(CPACK_PACKAGE_VERSION "1.1.0-dev")
SET(CPACK_PACKAGE_VERSION_MAJOR "1")
SET(CPACK_PACKAGE_VERSION_MINOR "1")
SET(CPACK_PACKAGE_VERSION_PATCH "0")
SET(CPACK_PACKAGING_INSTALL_PREFIX "/tmp")
SET(CPACK_RESOURCE_FILE_LICENSE "/source/clients/freerdp-git-11032013-bmiklautz-numpadpatch/LICENSE")
SET(CPACK_RESOURCE_FILE_README "/usr/share/cmake-2.8/Templates/CPack.GenericDescription.txt")
SET(CPACK_RESOURCE_FILE_WELCOME "/usr/share/cmake-2.8/Templates/CPack.GenericWelcome.txt")
SET(CPACK_SET_DESTDIR "on")
SET(CPACK_SOURCE_CYGWIN "")
SET(CPACK_SOURCE_GENERATOR "TGZ;TBZ2;TZ")
SET(CPACK_SOURCE_IGNORE_FILES "/\\.git/;/\\.gitignore;/CMakeCache.txt")
SET(CPACK_SOURCE_OUTPUT_CONFIG_FILE "/source/clients/freerdp-git-11032013-bmiklautz-numpadpatch/CPackSourceConfig.cmake")
SET(CPACK_SOURCE_PACKAGE_FILE_NAME "freerdp-1.1.0-dev-Linux-i686")
SET(CPACK_SOURCE_TBZ2 "ON")
SET(CPACK_SOURCE_TGZ "ON")
SET(CPACK_SOURCE_TZ "ON")
SET(CPACK_SOURCE_ZIP "OFF")
SET(CPACK_SYSTEM_NAME "Linux-i686")
SET(CPACK_TOPLEVEL_TAG "Linux-i686")

# Configuration for component "headers"

SET(CPACK_COMPONENTS_ALL Unspecified headers libraries)
set(CPACK_COMPONENT_HEADERS_DISPLAY_NAME "Headers")

# Configuration for component "libraries"

SET(CPACK_COMPONENTS_ALL Unspecified headers libraries)
set(CPACK_COMPONENT_LIBRARIES_DISPLAY_NAME "Libraries")

# Configuration for component "clients"

SET(CPACK_COMPONENTS_ALL Unspecified headers libraries)
set(CPACK_COMPONENT_CLIENTS_DISPLAY_NAME "Clients")
