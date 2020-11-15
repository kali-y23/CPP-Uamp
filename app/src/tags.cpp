#include "tags.h"
#include "stardelegate.h"

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
    rating = 0;
}

Tags::Tags(const std::string& path)
{
    QFileInfo info(path.c_str());

    ext = info.suffix();
    fullPath = path;
    if (info.isReadable()) {
        f = TagLib::FileRef(path.c_str());

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
            rating = 0;
        }
    }
    else {
        setAllTagsView("You do not have permissions to read this file.");
        valid = 0;
    }
}

Tags::Tags(int id_, const std::string& title_, const std::string& artist_,
           const std::string& album_, const std::string& genre_,
           int year_, int trackNumber_, int rating_, const std::string& fullPath_) :
           title(title_), artist(artist_), album(album_), genre(genre_), fullPath(fullPath_),
           id(id_), year(year_), trackNumber(trackNumber_), rating(rating_)
{
    f = TagLib::FileRef(fullPath_.c_str());
}

Tags::Tags(Tags *other) :
           title(other->title), artist(other->artist), album(other->album), genre(other->genre), fullPath(other->fullPath),
           year(other->year), trackNumber(other->trackNumber), rating(other->rating)
{
    f = TagLib::FileRef(fullPath.toCString());
}

QString Tags::getExt() {
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
        &Tags::getRating,
        &Tags::getPath
    };
    QVariant res = std::invoke(hash[column], this);

    return res;
}

QString getColunmName(int index) {
    std::map<int, QString> hash = {
        {0, "title"},
        {1, "artist"},
        {2, "album"},
        {3, "genre"},
        {4, "year"},
        {5, "number"},
        {6, "rating"}
    };

    return "UPDATE songs SET " + hash[index] + "=:value WHERE id=:id;";
}

void Tags::setTag(int column, const QVariant& value) {
    std::vector<void (Tags::*)(const QVariant& value)> hash {
        &Tags::setTitle,
        &Tags::setArtist,
        &Tags::setAlbum,
        &Tags::setGenre,
        &Tags::setYear,
        &Tags::setTrack,
        &Tags::setRating,
        &Tags::setPath
    };

    if (!f.isNull() && f.tag()) {
        (this->*hash[column])(value);
        f.file()->save();
        if (column == 6 && (value.toInt() < 0 || value.toInt() > 5)) {
            return;
        }
        QSqlQuery query(QSqlDatabase::database("myDb"));

        query.prepare(getColunmName(column));
        query.bindValue(":value", value.toString());
        query.bindValue(":id", id);
        query.exec();
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

QVariant Tags::getRating() const {
    return QVariant::fromValue(StarRating(rating));
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

void Tags::setRating(const QVariant& value) {
    int newValue(value.toInt());

    if (newValue >= 0 && newValue <= 5) { 
        rating = newValue;
    }
}

void Tags::setPath(const QVariant& value) {
    TagLib::String newValue(value.toString().toStdString());

    fullPath = newValue;
}


void Tags::setId(int value) {
    id = value;
}

int Tags::getId() {
    return id;
}
