#include "qsidebar.h"
//     QWidget *widget_treeview;
//     QFileSystemModel *model_filesystem;
//     QTreeView *tree_view;

// public:
//     QSideBar(QWidget *parent = nullptr);
//     ~QSideBar();

//     hideTreeView();
//     showTreeView();

// private:
//     setupTreeView();

QSideBar::QSideBar(QWidget *parent) {
    layout_main = new QStackedLayout;
    setupTreeView();

    layout_main->addWidget(widget_treeview);
}

QSideBar::~QSideBar() {
    //
}

void QSideBar::showTreeView() {
    widget_treeview->hide();
}

void QSideBar::hideTreeView() {
    widget_treeview->show();
}

void QSideBar::setupTreeView() {
    widget_treeview = new QWidget(this);
    layout_treeview = new QVBoxLayout(this);
    model_filesystem = new QFileSystemModel;
    tree_view = new QTreeView(this);

    model_filesystem->setRootPath(QDir::currentPath());
    tree_view->setModel(model_filesystem);
    layout_treeview->addWidget(tree_view);
}


