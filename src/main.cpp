#include <iostream>
#include <chrono>
#include "player/vlc.h"
#include "api/linux.h"


void printUsage();
void printVersion();


int main(int argc, char *argv[]) {
    // Argument variables
    bool lyrics = true;
    bool fullscreen = false;

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
        }
    }
    
    // Hides stderr if debug is disabled
#ifndef DEBUG
    freopen("/dev/null", "w", stderr);
#endif

    // Chooses the used API depending on the platform
#ifdef __linux__
    VLCPlayer player;
    DBusAPI<VLCPlayer> spotify(player);
    playVideosDBus<VLCPlayer>(player, spotify, lyrics);
#else
    std::cout << "spotivids only works on linux for now.\n";
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
