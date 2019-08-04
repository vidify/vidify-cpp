#include <iostream>
#include <vlc/vlc.h>
#include <dbus/dbus.h>

#ifndef PLAYER_LIB
#define PLAYER_LIB

void log(std::string msg, bool debug = true);

class VLCWindow {
    public:
        VLCWindow(bool debug, bool fullscreen);
        ~VLCWindow() = default; // Todo

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
        libvlc_media_player_t *player;

        // Config
        bool debug;
        bool fullscreen;
};

class DBusPlayer {
    public:
        DBusPlayer(bool debug, bool fullscreen);
        ~DBusPlayer() = default; // TODO
        
        VLCWindow player;
        std::string artist;
        std::string title;
        bool is_playing;
        void wait();
    private:
        DBusConnection *connection;
        DBusError error;
        // GMainLoop *loop;
};

#endif // PLAYER_LIB
