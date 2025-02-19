#----------------------------------------------------------------
# Generated CMake target import file for configuration "Test Release with JPEG decoder".
#----------------------------------------------------------------

# Commands may need to know the format version.
SET(CMAKE_IMPORT_FILE_VERSION 1)

# Compute the installation prefix relative to this file.
GET_FILENAME_COMPONENT(_IMPORT_PREFIX "${CMAKE_CURRENT_LIST_FILE}" PATH)
GET_FILENAME_COMPONENT(_IMPORT_PREFIX "${_IMPORT_PREFIX}" PATH)
GET_FILENAME_COMPONENT(_IMPORT_PREFIX "${_IMPORT_PREFIX}" PATH)
GET_FILENAME_COMPONENT(_IMPORT_PREFIX "${_IMPORT_PREFIX}" PATH)

# Make sure the targets which have been exported in some other 
# export set exist.

# Import target "winpr" for configuration "Test Release with JPEG decoder"
SET_PROPERTY(TARGET winpr APPEND PROPERTY IMPORTED_CONFIGURATIONS TEST RELEASE WITH JPEG DECODER)
SET_TARGET_PROPERTIES(winpr PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_TEST RELEASE WITH JPEG DECODER "C"
  IMPORTED_LINK_INTERFACE_LIBRARIES_TEST RELEASE WITH JPEG DECODER "-lpthread;dl;/usr/lib/libz.so;/usr/lib/libssl.so;/usr/lib/libcrypto.so;/usr/lib/libz.so;-lpthread;dl;-lpthread;dl;-lpthread;dl;rt;/usr/lib/libz.so;/usr/lib/libssl.so;/usr/lib/libcrypto.so;m;rt;/usr/lib/libssl.so;/usr/lib/libcrypto.so;/usr/lib/libz.so;/usr/lib/libz.so;dl"
  IMPORTED_LOCATION_TEST RELEASE WITH JPEG DECODER "${_IMPORT_PREFIX}/lib/libwinpr.a"
  )

LIST(APPEND _IMPORT_CHECK_TARGETS winpr )
LIST(APPEND _IMPORT_CHECK_FILES_FOR_winpr "${_IMPORT_PREFIX}/lib/libwinpr.a" )

# Make sure the targets which have been exported in some other 
# export set exist.

# Import target "winpr-makecert-tool" for configuration "Test Release with JPEG decoder"
SET_PROPERTY(TARGET winpr-makecert-tool APPEND PROPERTY IMPORTED_CONFIGURATIONS TEST RELEASE WITH JPEG DECODER)
SET_TARGET_PROPERTIES(winpr-makecert-tool PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_TEST RELEASE WITH JPEG DECODER "C"
  IMPORTED_LINK_INTERFACE_LIBRARIES_TEST RELEASE WITH JPEG DECODER "/usr/lib/libz.so;/usr/lib/libssl.so;/usr/lib/libcrypto.so;winpr"
  IMPORTED_LOCATION_TEST RELEASE WITH JPEG DECODER "${_IMPORT_PREFIX}/lib/libwinpr-makecert-tool.a"
  )

LIST(APPEND _IMPORT_CHECK_TARGETS winpr-makecert-tool )
LIST(APPEND _IMPORT_CHECK_FILES_FOR_winpr-makecert-tool "${_IMPORT_PREFIX}/lib/libwinpr-makecert-tool.a" )

# Loop over all imported files and verify that they actually exist
FOREACH(target ${_IMPORT_CHECK_TARGETS} )
  FOREACH(file ${_IMPORT_CHECK_FILES_FOR_${target}} )
    IF(NOT EXISTS "${file}" )
      MESSAGE(FATAL_ERROR "The imported target \"${target}\" references the file
   \"${file}\"
but this file does not exist.  Possible reasons include:
* The file was deleted, renamed, or moved to another location.
* An install or uninstall procedure did not complete successfully.
* The installation package was faulty and contained
   \"${CMAKE_CURRENT_LIST_FILE}\"
but not all the files it references.
")
    ENDIF()
  ENDFOREACH()
  UNSET(_IMPORT_CHECK_FILES_FOR_${target})
ENDFOREACH()
UNSET(_IMPORT_CHECK_TARGETS)

# Cleanup temporary variables.
SET(_IMPORT_PREFIX)

# Commands beyond this point should not need to know the version.
SET(CMAKE_IMPORT_FILE_VERSION)
