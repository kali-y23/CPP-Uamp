#include "general.h"

MyTable::MyTable(Mediator *mediator, QWidget *parent) :
                        QTableView(parent), Component(mediator)
{
    setModel(m_model);
}

MyTable::~MyTable()
{

}