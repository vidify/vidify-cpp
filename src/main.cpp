#include <iostream>
#include <chrono>
#include "config.h"
#include "player/vlc.h"

#if defined(__linux__) || defined(__sun) || defined(__FreeBSD) || defined(__NetBSD__) || defined(__OpenBSD__)
#    define USE_LINUX_API true
#    include "api/linux.h"
#elif defined(_WIN32)
#    define USE_WINDOWS_API true 
#elif defined(__APPLE__)
#    define USE_MACOS_API true
#else
#    define USE_WEB_API true
#endif

void printUsage();
void printVersion();


int main(int argc, char *argv[]) {
    // Argument variables
    bool lyrics = true;
    bool fullscreen = false;
    bool useWebApi = false;

    // Argument parsing
    if (argc >= 2) {
        for (int i = 1; i < argc; i++) {
            std::string arg = argv[i];

            if (arg == "--help" || arg == "-h") {
                printUsage();
                return 0;
            }

            else if (arg == "--version" || arg == "-v") {
                printVersion();
                return 0;
            }

            else if (arg == "--no-lyrics" || arg == "-n") {
                lyrics = false;
            }

            else if (arg == "--fullscreen" || arg == "-f") {
                fullscreen = true;
            }

            else if (arg == "--use-web-api" || arg == "-w") {
                useWebApi = true;
            }
        }
    }

    parseConfig();
    
    // Hides stderr if debug is disabled
#ifndef DEBUG
    freopen("/dev/null", "w", stderr);
#endif

    // Choosing the used API depending on the platform
    // The Web API is the default when the system isn't supported, and can be
    // enabled with a flag within the program.
#ifndef USE_WEB_API
    if (useWebApi) {
#endif
        std::cout << "Web API" << std::endl;
#ifndef USE_WEB_API
    }
#endif

#ifdef USE_LINUX_API
    VLCPlayer player;
    DBusAPI<VLCPlayer> spotify(player);
    playVideosDBus<VLCPlayer>(player, spotify, lyrics);
#elif defined(USE_WINDOWS_API)
    std::cout << "Windows" << std::endl;
#elif defined(USE_MACOS_API)
    std::cout << "macOS" << std::endl;
#endif

    return 0;
}


void printUsage() {
    std::cout << "usage: spotivids [-h] [-v] [-n] [-f]\n\n"
        << "  -h, --help            show this help message and exit\n"
        << "  -v, --version         show the program's version and exit\n"
        << "  -n, --no-lyrics       do not print lyrics\n"
        << "  -f, --fullscreen      play videos in fullscreen mode\n"
        << std::flush;
}


void printVersion() {
    std::cout << "spotivids (C++) 1.0.0" << std::endl;
}
