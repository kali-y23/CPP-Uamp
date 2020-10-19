#pragma once

#include <string>
#include <iostream>

#include <QtWidgets>

#include "qplayer.h"

class QPlayer;

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QWidget *central_widget;

    QHBoxLayout *layout_outer;
    QVBoxLayout *layout_inner;
    QSplitter *splitter;

    QToolBar *toolBar;
    QMenuBar *menuBar;

    QWidget *sidebar_widget;
    QWidget *content_widget;
    QTableView *view_songs;
    QPlayer *player;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void initToolbar();
};
