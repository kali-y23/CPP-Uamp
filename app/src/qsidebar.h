#pragma once

#include "mainwindow.h"

class QSideBar : public QWidget {
    Q_OBJECT

    QStackedLayout *layout_main;

    QWidget *widget_treeview;
    QVBoxLayout *layout_treeview;
    QFileSystemModel *model_filesystem;
    QTreeView *tree_view;

public:
    QSideBar(QWidget *parent = nullptr);
    ~QSideBar();

    void hideTreeView();
    void showTreeView();

private:
    void setupTreeView();
};
