#include "general.h"

MyTable::MyTable(Mediator *mediator, QWidget *parent) :
                        QTableView(parent), Component(mediator)
{
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setModel(m_model);
    setSortingEnabled(true);
    connect(this, SIGNAL(doubleClicked(const QModelIndex &)), reinterpret_cast<const QObject *> (mediator), SLOT(setPlaySong(const QModelIndex &)));
}

MyTable::~MyTable()
{

}