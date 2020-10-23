#pragma once

#include <QtWidgets>

#include "component.h"

class Component;
class Mediator;

class MainWindow : public QMainWindow, public Component
{
    Q_OBJECT

private:
    QToolBar *toolBar;

    void initToolbar();

public:
    explicit MainWindow(Mediator *mediator, QWidget *parent = nullptr);
    ~MainWindow();

    QStackedLayout *layoutOuter;

public slots:
    void setWidget(QWidget *widget, bool tool);

};
