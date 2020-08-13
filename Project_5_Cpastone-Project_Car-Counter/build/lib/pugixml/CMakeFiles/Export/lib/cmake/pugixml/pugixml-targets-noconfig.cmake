#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "pugixml::pugixml" for configuration ""
set_property(TARGET pugixml::pugixml APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(pugixml::pugixml PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "CXX"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libpugixml.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS pugixml::pugixml )
list(APPEND _IMPORT_CHECK_FILES_FOR_pugixml::pugixml "${_IMPORT_PREFIX}/lib/libpugixml.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
