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

void LibraryManager::addSongsToLibrary(const QString& path) {
    QFileInfo info(path);

    if (info.isDir()) {
        QDir dir(path);
        QList<QFileInfo> dirs = dir.entryInfoList(m_ptxtMask->text().split(" "), QDir::Files);

        for (const QFileInfo& finf : dirs) {
            processSong(finf.absoluteFilePath());
        }
    }
    else {
        processSong(path);
    }
}

void LibraryManager::processSong(const QString &path) {
    Tags *tags = new Tags(path.toStdString());

    if (saveToDb(tags)) {
        emit addSongToTreeView(tags);
    }
}

bool LibraryManager::saveToDb(Tags *tags) {
    QSqlQuery query(QSqlDatabase::database("myDb"));
    char *command = new char[1024];
    int songId = 0;

    std::sprintf(command, "SELECT id FROM songs WHERE path = '%s';",
                tags->getPath().toString().toStdString().c_str());
    query.exec(command);
    if (query.first() && !query.value(0).isNull()) {
        qDebug() << "already exists";
        query.first();
        songId = query.value(0).toInt();
        std::sprintf(command, "SELECT * FROM user_songs WHERE user_id = '%d' AND song_id = '%d' AND songs.id = user_songs.song_id;",
                    mediator->user->getId(), songId);
        query.exec(command);
        if (query.first() && !query.value(0).isNull()) {
            std::sprintf(command, "INSERT INTO user_songs (user_id, song_id) VALUES ('%d', '%d');",
                    mediator->user->getId(), songId);
            query.exec(command);
        }

        return 0;
    }
    else {
        std::sprintf(command, "INSERT INTO songs (title, artist, album, genre, year, number, path)\
                               VALUES ('%s', '%s', '%s', '%s', '%d', '%d', '%s');",
                    tags->getTitle().toString().toStdString().c_str(), tags->getArtist().toString().toStdString().c_str(),
                    tags->getAlbum().toString().toStdString().c_str(), tags->getGenre().toString().toStdString().c_str(),
                    tags->getYear().toInt(), tags->getTrack().toInt(),
                    tags->getPath().toString().toStdString().c_str());
        query.exec(command);
        std::sprintf(command, "SELECT last_insert_rowid();");
        query.exec(command);
        query.first();
        songId = query.value(0).toInt();
        std::sprintf(command, "INSERT INTO user_songs (user_id, song_id) VALUES ('%d', '%d');",
                    mediator->user->getId(), songId);
        query.exec(command);
    }
    return 1;
}

QVector<Tags *> LibraryManager::getUserSongs() {
    QVector<Tags *> data;
    QSqlQuery query(QSqlDatabase::database("myDb"));
    char *command = new char[1024];

    std::sprintf(command, "SELECT * FROM songs, user_songs ON user_songs.user_id = '%d' AND songs.id = user_songs.song_id;",
                    mediator->user->getId());
    query.exec(command);
    while (query.next()) {
        Tags *tags = new Tags(query.value(1).toString().toStdString(), query.value(2).toString().toStdString(),
                              query.value(3).toString().toStdString(), query.value(4).toString().toStdString(),
                              query.value(5).toInt(), query.value(6).toInt(),
                              query.value(7).toString().toStdString());

        data.push_back(tags);
    }

    return data;
}