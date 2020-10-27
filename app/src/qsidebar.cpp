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
    model_filesystem = new QFileSystemModel;
    tree_view = new QTreeView;

    model_filesystem->setRootPath(QDir::currentPath());
    tree_view->setModel(model_filesystem);
    layout_treeview->addWidget(tree_view);
}


