#include "vlc.h"
#include <iostream>
#include <algorithm>
#include <memory>
#include <array>
#include <vlc/vlc.h>


// Initialize the instance and the player
VLCPlayer::VLCPlayer() {
#ifdef DEBUG
    std::cout << "Initializing VLC" << std::endl;
#endif
    
    std::string args = "";
#ifdef DEBUG
    args += "--verbose=1";
#else
    args += "--quiet";
#endif

    const char *const vlc_args = args.c_str();
    instance = libvlc_new(2, &vlc_args);
    if (!instance) throw std::runtime_error("VLC couldn't be initialzed");

	mediaPlayer = libvlc_media_player_new(instance);
}


// Returns the url ouput from a youtube-dl search
std::string VLCPlayer::get_url(std::string title) {
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
void VLCPlayer::load_video(const std::string url) {
#ifdef DEBUG
    std::cout << "Playing video" << std::endl;
#endif

    // Media instance
    libvlc_media_t *media = libvlc_media_new_location(instance, url.c_str());
    if (!media) throw std::runtime_error("No media found");

    // Loading media on the player
    libvlc_media_player_set_media(mediaPlayer, media);
    libvlc_media_release(media);
}


// Print the song lyrics
void VLCPlayer::print_lyrics(std::string name) {
    std::cout << "\033[4m" << name << "\033[0m\n";
}


// Play/Pause the video
void VLCPlayer::play() {
    libvlc_media_player_play(mediaPlayer);
}


void VLCPlayer::pause() {
    libvlc_media_player_pause(mediaPlayer);
}


void VLCPlayer::toggle_pause() {
    if (libvlc_media_player_is_playing(mediaPlayer)) {
        pause();
    }
    else {
        play();
    }
}


// Set the position in milliseconds of the VLC media playing
void VLCPlayer::set_position(int ms) {
#ifdef DEBUG
    std::cout << "Position moved to " << ms << std::endl;
#endif
    libvlc_media_player_set_time(mediaPlayer, ms);
}
