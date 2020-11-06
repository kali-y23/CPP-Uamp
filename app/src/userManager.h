#pragma once

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtWidgets>
#include <string>
#include <cstdio>

#include "component.h"
#include "mediator.h"

class Component;
class Mediator;

class UserManager : public QObject, public Component {
    Q_OBJECT

public:
    UserManager(Mediator *mediator);
    ~UserManager();

public slots:
    void addUser(const QString& login_, const QString& password_, const QString& passwordRepeat_);
    void checkUser(const QString& login_, const QString& password_);

signals:
    void signUp();
    void signIn(int id, QString login);
    void fail();
};