#pragma once

#include <QtWidgets>
#include <QSqlDatabase>
#include <QSqlQuery>

#include "../../../taglib/taglib/tag.h"
#include <../../taglib/fileref.h>
#include <../../taglib/mpeg/mpegfile.h>
#include <../../taglib/ape/apefile.h>
#include <../../taglib/ape/apetag.h>
#include <../../taglib/asf/asffile.h>
#include <../../taglib/asf/asftag.h>
#include <../../taglib/flac/flacfile.h>
#include <../../taglib/mp4/mp4file.h>
#include <../../taglib/mp4/mp4tag.h>
#include <../../taglib/mpc/mpcfile.h>
#include <toolkit/tpropertymap.h>
#include <id3v2tag.h>

#include <iostream>
#include <string>
#include <map>
#include <vector>

class Tags {
    QString ext;
    TagLib::String title, artist, album, genre, fullPath;
    int id, year, trackNumber, rating = 0;
    TagLib::FileRef f;
    QPixmap *album_cover;

    QVariant check(TagLib::String tag) const;

    void setAllTagsView(TagLib::String str);

public:
    Tags(const std::string& path);
    Tags(int id, const std::string& title_, const std::string& artist_,
        const std::string& album_, const std::string& genre_,
        int year_, int trackNumber_, int rating_, const std::string& fullPath_);
    Tags(Tags *other);

    ~Tags();

    bool operator==(const Tags *other);

    QString getExt() const;

    QVariant getTag(int column) const;

    void setTag(int column, const QVariant& value);

    void extractAlbumCover(const TagLib::FileRef& fr);

    bool extractAPE(TagLib::APE::Tag* tag, TagLib::ByteVector& pic);
    bool extractID3(TagLib::ID3v2::Tag* tag, TagLib::ByteVector& pic);
    bool extractASF(TagLib::ASF::File* file, TagLib::ByteVector& pic);
    bool extractFLAC(TagLib::FLAC::File* file, TagLib::ByteVector& pic);
    bool extractMP4(TagLib::MP4::File* file, TagLib::ByteVector& pic);
    
    int getId();

    QVariant getArtist() const;

    QVariant getTitle() const;

    QVariant getAlbum() const;

    QVariant getGenre() const;

    QVariant getPath() const;

    QVariant getYear() const;

    QVariant getTrack() const;

    QPixmap *getImage() const;
    QVariant getRating() const;

    void setId(int value);

    void setArtist(const QVariant& value);

    void setTitle(const QVariant& value);

    void setAlbum(const QVariant& value);

    void setGenre(const QVariant& value);

    void setYear(const QVariant& value);

    void setTrack(const QVariant& value);

    void setPath(const QVariant& value);

    void setRating(const QVariant& value);

    int valid = 1;
};

