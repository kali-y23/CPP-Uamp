#pragma once

#include <iostream>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtWidgets>

class MyDb
{
    const QString appPath;
    const QString dbPath;

    QSqlDatabase db;

    void checkDir();
    void createIfNotExist();
public:
    MyDb();
};
