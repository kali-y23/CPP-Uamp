#pragma once

#include <QtWidgets>

#include "component.h"
#include "mytreeview.h"
#include "mylist.h"

class MyTreeView;
class MyList;
class Component;

class QSideBar : public QWidget, public Component {
    Q_OBJECT

    QStackedLayout *layout_stacked;
    QVBoxLayout *layout_main;

    QWidget *widget_treeview;
    QVBoxLayout *layout_treeview;
    MyTreeView *tree_view;
    QWidget *widget_playlists;
    QVBoxLayout *layout_playlists;
    MyList *playlists_view;
    QPushButton *createButton;

public:
    QSideBar(const Mediator *mediator, QWidget *parent = nullptr);
    ~QSideBar();

    void switchToTreeView();
    void switchToPlaylists();

    MyList *getList() {
        return playlists_view;
    }

public slots:
    void createPlaylist();

signals:
    void createPlaylist(const QString& text);

private:
    void setupTreeView();
    void setupPlaylists();
};
