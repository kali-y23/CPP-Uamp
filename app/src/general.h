#pragma once

#include <QtWidgets>

#include "component.h"
#include "qplayer.h"
#include "qsidebar.h"

class Component;
class Mediator;
class QPlayer;
class QSideBar;

class GeneralScreen : public QWidget, public Component
{
    Q_OBJECT

private:
    QWidget *central_widget;

    QHBoxLayout *layout_outer;
    QVBoxLayout *layout_inner;
    QSplitter *splitter;

    QMenuBar *menuBar;

    QSideBar *sidebar_widget;
    QWidget *content_widget;
    QTableView *view_songs;
    QPlayer *player;

public:
    explicit GeneralScreen(Mediator *mediator, QWidget *parent = nullptr);
    ~GeneralScreen();

};
