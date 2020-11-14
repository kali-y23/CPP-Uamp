#include "tags.h"

    // TagLib::String title, artist, album, genre, fullPath;
    // int year, trackNumber;
bool Tags::operator==(const Tags *other) {
    if (getTitle() == other->getTitle() && getArtist() == other->getArtist()
        && getAlbum() == other->getAlbum() && getGenre() == other->getGenre()
        && getYear() == other->getYear() && getTrack() == other->getTrack()
        && getExt() == other->getExt()) {
        return true;
    }
    return false;
}

QVariant Tags::check(TagLib::String tag) const {
    if (tag.isEmpty()) {
        return "Unknown";
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
    album_cover = new QPixmap(":no_cover.jpg");
}

Tags::Tags(const std::string& path)
{
    QFileInfo info(path.c_str());

    ext = info.completeSuffix();
    fullPath = path;
    if (info.isReadable()) {
        f = TagLib::FileRef(path.c_str());
        extractAlbumCover(f);

        if (!f.isNull() && f.tag()) {
            TagLib::Tag *tag = f.tag();

            artist = tag->artist();
            title = tag->title();
            if (title.isEmpty()) {
                QFileInfo info(path.c_str());
                title = info.baseName().toStdString();
            }
            album = tag->album();
            genre = tag->genre();
            year = tag->year();
            trackNumber = tag->track();
        }
    }
    else {
        setAllTagsView("You do not have permissions to read this file.");
    }
}

Tags::Tags(const std::string& title_, const std::string& artist_,
           const std::string& album_, const std::string& genre_,
           int year_, int trackNumber_, const std::string& fullPath_) :
           title(title_), artist(artist_), album(album_), genre(genre_), fullPath(fullPath_),
           year(year_), trackNumber(trackNumber_)
{
    f = TagLib::FileRef(fullPath.toCString());
    album_cover = nullptr;
    extractAlbumCover(f);
}

Tags::Tags(Tags *other) :
           title(other->title), artist(other->artist), album(other->album), genre(other->genre), fullPath(other->fullPath),
           year(other->year), trackNumber(other->trackNumber), album_cover(other->album_cover) {

}

Tags::~Tags() {
    delete album_cover;
}

QString Tags::getExt() const {
    return ext;
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

QPixmap *Tags::getImage() const {
    return album_cover;
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

