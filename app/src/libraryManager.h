#pragma once

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtWidgets>
#include <string>
#include <cstdio>
#include <deque>

#include "component.h"
#include "mediator.h"
#include "tags.h"

class Component;
class Mediator;

class LibraryManager : public QObject, public Component {
    Q_OBJECT

    QLineEdit *m_ptxtMask = new QLineEdit("*.mp3 *.flac *.wav *.mp4");

    void processSong(const QString& path);
    bool saveToDb(Tags *tags);

public:
    LibraryManager(Mediator *mediator);
    ~LibraryManager();

    QLineEdit * getMask() const;
    std::deque<Tags *> getUserSongs();

public slots:
    void addSongsToLibrary(const QString& path, bool recursive);

signals:
    void addSongToTreeView(Tags *tags);
};