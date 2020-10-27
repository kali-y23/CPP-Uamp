#pragma once

#include "mainwindow.h"

class QSideBar : public QWidget {
    Q_OBJECT

    QStackedLayout *layout_stacked;
    QVBoxLayout *layout_main;

    QWidget *widget_treeview;
    QVBoxLayout *layout_treeview;
    QFileSystemModel *model_filesystem;
    QTreeView *tree_view;

public:
    QSideBar(QWidget *parent = nullptr);
    ~QSideBar();

    void switchToTreeView();

private:
    void setupTreeView();
};
