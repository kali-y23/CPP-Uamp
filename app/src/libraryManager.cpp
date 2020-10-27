#include "libraryManager.h"

LibraryManager::LibraryManager(Mediator *mediator) : Component(mediator) {
    QObject::connect(this, SIGNAL(addSongToTreeView(const Tags&)), reinterpret_cast<QObject *>(mediator), SLOT(slotAddSong(const Tags&)));
}

void LibraryManager::addSongsToLibrary(const QString& path) {
    QFileInfo info(path);

    if (info.isDir()) {
        QDir dir(path);
        QList<QFileInfo> dirs = dir.entryInfoList(QDir::Files);

        for (const QFileInfo& finf : dirs) {
            // tags = processSong(finf.absoluteFilePath());
            Tags tags(finf.absoluteFilePath().toStdString());
            emit addSongToTreeView(tags);
        }
    }
    else {
        // tags = processSong(path);
        Tags tags(path.toStdString());
        emit addSongToTreeView(tags);
    }
}

// Tags LibraryManager::processSong(const QString &path) {
//     Tags tags(path.toStdString());

//     return tags;
//     // validate the song is a music file (??)

//     // read tags

//     // fill up the Tags struct 
// }
