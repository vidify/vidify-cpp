#ifdef __linux__
    #define SYSTEM "Linux"
#else
    #define SYSTEM "Other"
#endif

#include <iostream>
#include "../lib/player.h"


int main() {
    VLCWindow vlc_window;
    vlc_window.start_video();

    return 0;
}
