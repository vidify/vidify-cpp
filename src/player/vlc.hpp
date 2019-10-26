#include <iostream>
#include <vlc/vlc.h>

#ifndef H_PLAYER
#define H_PLAYER


class VLCPlayer {
public:
    VLCPlayer();
    ~VLCPlayer() = default; // Todo

    void play();
    void pause();
    void toggle_pause();
    std::string get_url(std::string title);
    void load_video(std::string url);
    void set_position(int ms);
    void print_lyrics(std::string name);
private:
    // VLC Instance
    libvlc_instance_t *instance;
    libvlc_media_player_t *mediaPlayer;
};


#endif  // H_PLAYER
