#include "libraryManager.h"

LibraryManager::LibraryManager(Mediator *mediator) : Component(mediator) {
    QObject::connect(this, SIGNAL(addSongToTreeView(Tags *)), reinterpret_cast<QObject *>(mediator), SLOT(slotAddSong(Tags *)));
    QObject::connect(this, SIGNAL(addPlaylist(Playlist *)), reinterpret_cast<QObject *>(mediator), SLOT(slotAddPlaylist(Playlist *)));
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

int LibraryManager::processSong(const QString &path) {
    Tags *tags = new Tags(path.toStdString());
    int songId = 0;

    if (saveToDb(tags, &songId)) {
        emit addSongToTreeView(tags);
    }
    return songId;
}

bool LibraryManager::saveToDb(Tags *tags, int *songId) {
    QSqlQuery query(QSqlDatabase::database("myDb"));
    QString filePath = QDir::homePath() + "/.uamp/" + tags->getArtist().toString() + "/" + tags->getAlbum().toString() + "/";
    QString fileName = filePath + tags->getTitle().toString() + "." + tags->getExt();

    query.prepare("SELECT id FROM songs WHERE path=:path;");
    query.bindValue(":path", fileName);
    query.exec();
    if (query.first() && !query.value(0).isNull()) {
        *songId = query.value(0).toInt();
        query.prepare("SELECT * FROM user_songs, songs WHERE user_id=:user_id AND song_id=:song_id AND songs.id = user_songs.song_id;");
        query.bindValue(":user_id", mediator->user->getId());
        query.bindValue(":song_id", *songId);
        query.exec();
        if (!query.first()) {
            query.prepare("INSERT INTO user_songs (user_id, song_id) VALUES (:user_id, :song_id);");
            query.bindValue(":user_id", mediator->user->getId());
            query.bindValue(":song_id", *songId);
            query.exec();
            tags->setId(*songId);
            return 1;
        }
        return 0;
    }
    else {
        QFileInfo info(tags->getPath().toString());
        
        if (tags->valid && info.exists() && info.isReadable()) {
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
            query.bindValue(":path", fileName);
            query.exec();
            query.prepare("SELECT last_insert_rowid();");
            query.exec();
            query.first();
            *songId = query.value(0).toInt();
            query.prepare("INSERT INTO user_songs (user_id, song_id) VALUES (:user_id, :song_id);");
            query.bindValue(":user_id", mediator->user->getId());
            query.bindValue(":song_id", *songId);
            query.exec();
            tags->setId(*songId);
            return 1;
        }
    }
    return 0;
}

std::deque<Tags *> LibraryManager::getUserSongs() {
    std::deque<Tags *> data;
    QSqlQuery query(QSqlDatabase::database("myDb"));

    query.prepare("SELECT * FROM songs, user_songs ON user_songs.user_id=:user_id AND songs.id = user_songs.song_id;");
    query.bindValue(":user_id", mediator->user->getId());
    query.exec();
    while (query.next()) {
        Tags *tags = new Tags(query.value(0).toInt(), query.value(1).toString().toStdString(),
                              query.value(2).toString().toStdString(),query.value(3).toString().toStdString(),
                              query.value(4).toString().toStdString(), query.value(5).toInt(),
                              query.value(6).toInt(), query.value(7).toString().toStdString());

        data.push_back(tags);
    }

    return data;
}

std::deque<Tags *> LibraryManager::getPlaylistSongs(int playlistId) {
    std::deque<Tags *> data;
    QSqlQuery query(QSqlDatabase::database("myDb"));

    query.prepare("SELECT * FROM songs INNER JOIN user_songs INNER JOIN playlist_content ON user_songs.user_id=:user_id AND songs.id = user_songs.song_id\
                   AND playlist_content.playlist_id=:playlist_id AND playlist_content.song_id=songs.id;");
    query.bindValue(":user_id", mediator->user->getId());
    query.bindValue(":playlist_id", playlistId);
    query.exec();
    while (query.next()) {
        Tags *tags = new Tags(query.value(0).toInt(), query.value(1).toString().toStdString(),
                              query.value(2).toString().toStdString(),query.value(3).toString().toStdString(),
                              query.value(4).toString().toStdString(), query.value(5).toInt(),
                              query.value(6).toInt(), query.value(7).toString().toStdString());

        data.push_back(tags);
    }

    return data;
}

void LibraryManager::getUserPlaylists() {
    QSqlQuery query(QSqlDatabase::database("myDb"));

    query.prepare("SELECT * FROM playlists WHERE user_id=:user_id");
    query.bindValue(":user_id", mediator->user->getId());
    query.exec();
    while (query.next()) {
        Playlist *playlist = new Playlist(query.value(1).toString(), query.value(0).toInt());

        emit addPlaylist(playlist);
    }
}

void LibraryManager::createPlaylist(const QString& text) {
    if (savePlaylist(text)) {
        QSqlQuery query(QSqlDatabase::database("myDb"));
        int Id;

        query.prepare("SELECT last_insert_rowid();");
        query.exec();
        query.first();
        Id = query.value(0).toInt();
        Playlist *playlist = new Playlist(text, Id);
        emit addPlaylist(playlist);
    }
}

bool LibraryManager::savePlaylist(const QString& text) {
    QSqlQuery query(QSqlDatabase::database("myDb"));

    query.prepare("INSERT INTO playlists (name, user_id) VALUES (:name, :user_id);");
    query.bindValue(":user_id", mediator->user->getId());
    query.bindValue(":name", text);
    if (query.exec()) {
        return 1;
    }
    return 0;
}

void LibraryManager::addSongToPlaylist(int playlistId, int songId) {
    QSqlQuery query(QSqlDatabase::database("myDb"));

    query.prepare("SELECT * FROM playlist_content WHERE playlist_id=:playlist_id AND song_id=:song_id");
    query.bindValue(":playlist_id", playlistId);
    query.bindValue(":song_id", songId);
    query.exec();
    if (!query.first()) {
        query.prepare("INSERT INTO playlist_content (playlist_id, song_id) VALUES (:playlist_id, :song_id);");
        query.bindValue(":playlist_id", playlistId);
        query.bindValue(":song_id", songId);
        query.exec();
    }
}

void LibraryManager::deleteFromLibrary(int songId) {
    QSqlQuery query(QSqlDatabase::database("myDb"));

    query.prepare("DELETE FROM songs WHERE id=:song_id;");
    query.bindValue(":song_id", songId);
    query.exec();
    query.prepare("DELETE FROM user_songs WHERE song_id=:song_id;");
    query.bindValue(":song_id", songId);
    query.exec();
    query.prepare("SELECT id FROM playlists WHERE user_id=:user_id");
    query.bindValue(":user_id", mediator->user->getId());
    query.exec();
    while (query.next()) {
        int playlistId = query.value(0).toInt();
        query.prepare("DELETE FROM playlist_content WHERE playlist_id=:playlist_id AND song_id=:song_id;");
        query.bindValue(":playlist_id", playlistId);
        query.bindValue(":song_id", songId);
        query.exec();
    }
}

void LibraryManager::deleteFromPlaylist(int playlistId, int songId) {
    QSqlQuery query(QSqlDatabase::database("myDb"));

    query.prepare("DELETE FROM playlist_content WHERE playlist_id=:playlist_id AND song_id=:song_id;");
    query.bindValue(":playlist_id", playlistId);
    query.bindValue(":song_id", songId);
    query.exec();
}

void LibraryManager::deletePlaylist(int id) {
    QSqlQuery query(QSqlDatabase::database("myDb"));

    query.prepare("DELETE FROM playlists WHERE id=:id");
    query.bindValue(":id", id);
    query.exec();
    query.prepare("DELETE FROM playlist_content WHERE playlist_id=:playlist_id");
    query.bindValue(":playlist_id", id);
    query.exec();
}

void LibraryManager::importPlaylist(QString path) {
    QFileInfo info(path);
    QString name = info.baseName();
    std::ifstream file(path.toStdString());

    if (savePlaylist(name)) {
        QSqlQuery query(QSqlDatabase::database("myDb"));
        std::string line;
        int playlistId, songId;

        query.prepare("SELECT last_insert_rowid();");
        query.exec();
        query.first();
        playlistId = query.value(0).toInt();
        Playlist *playlist = new Playlist(name, playlistId);
        emit addPlaylist(playlist);
        if (file.is_open()) {
            while (std::getline(file, line)) {
                if (std::regex_match (line, std::regex(".*\.[(mp3) | (mp4)]"))) {
                    if (line.find("file:") == 0) {
                        songId = processSong(line.substr(5).c_str());
                    }
                    else {
                        songId = processSong(line.c_str());
                    }
                    addSongToPlaylist(playlistId, songId);
                }
            }
            file.close();
        }
    }
}