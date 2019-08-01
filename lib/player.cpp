#include "player.h"
#include <iostream>
#include <vlc/vlc.h>

VLCWindow::VLCWindow() {
    std::cout << "Initializing VLC\n";
    vlc_instance = libvlc_new(0, NULL);
    if (vlc_instance == NULL) {
        std::cout << "Oh no we did a fucky wucky uwu\n";
    }

	vlc_player = libvlc_media_player_new(vlc_instance);

}

void VLCWindow::start_video() {
    std::cout << "Playing video\n";
}

