#pragma once

#include <QtWidgets>

#include "component.h"
#include "qplayer.h"
#include "qsidebar.h"
#include "mytable.h"

class Component;
class Mediator;
class QPlayer;
class QSideBar;
class MyTable;

class GeneralScreen : public QWidget, public Component
{
    Q_OBJECT

private:
    QVBoxLayout *layout_outer;
    QHBoxLayout *layout_inner;
    QSplitter *splitter;

    QMenuBar *menuBar;

    QSideBar *sidebar_widget;
    QWidget *content_widget;
    MyTable *view_songs;
    QPlayer *player;

public:
    explicit GeneralScreen(Mediator *mediator, QWidget *parent = nullptr);
    ~GeneralScreen();

    MyTable* getView() {
        return view_songs;
    }

public slots:
    void showInView(Tags *tags);
    void loadSongs();

};
