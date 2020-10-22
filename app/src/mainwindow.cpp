#include "mainwindow.h"

MainWindow::MainWindow(Mediator *mediator, QWidget *parent) :
                        QMainWindow(parent), Component(mediator)
{
    setGeometry(200, 200, 1800, 1000);
    initToolbar();
}

MainWindow::~MainWindow()
{
//
}

void MainWindow::initToolbar() {
    toolBar = new QToolBar(this);
    toolBar->setAllowedAreas(Qt::LeftToolBarArea);
    toolBar->setFloatable(false);
    toolBar->setOrientation(Qt::Vertical);
    toolBar->setMovable(false);
    toolBar->addAction("foo");
    toolBar->addAction("bar");
    addToolBar(Qt::LeftToolBarArea, toolBar);
}
