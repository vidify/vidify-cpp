#include "player.h"
#include <algorithm>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <vlc/vlc.h>


// Initialize the instance and the player
VLCWindow::VLCWindow(bool args_debug, bool args_fullscreen) {
    // Arguments config
    debug = args_debug;
    fullscreen = args_fullscreen;

    log("Initializing VLC", debug);
    
    std::string args = "";
    if (debug) args += "--verbose=0";
    else args += "--quiet";

    const char *const vlc_args = args.c_str();
    instance = libvlc_new(2, &vlc_args);
    if (!instance) throw std::runtime_error("VLC couldn't be initialzed");

	player = libvlc_media_player_new(instance);
}

// Returns the url ouput from a youtube-dl search
std::string VLCWindow::get_url(std::string title) {
    std::array<char, 128> buffer;
    std::string result;
    // Formatting the full command that returns the url
    std::string search = "youtube-dl -g 'ytsearch:" + title + "' "
        + "-f 'bestvideo'";
    auto pipe = popen(search.c_str(), "r");

    if (!pipe) throw std::runtime_error("popen() failed!");

    while (!feof(pipe)) {
        if (fgets(buffer.data(), 128, pipe) != nullptr)
            result += buffer.data();
    }

    auto rc = pclose(pipe);

    if (rc == EXIT_FAILURE) {
        std::cout << "No video was found" << std::endl;
    }

    // Remove extra new lines from output
    result.erase(std::remove(result.begin(), result.end(), '\n'), result.end());
    return result;
}


// Load a new video on the VLC player
void VLCWindow::load_video(const std::string url) {
    log("Playing video", debug);

    // Media instance
    libvlc_media_t *media = libvlc_media_new_location(instance, url.c_str());
    if (!media) throw std::runtime_error("No media found");
    libvlc_media_player_set_media(player, media);
    libvlc_media_release(media);
}

// Print the song lyrics
void VLCWindow::print_lyrics(std::string name) {
    std::cout << "\033[4m" << name << "\033[0m\n";
    // TODO
}

// Play/Pause the video
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

// Set the position in milliseconds of the VLC media playing
void VLCWindow::set_position(int ms) {
    log("Position moved to " + std::to_string(ms));
    libvlc_media_player_set_time(player, ms);
}

// Initialize all dbus variables
DbusPlayer::DbusPlayer(bool debug, bool fullscreen) : player(debug, fullscreen) {
}

// Wait for changes in the dbus data
void DbusPlayer::wait() {
    while(1) {}
}

// Log a formatted message if debug is enabled
void log(std::string msg, bool debug) {
    if (debug) {
        std::cout << "\033[92m" << ">> " << msg << "\033[0m" << std::endl;
    }
}

