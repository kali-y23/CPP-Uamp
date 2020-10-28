#include "libraryManager.h"

LibraryManager::LibraryManager(Mediator *mediator) : Component(mediator) {
    QObject::connect(this, SIGNAL(addSongToTreeView(const Tags&)), reinterpret_cast<QObject *>(mediator), SLOT(slotAddSong(const Tags&)));
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
    Tags tags(path.toStdString());

    if (saveToDb(tags)) {
        emit addSongToTreeView(tags);
    }
}

bool LibraryManager::saveToDb(const Tags &tags) {
    QSqlQuery query(QSqlDatabase::database("myDb"));
    char *command = new char[1024];

    std::sprintf(command, "SELECT * FROM songs, user_songs ON songs.path = '%s' AND user_songs.user_id = '%d' AND songs.id = user_songs.song_id;",
                tags.getPath().toString().toStdString().c_str(), mediator->user->getId());
    if (!query.exec(command)) {
        qDebug() << "fail1";
        return 0;
    }
    if (!query.value(0).isNull()) {
        qDebug() << "already exists";
        return 0;
    }
    query.clear();
    std::sprintf(command, "INSERT INTO songs VALUES (%s, %s)", tags.getTitle().toString().toStdString().c_str(), tags.getPath().toString().toStdString().c_str());
    if (!query.exec(command)) {
        qDebug() << "fail2";
        return 0;
    }
    return 1;
}
