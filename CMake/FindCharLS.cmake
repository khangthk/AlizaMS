find_path(CHARLS_2_0_INCLUDE_DIR CharLS/charls.h /usr/include /usr/local/include)
find_library(CHARLS_2_0_LIBRARY NAMES CharLS PATHS /usr/lib /usr/local/lib)
if(CHARLS_2_0_LIBRARY AND CHARLS_2_0_INCLUDE_DIR)
  set(CHARLS_LIBRARIES    ${CHARLS_2_0_LIBRARY})
  set(CHARLS_INCLUDE_DIRS ${CHARLS_2_0_INCLUDE_DIR})
  set(CHARLS_FOUND "YES")
  set(CHARLS_2_1_OR_HIGHER FALSE)
else()
  find_path(CHARLS_INCLUDE_DIR charls/charls.h /usr/include /usr/local/include)
  find_library(CHARLS_LIBRARY NAMES charls PATHS /usr/lib /usr/local/lib)
  if(CHARLS_LIBRARY AND CHARLS_INCLUDE_DIR)
    set(CHARLS_LIBRARIES    ${CHARLS_LIBRARY})
    set(CHARLS_INCLUDE_DIRS ${CHARLS_INCLUDE_DIR})
    set(CHARLS_FOUND "YES")
	set(CHARLS_2_1_OR_HIGHER TRUE)
  else()
    set(CHARLS_FOUND "NO")
  endif()
endif()

if(CHARLS_FOUND)
  message(STATUS "Found CharLS library: ${CHARLS_LIBRARIES}, headers: ${CHARLS_INCLUDE_DIRS}")
  if(CHARLS_OR_HIGHER)
    message(STATUS "CharLS library version 2.1 or higher")
  endif()
else()
  message(FATAL_ERROR "CharLS not found")
endif()

mark_as_advanced(CHARLS_2_0_LIBRARY CHARLS_2_0_INCLUDE_DIR CHARLS_LIBRARY CHARLS_INCLUDE_DIR)

