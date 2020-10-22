#include "general.h"

GeneralScreen::GeneralScreen(Mediator *mediator, QWidget *parent) :
                        QWidget(parent), Component(mediator)
{
    sidebar_widget = new QWidget(this);
    sidebar_widget->setObjectName("sidebar");
    content_widget = new QWidget(this);

    menuBar = new QMenuBar(this);

    layout_outer = new QHBoxLayout(this);
    splitter = new QSplitter(this);
    layout_outer->addWidget(splitter);

    splitter->addWidget(sidebar_widget);
    splitter->addWidget(content_widget);
    splitter->setSizes({150, 700});
}

GeneralScreen::~GeneralScreen()
{

}