#pragma once

#include <QtWidgets>

#include "component.h"
#include "tags.h"
#include "listmodel.h"

class Component;
class Mediator;

class MyList : public QListView, public Component
{
    Q_OBJECT
    ListModel *m_model = new ListModel(std::vector<Playlist *>());
public:
    explicit MyList(const Mediator *mediator, QWidget *parent = nullptr);
    ~MyList();

    ListModel* getModel() {
        return m_model;
    }

signals:


public slots:

};
