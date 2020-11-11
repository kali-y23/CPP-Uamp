#include "mylist.h"

MyList::MyList(const Mediator *mediator, QWidget *parent) :
                        QListView(parent), Component(mediator)
{
    setModel(m_model);
    setContextMenuPolicy(Qt::CustomContextMenu);
    setAlternatingRowColors(true);

    // connect(this, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(sendNextSong(const QModelIndex &)));
}

MyList::~MyList()
{

}
