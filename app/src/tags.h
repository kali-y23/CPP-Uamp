#pragma once

#include <QtWidgets>

#include "../../../taglib/taglib/tag.h"
#include <../../taglib/fileref.h>
#include <toolkit/tpropertymap.h>
#include <id3v2tag.h>

#include <iostream>
#include <string>
#include <map>
#include <vector>

typedef char *(*TagLib_StringHandler)(const char *);

class Tags {
    QString ext;
    TagLib::String title, artist, album, genre, fullPath;
    int year, trackNumber;
    TagLib::FileRef f;

    QVariant check(TagLib::String tag) const;

    void setAllTagsView(TagLib::String str);

public:
    Tags(const std::string& path);
    Tags(const std::string& title_, const std::string& artist_,
        const std::string& album_, const std::string& genre_,
        int year_, int trackNumber_, const std::string& fullPath_);

    QString getExt();

    QVariant getTag(int column) const;

    void setTag(int column, const QVariant& value);

    QVariant getArtist() const;

    QVariant getTitle() const;

    QVariant getAlbum() const;

    QVariant getGenre() const;

    QVariant getPath() const;

    QVariant getYear() const;

    QVariant getTrack() const;

    void setArtist(const QVariant& value);

    void setTitle(const QVariant& value);

    void setAlbum(const QVariant& value);

    void setGenre(const QVariant& value);

    void setYear(const QVariant& value);

    void setTrack(const QVariant& value);

    void setPath(const QVariant& value);
};

