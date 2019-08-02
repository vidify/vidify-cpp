#ifdef __linux__
    #define SYSTEM "Linux"
#else
    #define SYSTEM "Other"
#endif

#include <iostream>
#include "../lib/player.h"

void print_usage();
void print_version();
void play_videos_dbus(VLCWindow player, DbusPlayer spotify);


int main(int argc, char *argv[]) {
    // Argument variables
    bool SHOW_LYRICS = true;
    bool FULLSCREEN = false;
    bool DEBUG = false;

    // Argument parsing
    if (argc >= 2) {
        for (int i=1; i<=argc; i++) {
            std::string arg = argv[i];
            if (arg == "--help" || arg == "-h") {
                print_usage();
                return 0;
            }
            else if (arg == "--version" || arg == "-v") {
                print_version();
                return 0;
            }
            else if (arg == "--no-lyrics" || arg == "-n") {
                SHOW_LYRICS = false;
            }
            else if (arg == "--fullscreen" || arg == "-f") {
                FULLSCREEN = true;
            }
            else if (arg == "--debug") {
                DEBUG = true;
            }
        }
    }
    
    // Hides stderr if debug is disabled
    if (!DEBUG) freopen("/dev/null", "w", stderr);

    DbusPlayer spotify(DEBUG, FULLSCREEN);

    // Check platform
    play_videos_dbus(spotify.player, spotify);

    return 0;
}

void play_videos_dbus(VLCWindow player, DbusPlayer spotify) {
    while(1) {
        // Get formatted name

        // Count elapsed time
        // Get url with youtube_dl
        std::string url = "/home/mario/Downloads/test_video.mp4";
        player.load_video(url);
        // Set offset time
        // Play only if spotify is playing
        player.play();

        // Print lyrics

        spotify.wait();
    }
}

void print_usage() {
    std::cout << "usage: spotify-videoclips [-h] [-v] [-n] [-f]\n\n"
        << "Windows and Mac users must pass --username, --client-id and --client-secret to\n"
        << "use the web API. Read more about how to obtain them in the README\n"
        << "(https://github.com/marioortizmanero/spotify-videoclips)\n\n"
        << "optional arguments:\n"
        << "  -h, --help            show this help message and exit\n"
        << "  -v, --version         show the program's version and exit\n"
        << "  --debug               display debug messages\n"
        << "  -n, --no-lyrics       do not print lyrics\n"
        << "  -f, --fullscreen      play videos in fullscreen mode\n"
        << std::flush;
}

void print_version() {
    std::cout << "spotify-videoclips 1.0.0" << std:: endl;
}
