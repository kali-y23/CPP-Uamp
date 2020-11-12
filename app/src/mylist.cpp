#include "mylist.h"

MyList::MyList(const Mediator *mediator, QWidget *parent) :
                        QListView(parent), Component(mediator)
{
    setModel(model);
    setContextMenuPolicy(Qt::CustomContextMenu);
    setAlternatingRowColors(true);

    connect(this, SIGNAL(clicked(const QModelIndex &)), this, SLOT(getSelected(const QModelIndex &)));
    connect(this, SIGNAL(getSelected(int)), reinterpret_cast<const QObject *>(mediator), SLOT(selectPlaylist(int)));
}

MyList::~MyList()
{

}

void MyList::getSelected(const QModelIndex &index) {
    emit getSelected(model->data(index.row())->getId());
}
