CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

PROJECT(spotivids-cpp VERSION 1.0.0)
SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS "-pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused -DDEBUG")
LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")


FIND_PACKAGE(LibVLC REQUIRED)
IF (LIBVLC_FOUND)
    MESSAGE(STATUS "Found LibVLC library path: ${LIBVLC_LIBRARY}")
    MESSAGE(STATUS "Found LibVLC include-dir path: ${LIBVLC_INCLUDE_DIR}")
    INCLUDE_DIRECTORIES(${LIBVLC_INCLUDE_DIR})
ELSE ()
    MESSAGE(FATAL_ERROR "LibVLC wasn't found in the system. Please install the libraries and try again.")
ENDIF (LIBVLC_FOUND)


FIND_PACKAGE(DBus REQUIRED)
IF (DBUS_FOUND)
    MESSAGE(STATUS "Found DBus library path: ${DBUS_LIBRARIES}")
    MESSAGE(STATUS "Found DBus include-dir path: ${DBUS_INCLUDE_DIR}")
    INCLUDE_DIRECTORIES(${DBUS_INCLUDE_DIRS})
ELSE ()
    MESSAGE(FATAL_ERROR "DBus wasn't found in the system. Please install the libraries and try again.")
ENDIF (DBUS_FOUND)


FIND_PACKAGE(GLIB REQUIRED)
IF (GLIB_FOUND)
    MESSAGE(STATUS "Found GLib library path: ${GLIB_LIBRARIES}")
    MESSAGE(STATUS "Found GLib include-dir path: ${GLIB_INCLUDE_DIRS}")
    INCLUDE_DIRECTORIES(${GLIB_INCLUDE_DIRS})
ELSE ()
    MESSAGE(FATAL_ERROR "GLib wasn't found in the system. Please install the libraries try again.")
ENDIF (GLIB_FOUND)


SET(SOURCE_FILES
                src/main.cpp
                src/player/vlc.cpp)

ADD_EXECUTABLE(spotivids ${SOURCE_FILES})
TARGET_LINK_LIBRARIES(
    spotivids
    ${LIBVLC_LIBRARY} 
    ${DBUS_LIBRARIES}
    ${GLIB_LIBRARIES}
    ${GLIB_GOBJECT_LIBRARIES}
)
