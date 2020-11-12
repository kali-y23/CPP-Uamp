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
    ListModel *model = new ListModel(std::vector<Playlist *>());
    QMenu* mainMenu;
    QAction* removeAction;
    QAction* importAction;
    QAction* exportAction;
    
public:
    explicit MyList(const Mediator *mediator, QWidget *parent = nullptr);
    ~MyList();

    ListModel* getModel() {
        return model;
    }

signals:
    void getSelected(int id);
    void removePlaylist(int id);

public slots:
    void getSelected(const QModelIndex &index);
    void showContextMenuRequested(const QPoint &pos);
    void removePlaylist();
};
