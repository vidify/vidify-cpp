#include <iostream>
#include <vlc/vlc.h>

#ifndef PLAYER_LIB
#define PLAYER_LIB

class VLCWindow {
    public:
        VLCWindow();
        ~VLCWindow() = default; // Todo

        void play();
        void pause();
        void toggle_pause();
        void get_url();
        void start_video();
        void set_position();
    private:
        libvlc_media_player_t *vlc_player;
        libvlc_instance_t *vlc_instance;
};

class WebPlayer {
    public:
        std::string format_name();
        void start_video(std::string url);
        void wait();
    private:
};

#endif // PLAYER_LIB
