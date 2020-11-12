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
    MyModel *m_model = new MyModel(std::deque<Tags *>());
public:
    explicit MyTable(Mediator *mediator, QWidget *parent = nullptr);
    ~MyTable();

    MyModel* getModel() {
        return m_model;
    }

signals:
    void sendSongToPlayer(Tags *tags);
    void updateQueue(Tags *tags);

public slots:
    void sendNextSong(const QModelIndex &index);
};
