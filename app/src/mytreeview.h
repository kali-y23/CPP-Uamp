#pragma once

#include "component.h"
#include <QtWidgets>


class Component;
class Mediator;

class MyTreeView : public QTreeView, public Component {
    Q_OBJECT

    QFileSystemModel *model_filesystem;
    QMenu *context_menu;
    QAction *action_import;

public:
    MyTreeView(const Mediator *mediator);
    ~MyTreeView();

signals:
    void songImported(const QString& path);

public slots:
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void importSong();

};
