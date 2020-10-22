#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
                        QMainWindow(parent)
{
    central_widget = new QWidget(this);
    setCentralWidget(central_widget);
    setGeometry(200, 200, 1800, 1000);

    sidebar_widget = new QWidget(central_widget);
    content_widget = new QWidget(central_widget);

    initToolbar();
    menuBar = new QMenuBar(this);

    layout_outer = new QHBoxLayout(central_widget);
    splitter = new QSplitter(central_widget);
    layout_outer->addWidget(splitter);

    splitter->addWidget(sidebar_widget);
    splitter->addWidget(content_widget);
    splitter->setSizes({150, 700});

    layout_inner = new QVBoxLayout(content_widget);
    player = new QPlayer(content_widget);
    view_songs = new QTableView(content_widget);
    layout_inner->addWidget(player);
    layout_inner->addWidget(view_songs);
}

MainWindow::~MainWindow()
{

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
