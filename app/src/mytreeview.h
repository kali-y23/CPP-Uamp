#pragma once

#include "mainwindow.h"

// class Mediator;

class MyTreeView : public QTreeView, public Component {
    QFileSystemModel *model_filesystem;
    QMenu *context_menu;
    QAction *action_import;

public:
    MyTreeView(const Mediator *mediator);
    ~MyTreeView();

public slots:
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
};
