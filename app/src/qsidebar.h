#pragma once

#include <QtWidgets>

#include "component.h"
#include "mytreeview.h"

class MyTreeView;
class Component;

class QSideBar : public QWidget, public Component {
    Q_OBJECT

    QStackedLayout *layout_stacked;
    QVBoxLayout *layout_main;

    QWidget *widget_treeview;
    QVBoxLayout *layout_treeview;
    MyTreeView *tree_view;

public:
    QSideBar(const Mediator *mediator, QWidget *parent = nullptr);
    ~QSideBar();

    void switchToTreeView();

private:
    void setupTreeView();
};
