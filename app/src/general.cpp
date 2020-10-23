#include "general.h"

GeneralScreen::GeneralScreen(Mediator *mediator, QWidget *parent) :
                        QWidget(parent), Component(mediator)
{
    // sidebar_widget = new QSideBar(central_widget);
    // sidebar_widget->setObjectName("sidebar");
    content_widget = new QWidget(central_widget);

    menuBar = new QMenuBar(this);

    layout_outer = new QHBoxLayout(this);
    splitter = new QSplitter(this);
    layout_outer->addWidget(splitter);

    // splitter->addWidget(sidebar_widget);
    splitter->addWidget(content_widget);
    splitter->setSizes({150, 700});

    layout_inner = new QVBoxLayout(content_widget);
    player = new QPlayer(content_widget);
    view_songs = new QTableView(content_widget);
    layout_inner->addWidget(player);
    layout_inner->addWidget(view_songs);
}

GeneralScreen::~GeneralScreen()
{

}