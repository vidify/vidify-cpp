# Try to find LibVLC
# Once done, this will define:
# 
#  LIBVLC_FOUND - true if found
#  LIBVLC_INCLUDE_DIR
#  LIBVLC_LIBRARY


# FIND_PATH and FIND_LIBRARY normally search standard locations
# before the specified paths. To search non-standard paths first,
# FIND_* is invoked first with specified paths and NO_DEFAULT_PATH
# and then again with no specified paths to search the default
# locations. When an earlier FIND_* succeeds, subsequent FIND_*s
# searching for the same item do nothing.

FIND_PATH(LIBVLC_INCLUDE_DIR vlc/vlc.h
  HINTS "$ENV{LIBVLC_INCLUDE_PATH}"
  PATHS
    #Mac OS and Contribs
    "${CMAKE_CURRENT_SOURCE_DIR}/contribs/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/contribs/include/vlc"
    "/Applications/VLC.app/Contents/MacOS/include"
    "/Applications/VLC.app/Contents/MacOS/include/vlc"
    # Env
    "$ENV{LIB_DIR}/include"
    "$ENV{LIB_DIR}/include/vlc"
    # Linux
    "/usr/include"
    "/usr/include/vlc"
    "/usr/local/include"
    "/usr/local/include/vlc"
    # mingw
    c:/msys/local/include
    "c:/Program Files (x86)/VideoLAN/VLC/sdk/include"
  )
FIND_PATH(LIBVLC_INCLUDE_DIR PATHS "${CMAKE_INCLUDE_PATH}/vlc" NAMES vlc.h)

FIND_LIBRARY(LIBVLC_LIBRARY NAMES vlc libvlc
  HINTS "$ENV{LIBVLC_LIBRARY_PATH}"
  PATHS
    "$ENV{LIB_DIR}/lib"
    # Mac OS
    "${CMAKE_CURRENT_SOURCE_DIR}/contribs/lib"
    "${CMAKE_CURRENT_SOURCE_DIR}/contribs/plugins"
    "/Applications/VLC.app/Contents/MacOS/lib"
    "/Applications/VLC.app/Contents/MacOS/plugins"
    # mingw
    c:/msys/local/lib
    "c:/Program Files (x86)/VideoLAN/VLC/sdk/lib"
  )
FIND_LIBRARY(LIBVLC_LIBRARY NAMES vlc libvlc)
FIND_LIBRARY(LIBVLCCORE_LIBRARY NAMES vlccore libvlccore
  HINTS "$ENV{LIBVLC_LIBRARY_PATH}"
  PATHS
    "$ENV{LIB_DIR}/lib"
    # Mac OS
    "${CMAKE_CURRENT_SOURCE_DIR}/contribs/lib"
    "${CMAKE_CURRENT_SOURCE_DIR}/contribs/plugins"
    "/Applications/VLC.app/Contents/MacOS/lib"
    "/Applications/VLC.app/Contents/MacOS/plugins"
    # mingw
    c:/msys/local/lib
    "c:/Program Files (x86)/VideoLAN/VLC/sdk/lib"
  )
FIND_LIBRARY(LIBVLCCORE_LIBRARY NAMES vlccore libvlccore)

IF (LIBVLC_INCLUDE_DIR AND LIBVLC_LIBRARY AND LIBVLCCORE_LIBRARY)
   SET(LIBVLC_FOUND TRUE)
ENDIF (LIBVLC_INCLUDE_DIR AND LIBVLC_LIBRARY AND LIBVLCCORE_LIBRARY)
