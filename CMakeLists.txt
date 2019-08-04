CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

PROJECT(Spotify-music-videos-cpp VERSION 1.0.0)
SET(CMAKE_CXX_STANDARD 17)
LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

FIND_PACKAGE(LibVLC REQUIRED)
IF (LIBVLC_FOUND)
    INCLUDE_DIRECTORIES(${LIBVLC_INCLUDE_DIR})
ELSE ()
    MESSAGE(FATAL_ERROR "LibVLC wasn't found in the system. Please install the libraries and try again")
ENDIF (LIBVLC_FOUND)

FIND_PACKAGE(DBus REQUIRED)
IF (DBUS_FOUND)
    INCLUDE_DIRECTORIES(${DBUS_INCLUDE_DIRS})
ELSE ()
    MESSAGE(FATAL_ERROR "DBus wasn't found in the system. Please install the libraries and try again")
ENDIF (DBUS_FOUND)


SET(SOURCE_FILES
                src/main.cpp
                lib/player.cpp)

ADD_EXECUTABLE(spotify_videos ${SOURCE_FILES})
TARGET_LINK_LIBRARIES(spotify_videos ${LIBVLC_LIBRARY} ${DBUS_LIBRARIES})
