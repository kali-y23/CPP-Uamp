#include "general.h"
#include <iostream>

GeneralScreen::GeneralScreen(Mediator *mediator, QWidget *parent) :
                        QWidget(parent), Component(mediator)
{
    view_songs = new MyTable(mediator, content_widget);
    queue_widget = new QueueWidget(mediator, content_widget);

    player = new QPlayer(mediator, this);
    menuBar = new QMenuBar(this);
    content_widget = new QWidget(this);
    layout_outer = new QVBoxLayout(this);

    layout_outer->addWidget(player);
    layout_outer->addWidget(content_widget);

    layout_inner = new QHBoxLayout(content_widget);
    splitter = new QSplitter;
    layout_inner->addWidget(splitter);

    sidebar_widget = new QSideBar(mediator, content_widget);
    sidebar_widget->setObjectName("sidebar");
    view_songs = new MyTable(mediator, content_widget);
    queue_widget = new QueueWidget(mediator, content_widget);

    splitter->addWidget(sidebar_widget);
    splitter->addWidget(view_songs);
    splitter->addWidget(queue_widget);
    splitter->setSizes({150, 700, 250});

    queue_widget->hide();

    connect(view_songs, SIGNAL(sendSongToPlayer(Tags *)), this, SLOT(updatePlayerData(Tags *)));
    connect(queue_widget, SIGNAL(sendSongToPlayer(Tags *)), this, SLOT(updatePlayerData(Tags *)));
    connect(queue_widget, SIGNAL(sendFirstSongToPlayer(Tags *)), player, SLOT(setData(Tags *)));
}

GeneralScreen::~GeneralScreen()
{

}

void GeneralScreen::showInView(Tags *tags) {
    getView()->getModel()->addData(tags);
}

void GeneralScreen::showInList(Playlist *playlist) {
    sidebar_widget->getList()->getModel()->addData(playlist);
}

void GeneralScreen::loadSongs() {
    std::deque<Tags *> data = mediator->getLibraryManager()->getUserSongs();

    getView()->getModel()->setNewData(std::move(data));
    getQueue()->setQueue(data);
}

void GeneralScreen::loadPlaylists() {
    std::vector<Playlist *> data = mediator->getLibraryManager()->getUserPlaylists();
    
    sidebar_widget->getList()->getModel()->setNewData(std::move(data));
}

void GeneralScreen::toggleQueue(void) {
    if (queue_widget->isVisible())
        queue_widget->hide();
    else
        queue_widget->show();
}

void GeneralScreen::updatePlayerData(Tags *tags) {
    getPlayer()->updateData(tags);
}


void GeneralScreen::changeSidebar(int index) {
    if (index == LIBRARY) {
        sidebar_widget->switchToTreeView();
    }
    if (index == PLAYLISTS) {
         sidebar_widget->switchToPlaylists();
    }
}