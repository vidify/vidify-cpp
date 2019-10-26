#include <iostream>
#include <QApplication>
#include <QSettings>
#include "config.hpp"


// Initializing the config by first parsing the file and then the arguments.
// This way the arguments config have priority over the file.
Config::Config(int argc, char *argv[]) {
    parseFile();
    parseArguments(argc, argv);
}


// Parsing the config file
void Config::parseFile() {
    QSettings settings("spotivids", "spotivids");
    settings.setPath(QSettings::IniFormat, QSettings::UserScope, "spotivids.conf");
    std::cout << "Config file at " << settings.fileName().toStdString() << std::endl;

    settings.beginGroup("/Defaults");
    lyrics.value = settings.value(lyrics.name, lyrics.value).toBool();
    fullscreen.value = settings.value(fullscreen.name, fullscreen.value).toBool();
    useMpv.value = settings.value(useMpv.name, useMpv.value).toBool();
    settings.endGroup();
}


// No arguments are supported as this C++ implementation intends to be
// fully a desktop app, with as little commandline interaction as possible.
// It could be implemented in the future but right now it isn't a priority.
void Config::parseArguments(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];

        if (arg == "--help" || arg == "-h") {
            printUsage();
            exit(0);
        }

        else if (arg == "--version" || arg == "-v") {
            printVersion();
            exit(0);
        }
    }
}


void Config::printUsage() {
    std::cout << "usage: spotivids [-h] [-v]\n\n"
        << "  -h, --help            show this help message and exit\n"
        << "  -v, --version         show the program's version and exit\n"
        << std::flush;
}


void Config::printVersion() {
    std::cout << "spotivids (C++) 1.0.0" << std::endl;
}
