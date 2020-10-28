#pragma once

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtWidgets>
#include <string>
#include <cstdio>

#include "component.h"
#include "mediator.h"
#include "tags.h"

class Component;
class Mediator;

class LibraryManager : public QObject, public Component {
    Q_OBJECT

    QLineEdit *m_ptxtMask = new QLineEdit("*.mp3");

    void processSong(const QString& path);
    bool saveToDb(const Tags& tags);

public:
    LibraryManager(Mediator *mediator);
    ~LibraryManager();

    QLineEdit * getMask() const;

public slots:
    void addSongsToLibrary(const QString& path);

signals:
    void addSongToTreeView(const Tags& tags);
};