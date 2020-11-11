#pragma once

#include <QtWidgets>

#include <iostream>
#include <string>
#include <map>
#include <vector>

class Playlist {
    QString name;
    int id;

public:
    Playlist(QString name_, int id_);
    ~Playlist();
};

