#include <iostream>
#include <vlc/vlc.h>

#ifndef PLAYER_LIB
#define PLAYER_LIB

class VLCWindow {
    public:
        VLCWindow(bool debug, bool fullscreen);
        ~VLCWindow() = default; // Todo

        void play();
        void pause();
        void toggle_pause();
        void get_url();
        void load_video(std::string url);
        void set_position();
    private:
        // VLC Instance
        libvlc_instance_t *instance;
        libvlc_media_player_t *player;

        // Config
        bool debug;
        bool fullscreen;
};

class WebPlayer {
    public:
        std::string format_name();
        void start_video(std::string url);
        void wait();
    private:
};

class DbusPlayer {
    public:
        DbusPlayer(bool debug, bool fullscreen);
        ~DbusPlayer() = default; // TODO
        
        std::string asd = "aaaaaaaaaaaa";
        VLCWindow player;
        void wait();
    private:
};

#endif // PLAYER_LIB
