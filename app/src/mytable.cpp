#include "general.h"

MyTable::MyTable(Mediator *mediator, QWidget *parent) :
                        QTableView(parent), Component(mediator)
{
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setModel(m_model);
    setSortingEnabled(true);
    connect(this, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(sendNextSong(const QModelIndex &)));
}

MyTable::~MyTable()
{

}

void MyTable::sendNextSong(const QModelIndex &index) {
    emit sendSongToPlayer(getModel()->rowData(index));
}
