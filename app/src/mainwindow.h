#pragma once

#include <string>
#include <iostream>

#include <QtWidgets>

#include "qplayer.h"
#include "mediator.h"
#include "qsidebar.h"

class QPlayer;
class QSideBar;

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

    QSideBar *sidebar_widget;
    QWidget *content_widget;
    QTableView *view_songs;
    QPlayer *player;

    Mediator *mediator = new Mediator;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void paintEvent(QPaintEvent *) override;

private:
    void initToolbar();
};
