#include "general.h"

GeneralScreen::GeneralScreen(Mediator *mediator, QWidget *parent) :
                        QWidget(parent), Component(mediator)
{
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
    splitter->setSizes({150, 700, 150});
}

GeneralScreen::~GeneralScreen()
{

}

void GeneralScreen::showInView(Tags *tags) {
    getView()->getModel()->addData(tags);
}

void GeneralScreen::loadSongs() {
    std::deque<Tags *> data = mediator->getLibraryManager()->getUserSongs();

    getView()->getModel()->setNewData(std::move(data));
    getQueue()->setQueue(data);
}