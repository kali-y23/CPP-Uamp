#pragma once

#include <QtWidgets>

#include "component.h"
#include "mediator.h"


class Component;
class Mediator;

class MyTreeView : public QTreeView, public Component {
    Q_OBJECT

    QFileSystemModel *model_filesystem;
    QMenu *context_menu;
    QAction *action_import;
    QAction *action_import_recursive;

public:
    MyTreeView(const Mediator *mediator);
    ~MyTreeView();

signals:
    void songImported(const QString& path, bool recursive);

public slots:
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void importSong();
    void importSongRecursive();
};
