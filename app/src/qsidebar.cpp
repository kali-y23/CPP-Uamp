#include "qsidebar.h"

QSideBar::QSideBar(const Mediator *mediator, QWidget *parent) : 
                   QWidget(parent), Component(mediator) {
    layout_main = new QVBoxLayout(this);
    layout_stacked = new QStackedLayout;

    setupTreeView();

    layout_stacked->addWidget(widget_treeview);

    layout_main->addLayout(layout_stacked);
    setLayout(layout_main);

    switchToTreeView();
}

QSideBar::~QSideBar() {
    //
}

void QSideBar::switchToTreeView() {
    layout_stacked->setCurrentIndex(0);
}

void QSideBar::setupTreeView() {
    widget_treeview = new QWidget;
    layout_treeview = new QVBoxLayout(widget_treeview);
    tree_view = new MyTreeView(mediator);

    QLabel *label = new QLabel("  Choose a song or a directory with songs");
    layout_treeview->addWidget(label);
    layout_treeview->addWidget(tree_view);
}

// void QAbstractItemView::mouseDoubleClickEvent(QMouseEvent *event)
