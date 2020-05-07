#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "fmi4cpp::fmi4cpp" for configuration ""
set_property(TARGET fmi4cpp::fmi4cpp APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(fmi4cpp::fmi4cpp PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libfmi4cpp.so"
  IMPORTED_SONAME_NOCONFIG "libfmi4cpp.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS fmi4cpp::fmi4cpp )
list(APPEND _IMPORT_CHECK_FILES_FOR_fmi4cpp::fmi4cpp "${_IMPORT_PREFIX}/lib/libfmi4cpp.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
