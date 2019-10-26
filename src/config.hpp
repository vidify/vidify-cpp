#include <QApplication>


// A single config option with the argument names, the config file name and
// the section where it's located, and the default value.
template <typename T>
struct Option {
    QString name;
    QString section;
    T value;
};


// All the options available with their section in the config file and
// their default values.
struct Options {
    Option<bool>        lyrics{"lyrics", "Defaults", true};
    Option<bool>        fullscreen{"fullscreen", "Defaults", false};
    Option<bool>        useMpv{"use_mpv", "Defaults", false};
    Option<QString> vlcArgs{"vlc_args", "Defaults", ""};
    Option<QString> mpvFlags{"mpv_flags", "Defaults", ""};

    Option<bool>        useWebApi{"use_web_api", "WebAPI", false};
    Option<QString> clientId{"client_id", "WebAPI", ""};
    Option<QString> clientSecret{"client_secret", "WebAPI", ""};
    Option<QString> redirectUri{"redirect_uri", "WebAPI", "http://localhost:8888/callback/"};
    Option<QString> authToken{"auth_token", "WebAPI", ""};
    Option<int>         expiration{"expiration", "WebAPI", -1};
};


// The config interface with functions to parse both from the config file
// and from the arguments.
class Config : Options {
public:
    Config(int argc, char *argv[]);
    void printUsage();
    void printVersion();
private:
    void parseFile();
    void parseArguments(int argc, char *argv[]);
};
