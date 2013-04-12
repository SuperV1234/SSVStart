set(FIND_SSVSTART_LIB_PATHS
  "${PROJECT_SOURCE_DIR}/../SSVStart/"
  "${PROJECT_SOURCE_DIR}/extlibs/SSVStart/"
  ${SSVSTART_ROOT}
  $ENV{SSVSTART_ROOT}
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local
  /usr/
  /sw/
  /opt/local
  /opt/csw
  /opt
)

FIND_PATH(SSVSTART_INCLUDE_DIR
  NAMES SSVStart/SSVStart.h
  PATH_SUFFIXES include/
  PATHS ${FIND_SSVSTART_LIB_PATHS}
)
MESSAGE("\nFound SSVStart include at: ${SSVSTART_INCLUDE_DIR}.\n")

FIND_LIBRARY(SSVSTART_LIBRARY_RELEASE
  NAMES SSVStart SSVStart-s
  PATH_SUFFIXES lib/ lib64/
  PATHS ${FIND_SSVSTART_LIB_PATHS}
)
MESSAGE("\nFound SSVStart release library at: ${SSVSTART_LIBRARY_RELEASE}.\n")

FIND_LIBRARY(SSVSTART_LIBRARY_DEBUG
  NAMES SSVStart-d SSVStart-s-d
  PATH_SUFFIXES lib/ lib64/
  PATHS ${FIND_SSVSTART_LIB_PATHS}
)
MESSAGE("\nFound SSVStart debug library at: ${SSVSTART_LIBRARY_DEBUG}.\n")

if(SSVSTART_LIBRARY_DEBUG OR SSVSTART_LIBRARY_RELEASE)
  set(SSVSTART_FOUND TRUE)
  if(SSVSTART_LIBRARY_DEBUG AND SSVSTART_LIBRARY_RELEASE)
    SET(SSVSTART_LIBRARY debug ${SSVSTART_LIBRARY_DEBUG} optimized ${SSVSTART_LIBRARY_RELEASE})
  endif()
  if(SSVSTART_LIBRARY_DEBUG AND NOT SSVSTART_LIBRARY_RELEASE)
    set(SSVSTART_LIBRARY_RELEASE ${SSVSTART_LIBRARY_DEBUG})
    set(SSVSTART_LIBRARY         ${SSVSTART_LIBRARY_DEBUG})
  endif()
  if(SSVSTART_LIBRARY_RELEASE AND NOT SSVSTART_LIBRARY_DEBUG)
    set(SSVSTART_LIBRARY_DEBUG ${SSVSTART_LIBRARY_RELEASE})
    set(SSVSTART_LIBRARY       ${SSVSTART_LIBRARY_RELEASE})
  endif()
else()
  set(SSVSTART_FOUND FALSE)
  set(SSVSTART_LIBRARY "")
endif()

IF(SSVSTART_FOUND)
  MESSAGE(STATUS "\nFound SSVSTART: ${SSVSTART_LIBRARY}\n")
ELSE()
  IF(SSVSTART_FIND_REQUIRED)
    MESSAGE(FATAL_ERROR "\nCould not find SSVStart library\n")
  ENDIF(SSVSTART_FIND_REQUIRED)
  set(SSVSTART_ROOT "" CACHE PATH "SSVStart top-level directory")
  message("\n-> SSVStart directory not found. Set SSVSTART_ROOT to SSVStart' top-level path (containing both \"include\" and \"lib\" directories).")
ENDIF()

MARK_AS_ADVANCED(
  SSVSTART_LIBRARY_DEBUG
  SSVSTART_LIBRARY_RELEASE
  SSVSTART_LIBRARY
  SSVSTART_INCLUDE_DIR
)
