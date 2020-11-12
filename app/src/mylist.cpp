#include "mylist.h"

MyList::MyList(const Mediator *mediator, QWidget *parent) :
                        QListView(parent), Component(mediator)
{
    setModel(model);
    setContextMenuPolicy(Qt::CustomContextMenu);
    setAlternatingRowColors(true);
    
    mainMenu = new QMenu(this);
    removeAction = new QAction(tr("&Remove playlist"), this);
    importAction = new QAction(tr("&Import playlist"), this);
    exportAction = new QAction(tr("&Export playlist"), this);


    connect(this, SIGNAL(clicked(const QModelIndex &)), this, SLOT(getSelected(const QModelIndex &)));
    connect(this, SIGNAL(getSelected(int)), reinterpret_cast<const QObject *>(mediator), SLOT(selectPlaylist(int)));
    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(showContextMenuRequested(const QPoint &))); 
    connect(removeAction, SIGNAL(triggered()), this, SLOT(removePlaylist()));
    connect(this , SIGNAL(removePlaylist(int)), reinterpret_cast<const QObject *>(mediator), SLOT(removePlaylist(int)));
}

MyList::~MyList()
{

}

void MyList::removePlaylist() {
    emit removePlaylist(model->data(currentIndex().row())->getId());
    model->remove(currentIndex());
}

void MyList::getSelected(const QModelIndex &index) {
    emit getSelected(model->data(index.row())->getId());
}

void MyList::showContextMenuRequested(const QPoint &pos) {
    QModelIndex index = indexAt(pos);

    mainMenu->clear();
    if (index.isValid()) {
        mainMenu->addAction(removeAction);
        mainMenu->addAction(exportAction);
    }
    else {
        mainMenu->addAction(importAction);
    }
    mainMenu->popup(viewport()->mapToGlobal(pos));
}
