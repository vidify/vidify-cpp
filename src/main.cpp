#include <iostream>
#include <chrono>
#include "../lib/player.h"


void print_usage();
void print_version();
void play_videos_dbus(VLCWindow player, DBusPlayer spotify);

// Argument variables
bool SHOW_LYRICS = true;
bool FULLSCREEN = false;


int main(int argc, char *argv[]) {
    // Argument parsing
    if (argc >= 2) {
        for (int i = 1; i < argc; i++) {
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
        }
    }
    
    // Hides stderr if debug is disabled
#ifdef DEBUG
    freopen("/dev/null", "w", stderr);
#endif

    // Chooses the used API depending on the platform
#ifdef __linux__
    DBusPlayer spotify(FULLSCREEN);
    play_videos_dbus(spotify.player, spotify);
#else
    std::cout << "spotify-videos only works on linux for now.\n";
#endif

    return 0;
}

void play_videos_dbus(VLCWindow player, DBusPlayer spotify) {
    while(1) {
        std::string name = "Arctic Monkeys";

        auto t_start = std::chrono::high_resolution_clock::now();

        std::string url = player.get_url(name);
        player.load_video(url);

        auto t_end = std::chrono::high_resolution_clock::now();
        int offset = std::chrono::duration<double, std::milli>(t_end-t_start).count();


        // TODO: Play only if spotify is playing
        player.play();
        player.set_position(offset);

        if (SHOW_LYRICS) player.print_lyrics(name);

        spotify.wait();
    }
}

void print_usage() {
    std::cout << "usage: spotify-videos [-h] [-v] [-n] [-f]\n\n"
        << "Windows and Mac users must pass --username, --client-id and --client-secret to\n"
        << "use the web API. Read more about how to obtain them in the README\n"
        << "(https://github.com/marioortizmanero/spotify-music-videos-cpp)\n\n"
        << "optional arguments:\n"
        << "  -h, --help            show this help message and exit\n"
        << "  -v, --version         show the program's version and exit\n"
        << "  -n, --no-lyrics       do not print lyrics\n"
        << "  -f, --fullscreen      play videos in fullscreen mode\n"
        << std::flush;
}

void print_version() {
    std::cout << "spotify-videos (c++) 1.0.0" << std::endl;
}
