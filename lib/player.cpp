#include "player.h"
#include <iostream>
#include <vlc/vlc.h>
#define STR_LONG 64

// Log a formatted message if debug is enabled
void log(std::string msg, bool debug) {
    if (debug) {
        std::cout << "\033[92m" << ">>" << msg << "\033[0m" << std::endl;
    }
}

// Show a formatted error and quit
void error(std::string msg) {
    throw std::exception();
    std::cout << "\033[91m" << "[ERROR]:" << msg << "\033[0m" << std::endl;
}


// Initialize the instance and the player
VLCWindow::VLCWindow(bool args_debug, bool args_fullscreen) {
    // Arguments config
    debug = args_fullscreen;
    fullscreen = args_fullscreen;

    log("Initializing VLC", debug);
    
    std::string args = "";
    if (debug) args += "--verbose=1";
    else args += "--quiet";

    const char *const vlc_args = args.c_str();
    instance = libvlc_new(2, &vlc_args);
    if (instance == NULL) {
        error("VLC couldn't be initialzed");
    }

	player = libvlc_media_player_new(instance);
}

// Load a new video on the VLC player
void VLCWindow::load_video(const std::string url) {
    log("Playing video", debug);

    // Media instance
    libvlc_media_t *media = libvlc_media_new_path(instance, url.c_str());
    libvlc_media_player_set_media(player, media);
    libvlc_media_release(media);
}

void VLCWindow::play() {
    libvlc_media_player_play(player);
}
void VLCWindow::pause() {
    libvlc_media_player_pause(player);
}
void VLCWindow::toggle_pause() {
    if (libvlc_media_player_is_playing(player)) {
        pause();
    }
    else {
        play();
    }
}

// Set the position of the VLC media playing
void VLCWindow::set_position() {
}


DbusPlayer::DbusPlayer(bool debug, bool fullscreen) : player(debug, fullscreen) {
}

void DbusPlayer::wait() {
    while(1) {}
}

