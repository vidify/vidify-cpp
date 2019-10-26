#include <iostream>
#include <chrono>
#include "config.hpp"
#include "player/vlc.hpp"

#if defined(__linux__) || defined(__sun) || defined(__FreeBSD) || defined(__NetBSD__) || defined(__OpenBSD__)
#    define USE_LINUX_API true
#    include "api/linux.hpp"
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

    // Config parsing from both the config file and the arguments
    Config config(argc, argv);
    
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


