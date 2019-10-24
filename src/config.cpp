#include <iostream>
#include <QApplication>
#include <QSettings>
#include "config.h"


template <typename T>
struct option {
    std::string section;
    T defaultValue;
};


void parseConfig() {
    QSettings settings("spotivids", "spotivids");
    settings.setPath(QSettings::IniFormat, QSettings::UserScope, "spotivids.conf");
    std::cout << "Config file at " << settings.fileName().toStdString() << std::endl;

    settings.beginGroup("/Defaults");
    std::cout << settings.value("fullscreen").toBool() << std::endl;
    std::cout << settings.value("test").toInt() << std::endl;
    settings.endGroup();
}
