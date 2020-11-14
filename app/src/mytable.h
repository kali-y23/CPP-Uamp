#pragma once

#include <QtWidgets>

#include <vector>

#include "component.h"
#include "tags.h"
#include "playlist.h"
#include "mymodel.h"

class Component;
class Mediator;

class MyTable : public QTableView, public Component
{
    Q_OBJECT
    MyModel *model = new MyModel(std::deque<Tags *>());
    QMenu *mainMenu;
    QMenu *playlistMenu;
    QAction *editAction;
    QAction *removeAction;
    std::vector<QAction *> playlistActions;

public:
    explicit MyTable(Mediator *mediator, QWidget *parent = nullptr);
    ~MyTable();

    MyModel *getModel() {
        return model;
    }

signals:
    void sendSongToPlayer(Tags *tags);
    void removeSong(int id);

public slots:
    void sendNextSong(const QModelIndex &index);
    void showContextMenuRequested(const QPoint &pos);
    void removeSong();
};
