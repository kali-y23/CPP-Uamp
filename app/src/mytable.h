#pragma once

#include <QtWidgets>


#include "component.h"
#include "tags.h"
#include "mymodel.h"

class Component;
class Mediator;

class MyTable : public QTableView, public Component
{
    Q_OBJECT
    MyModel *m_model = new MyModel(QVector<Tags>());
public:
    explicit MyTable(Mediator *mediator, QWidget *parent = nullptr);
    ~MyTable();

};
