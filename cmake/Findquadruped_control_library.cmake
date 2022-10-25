SET(quadruped_control_library_FOUND FALSE)
UNSET(quadruped_control_library_INCLUDE_DIR CACHE)
UNSET(quadruped_control_library_LIBRARY CACHE)

IF(CUSTOM_quadruped_control_library_PATH)
  FIND_PATH(quadruped_control_library_INCLUDE_DIR quadruped_control_library
    PATHS
    ${CUSTOM_quadruped_control_library_PATH}/include
    NO_DEFAULT_PATH
  )

  FIND_LIBRARY(quadruped_control_library_LIBRARY quadruped_control_library
    PATHS
    ${CUSTOM_quadruped_control_library_PATH}/lib
    NO_DEFAULT_PATH
  )

ELSE(CUSTOM_quadruped_control_library_PATH)
  FIND_PATH(quadruped_control_library_INCLUDE_DIR quadruped_control_library
    HINTS
    $ENV{HOME}/local/include
    $ENV{quadruped_control_library_PATH}/src
    $ENV{quadruped_control_library_PATH}/include
    $ENV{quadruped_control_library_INCLUDE_PATH}
    /usr/local/include
    /usr/include
  )

  FIND_LIBRARY(quadruped_control_library_LIBRARY quadruped_control_library
    PATHS
    $ENV{HOME}/local/lib
    $ENV{HOME}/local/lib/x86_64-linux-gnu
    $ENV{quadruped_control_library_PATH}/lib
    $ENV{quadruped_control_library_LIBRARY_PATH}
    /usr/local/lib
    /usr/local/lib/x86_64-linux-gnu
    /usr/lib
    /usr/lib/x86_64-linux-gnu
  )
ENDIF(CUSTOM_quadruped_control_library_PATH)

IF(quadruped_control_library_INCLUDE_DIR AND quadruped_control_library_LIBRARY)
  SET(quadruped_control_library_FOUND TRUE)
ELSE(quadruped_control_library_INCLUDE_DIR AND quadruped_control_library_LIBRARY)
  IF(quadruped_control_library_FIND_REQUIRED)
    MESSAGE(SEND_ERROR " Could not find quadruped_control_library.")
    MESSAGE(SEND_ERROR " Try setting CUSTOM_quadruped_control_library_PATH in Findquadruped_control_library.cmake force CMake to use the desired directory.")
  ELSE(quadruped_control_library_FIND_REQUIRED)
    MESSAGE(STATUS " Could not find quadruped_control_library.")
    MESSAGE(STATUS " Try setting CUSTOM_quadruped_control_library_PATH in Findquadruped_control_library.cmake force CMake to use the desired directory.")
  ENDIF(quadruped_control_library_FIND_REQUIRED)
ENDIF(quadruped_control_library_INCLUDE_DIR AND quadruped_control_library_LIBRARY)

IF(quadruped_control_library_FOUND)
  IF(NOT quadruped_control_library_FIND_QUIETLY)
    MESSAGE(STATUS "Found quadruped_control_library: ${quadruped_control_library_LIBRARY}")
  ENDIF(NOT quadruped_control_library_FIND_QUIETLY)

  foreach(COMPONENT ${quadruped_control_library_FIND_COMPONENTS})
    IF(quadruped_control_library_${COMPONENT}_FOUND)
      IF(NOT quadruped_control_library_FIND_QUIETLY)
        MESSAGE(STATUS "Found quadruped_control_library ${COMPONENT}: ${quadruped_control_library_${COMPONENT}_LIBRARY}")
      ENDIF(NOT quadruped_control_library_FIND_QUIETLY)
    ELSE(quadruped_control_library_${COMPONENT}_FOUND)
      MESSAGE(ERROR " Could not find quadruped_control_library ${COMPONENT}")
    ENDIF(quadruped_control_library_${COMPONENT}_FOUND)
  endforeach(COMPONENT)
ENDIF(quadruped_control_library_FOUND)

MARK_AS_ADVANCED(
  quadruped_control_library_INCLUDE_DIR
  quadruped_control_library_LIBRARY
)
