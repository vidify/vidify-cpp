#include <iostream>
#include <chrono>
#include <QtDBus>
#include <glib-2.0/glib-object.h>

#ifndef H_LINUX
#define H_LINUX


/*
 * DBus class to access the API information.
 * It contains a player of type P (because it can be VLC or mpv) to control it
 * directly from within this API, like pausing the video when DBus does.
 */
template <class P>
class DBusAPI {
public:
    DBusAPI(P videoPlayer);
    ~DBusAPI() = default;  // TODO
    
    P player;
    std::string artist;
    std::string title;
    bool is_playing;
    void wait();
private:
};


template <class P>
DBusAPI<P>::DBusAPI(P videoPlayer) {
    this->player = videoPlayer;

    // Connnect to DBus
    if (!QDBusConnection::sessionBus().isConnected()) {
        std::cerr << "ERROR: Cannot connect to the DBus session bus.\n";
        exit(1);
    }

    QDBusInterface mprisInterface = QDBusInterface("org.mpris.MediaPlayer2.spotify", "/org/mpris/MediaPlayer2", "org.mpris.MediaPlayer2");
    if (!mprisInterface.isValid()) {
        std::cerr << "ERROR: Cannot connect to the Spotify interface\n";
        exit(1);
    }

    QVariant metadata = mprisInterface.property("Metadata");
    exit(0);
}


// Wait for changes in the dbus data
template <class P>
void DBusAPI<P>::wait() {
    while(1) {}
}


// Playing videos with the DBus API
template <class P>
void playVideosDBus(P player, DBusAPI<P> spotify, bool lyrics) {
    while(1) {
        std::string name = "Arctic Monkeys";

        auto t_start = std::chrono::high_resolution_clock::now();
        std::string url = player.get_url(name);
        player.load_video(url);

        auto t_end = std::chrono::high_resolution_clock::now();
        int offset = std::chrono::duration<double, std::milli>(t_end - t_start).count();

        player.play();
        player.set_position(offset);

        if (lyrics) player.print_lyrics(name);

        spotify.wait();
    }
}


#endif  // H_LINUX
