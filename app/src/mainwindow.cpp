#include "mainwindow.h"

MainWindow::MainWindow(Mediator *mediator, QWidget *parent) :
                        QMainWindow(parent), Component(mediator)
{
    setCentralWidget(new QWidget(this));
    layoutOuter = new QStackedLayout(centralWidget());
    resize(1200, 700);
    initToolbar();
}

MainWindow::~MainWindow()
{
}

void MainWindow::initToolbar() {
    actionLibrary = new QAction("Library");
    actionPlaylists = new QAction("Playlists");
    actionSignOut = new QAction("Sign Out");
    toolBar = new QToolBar(this);

    toolBar->setAllowedAreas(Qt::LeftToolBarArea);
    toolBar->setFloatable(false);
    toolBar->setOrientation(Qt::Vertical);
    toolBar->setMovable(false);
    toolBar->addAction(actionLibrary);
    toolBar->addAction(actionPlaylists);
    toolBar->addAction(actionSignOut);
    addToolBar(Qt::LeftToolBarArea, toolBar);
    toolBar->hide();

    // connect(actionLibrary, SIGNAL(triggered()), mediator, SLOT(backToSignIn()));
    // connect(actionPlaylists, SIGNAL(triggered()), mediator, SLOT(backToSignIn()));
    QObject::connect(actionSignOut, SIGNAL(triggered()), mediator, SLOT(backToSignIn()));
}

void MainWindow::setWidget(QWidget *widget, bool tool) {
    layoutOuter->setCurrentWidget(widget);
    if (tool) {
        toolBar->show();
    }
    else {
        toolBar->hide();
    }
}

// void MainWindow::paintEvent(QPaintEvent *)
// {
//     QStyleOption opt;
//     opt.init(this);
//     QPainter p(this);
//     style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
// }
