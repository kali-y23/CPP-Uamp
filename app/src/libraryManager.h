#pragma once

#include <QtWidgets>

#include "component.h"
#include "tags.h"

class LibraryManager : public QObject, public Component {
    Q_OBJECT

    QLineEdit *m_ptxtMask = new QLineEdit("*.mp3");

public:
    LibraryManager(Mediator *mediator);
    ~LibraryManager();

    QLineEdit * getMask() const;

private:
    void processSong(const QString& path) const;

public slots:
    void addSongsToLibrary(const QString& path);

signals:
    void addSongToTreeView(const Tags& tags);
};