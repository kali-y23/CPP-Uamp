#include "tags.h"

QVariant Tags::check(TagLib::String tag) const {
    if (tag.isEmpty()) {
        return "None";
    }
    return tag.toCString();
}

void Tags::setAllTagsView(TagLib::String str) {
    artist = str;
    title = str;
    album = str;
    genre = str;
    year = 0;
    trackNumber = 0;
}

Tags::Tags(const std::string& path) {
    fullPath = path;
    // if (read) {
    f = TagLib::FileRef(path.c_str());

    if (!f.isNull() && f.tag()) {
        TagLib::Tag *tag = f.tag();

        artist = tag->artist();
        title = tag->title();
        album = tag->album();
        genre = tag->genre();
        year = tag->year();
        trackNumber = tag->track();
    }
    // }
    // else {
    //     setAllTagsView("You do not have permissions to read this file.");
    // }
}

QVariant Tags::getTag(int column) const {
    std::vector<QVariant (Tags::*)(void) const> hash {
        &Tags::getTitle,
        &Tags::getArtist,
        &Tags::getAlbum,
        &Tags::getGenre,
        &Tags::getYear,
        &Tags::getTrack,
        &Tags::getPath
    };
    QVariant res = std::invoke(hash[column], this);

    return res;
}

void Tags::setTag(int column, const QVariant& value) {
    std::vector<void (Tags::*)(const QVariant& value)> hash {
        &Tags::setTitle,
        &Tags::setArtist,
        &Tags::setAlbum,
        &Tags::setGenre,
        &Tags::setYear,
        &Tags::setTrack,
        &Tags::setPath
    };

    if (!f.isNull() && f.tag()) {
        (this->*hash[column])(value);
        f.file()->save();
    }
}

QVariant Tags::getArtist() const {
    return check(artist);
}

QVariant Tags::getTitle() const {
    return check(title);
}

QVariant Tags::getAlbum() const {
    return check(album);
}

QVariant Tags::getGenre() const {
    return check(genre);
}

QVariant Tags::getPath() const {
    return check(fullPath);
}

QVariant Tags::getYear() const {
    return year;
}

QVariant Tags::getTrack() const {
    return trackNumber;
}

void Tags::setArtist(const QVariant& value) {
    TagLib::String newValue(value.toString().toStdString());
    TagLib::Tag *tag = f.tag();

    artist = newValue;
    tag->setArtist(newValue);
}

void Tags::setTitle(const QVariant& value) {
    TagLib::String newValue(value.toString().toStdString());
    TagLib::Tag *tag = f.tag();

    title = newValue;
    tag->setTitle(newValue);
}

void Tags::setAlbum(const QVariant& value) {
    TagLib::String newValue(value.toString().toStdString());
    TagLib::Tag *tag = f.tag();

    album = newValue;
    tag->setAlbum(newValue);
}

void Tags::setGenre(const QVariant& value) {
    TagLib::String newValue(value.toString().toStdString());
    TagLib::Tag *tag = f.tag();

    genre = newValue;
    tag->setGenre(newValue);
}

void Tags::setYear(const QVariant& value) {
    int newValue(value.toInt());
    TagLib::Tag *tag = f.tag();

    year = newValue;
    tag->setYear(newValue);
}

void Tags::setTrack(const QVariant& value) {
    int newValue(value.toInt());
    TagLib::Tag *tag = f.tag();

    trackNumber = newValue;
    tag->setTrack(newValue);
}

void Tags::setPath(const QVariant& value) {
    TagLib::String newValue(value.toString().toStdString());

    fullPath = newValue;
}

