#include "qsuperbutton.h"

#include <iostream>

QSuperButton::QSuperButton(ButtonType type, QWidget *parent) {
    index = 0;
    connect(this, SIGNAL(clicked()), this, SLOT(click()));

    if (type == ButtonType::Loop) {
        createLoopList();
        setIconSize({30, 30});
    }
    else if (type == ButtonType::Play) {
        createPlayList();
        setIconSize({50, 50});
    }
    else if (type == ButtonType::Shuffle) {
        createShuffleList();
        setIconSize({30, 30});
    }
    else if (type == ButtonType::Playlist) {
        createPlaylistList();
        setIconSize({30, 30});
    }

    setIcon(list[index]);
}

QSuperButton::~QSuperButton() {
    //
}

void QSuperButton::createLoopList(void) {
    QIcon ic1(":/repeat.png");
    QIcon ic2(":/repeat_on.png");
    QIcon ic3(":/repeat_one.png");

    list.push_back(ic1);
    list.push_back(ic2);
    list.push_back(ic3);
}

void QSuperButton::createPlayList(void) {
    QIcon ic1(":/play.png");
    QIcon ic2(":/pause.png");

    list.push_back(ic1);
    list.push_back(ic2);
}

void QSuperButton::createShuffleList(void) {
    QIcon ic1(":/shuffle.png");
    QIcon ic2(":/shuffle_on.png");

    list.push_back(ic1);
    list.push_back(ic2);
}

void QSuperButton::createPlaylistList(void) {
    QIcon ic1(":/playlist.png");
    QIcon ic2(":/playlist_on.png");

    list.push_back(ic1);
    list.push_back(ic2);
}

void QSuperButton::click() {
    if (index < list.size() - 1) {
        ++index;
    }
    else
        index = 0;
    setIcon(list[index]);
}

QPlayButton::QPlayButton(ButtonType type, QWidget *parent) :
            QSuperButton(type, parent)
{
    createPlaySignalList();
}

QPlayButton::~QPlayButton() {
    //
}

void QPlayButton::click() {
    if (index < signalsList.size() - 1) {
        ++index;
    }
    else
        index = 0;

    emit std::invoke(signalsList[index], this);
    setIcon(list[index]);
}

void QPlayButton::createPlaySignalList(void) {
    signalsList.push_back(&QPlayButton::stop);
    signalsList.push_back(&QPlayButton::play);
}