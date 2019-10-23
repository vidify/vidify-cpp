#include "player.h"
#include <algorithm>
#include <iostream>
#include <memory>
#include <array>

#include <vlc/vlc.h>
#include <dbus/dbus.h>
#include <glib-2.0/glib-object.h>

#define SPOTIFY_BUS "org.mpris.MediaPlayer2.spotify"


// Initialize the instance and the player
VLCWindow::VLCWindow(bool args_fullscreen) {
    fullscreen = args_fullscreen;

#ifdef DEBUG
    std::cout << "Initializing VLC" << std::endl;
#endif
    
    std::string args = "";
#ifdef DEBUG
    args += "--verbose=0";
#else
    args += "--quiet";
#endif

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
    std::string search = "youtube-dl -g 'ytsearch:" + title + "' -f 'bestvideo'";

    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(search.c_str(), "r"), pclose);
    if (!pipe) throw std::runtime_error("popen() failed!");

    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    // Removing the extra new line at the end
    result.pop_back();

    return result;
}


// Load a new video on the VLC player
void VLCWindow::load_video(const std::string url) {
#ifdef DEBUG
    std::cout << "Playing video" << std::endl;
#endif

    // Media instance
    libvlc_media_t *media = libvlc_media_new_location(instance, url.c_str());
    if (!media) throw std::runtime_error("No media found");

    // Loading media on the player
    libvlc_media_player_set_media(player, media);
    libvlc_media_release(media);
    libvlc_set_fullscreen(player, fullscreen);
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
#ifdef DEBUG
    std::cout << "Position moved to " << ms << std::endl;
#endif
    libvlc_media_player_set_time(player, ms);
}

// Initialize all dbus variables
DBusPlayer::DBusPlayer(bool fullscreen) : player(fullscreen) {
    // Init the error structure
    dbus_error_init(&error);

    // Connnect to DBus
    connection = dbus_bus_get(DBUS_BUS_SYSTEM, &error);
    if (connection == nullptr) {
        perror(error.name);
        perror(error.message);
    }

    // Connect to the MPRIS player
}

// Wait for changes in the dbus data
void DBusPlayer::wait() {
    while(1) {}
}
