#pragma once

#include <iostream>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtWidgets>

#include "component.h"

class Component;
class Mediator;

class MyDb : public Component
{
    const QString appPath;
    const QString dbPath;

    QSqlDatabase db;

    void checkDir();
    void createIfNotExist();
public:
    MyDb(const Mediator *mediator_);
};
