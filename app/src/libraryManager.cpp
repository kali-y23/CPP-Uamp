#include "libraryManager.h"

LibraryManager::LibraryManager(Mediator *mediator) : Component(mediator) {
    QObject::connect(this, SIGNAL(addSongToTreeView(Tags *)), reinterpret_cast<QObject *>(mediator), SLOT(slotAddSong(Tags *)));
}

LibraryManager::~LibraryManager() {
    delete m_ptxtMask;
}

QLineEdit *LibraryManager::getMask() const {
    return m_ptxtMask;
}

void LibraryManager::addSongsToLibrary(const QString& path, bool recursive) {
    QFileInfo info(path);

    if (info.isDir()) {
        QDir dir(path);
        QList<QFileInfo> files = dir.entryInfoList(m_ptxtMask->text().split(" "), QDir::Files);
        QList<QFileInfo> dirs = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);

        if (recursive)
            for (const QFileInfo &dirinf : dirs)
                addSongsToLibrary(dirinf.absoluteFilePath(), true);

        for (const QFileInfo& finf : files)
            processSong(finf.absoluteFilePath());
    }
    else
        processSong(path);
}

void LibraryManager::processSong(const QString &path) {
    Tags *tags = new Tags(path.toStdString());

    if (saveToDb(tags)) {
        emit addSongToTreeView(tags);
    }
}

bool LibraryManager::saveToDb(Tags *tags) {
    QSqlQuery query(QSqlDatabase::database("myDb"));
    int songId = 0;
    QString filePath = QDir::homePath() + "/.uamp/" + tags->getArtist().toString() + "/" + tags->getAlbum().toString() + "/";
    QString fileName = filePath + tags->getTitle().toString() + "." + tags->getExt();

    query.prepare("SELECT id FROM songs WHERE path=:path;");
    query.bindValue(":path", fileName);
    query.exec();
    if (query.first() && !query.value(0).isNull()) {
        songId = query.value(0).toInt();
        query.prepare("SELECT * FROM user_songs, songs WHERE user_id=:user_id AND song_id=:song_id AND songs.id = user_songs.song_id;");
        query.bindValue(":user_id", mediator->user->getId());
        query.bindValue(":song_id", songId);
        query.exec();
        if (!query.first()) {
            query.prepare("INSERT INTO user_songs (user_id, song_id) VALUES (:user_id, :song_id);");
            query.bindValue(":user_id", mediator->user->getId());
            query.bindValue(":song_id", songId);
            query.exec();
            return 1;
        }
        return 0;
    }
    else {
        QDir appDir;

        appDir.mkpath(filePath);
        QFile::copy(tags->getPath().toString(), fileName);
        tags->setPath(fileName);
        query.prepare("INSERT INTO songs (title, artist, album, genre, year, number, path)\
                               VALUES (:title, :artist, :album, :genre, :year, :number, :path);");
        query.bindValue(":title", tags->getTitle().toString());
        query.bindValue(":artist", tags->getArtist().toString());
        query.bindValue(":album", tags->getAlbum().toString());
        query.bindValue(":genre", tags->getGenre().toString());
        query.bindValue(":year", tags->getYear().toInt());
        query.bindValue(":number", tags->getTrack().toInt());
        query.bindValue(":path", tags->getPath().toString());
        query.exec();
        query.prepare("SELECT last_insert_rowid();");
        query.exec();
        query.first();
        songId = query.value(0).toInt();
        query.prepare("INSERT INTO user_songs (user_id, song_id) VALUES (:user_id, :song_id);");
        query.bindValue(":user_id", mediator->user->getId());
        query.bindValue(":song_id", songId);
        query.exec();
    }
    return 1;
}

std::deque<Tags *> LibraryManager::getUserSongs() {
    std::deque<Tags *> data;
    QSqlQuery query(QSqlDatabase::database("myDb"));

    query.prepare("SELECT * FROM songs, user_songs ON user_songs.user_id=:user_id AND songs.id = user_songs.song_id;");
    query.bindValue(":user_id", mediator->user->getId());
    query.exec();
    while (query.next()) {
        Tags *tags = new Tags(query.value(1).toString().toStdString(), query.value(2).toString().toStdString(),
                              query.value(3).toString().toStdString(), query.value(4).toString().toStdString(),
                              query.value(5).toInt(), query.value(6).toInt(),
                              query.value(7).toString().toStdString());

        data.push_back(tags);
    }

    return data;
}

std::list<Playlist *> LibraryManager::getUserPlaylists() {
    std::list<Playlist *> data;

    return data;
}
