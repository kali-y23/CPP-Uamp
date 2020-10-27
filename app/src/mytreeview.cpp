#include "mytreeview.h"

MyTreeView::MyTreeView(const Mediator *mediator) : Component(mediator) {
    model_filesystem = new QFileSystemModel();
    model_filesystem->setRootPath(QDir::homePath());

    setModel(model_filesystem);
    setRootIndex(model_filesystem->index(QDir::homePath()));

    hideColumn(1);
    hideColumn(2);
    hideColumn(3);

    context_menu = new QMenu(this);
    action_import = new QAction(("Import song or songs from directory"), this);

    // connect(action_import, SIGNAL(triggered()), SLOT(slotRemove())); add to DB && to tree view

    context_menu->addAction(action_import);
}

MyTreeView::~MyTreeView() {
    delete model_filesystem;
    delete context_menu;
    delete action_import;
}

void MyTreeView::mouseDoubleClickEvent(QMouseEvent *event) {
    QModelIndex index = currentIndex();

    if (!model_filesystem->isDir(index)) {
        // addToDB
        // addToTableView
    }
    else {
        expand(index);
    }
}

void MyTreeView::mousePressEvent(QMouseEvent *event) {
    QTreeView::mousePressEvent(event);
    if (event->button() == Qt::RightButton)
        context_menu->popup(this->mapToGlobal(event->pos()));
}
