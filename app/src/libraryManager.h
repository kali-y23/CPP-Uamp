#pragma once

#include <QtWidgets>

#include "component.h"
#include "tags.h"

class LibraryManager : public QObject, public Component {
    Q_OBJECT

public:
    LibraryManager(Mediator *mediator);

private:
    void processSong(const QString& path) const;

public slots:
    void addSongsToLibrary(const QString& path);

signals:
    void addSongToTreeView(const Tags& tags);
};