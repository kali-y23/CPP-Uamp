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
            Tags *tags = new Tags(finf.absoluteFilePath().toStdString());
            // emit addToQueue(tags);
            emit addSongToTreeView(*tags);
        }
    }
    else {
        Tags *tags = new Tags(path.toStdString());
        emit addSongToTreeView(*tags);
    }
}
