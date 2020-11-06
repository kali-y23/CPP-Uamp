#pragma once

#include <QtWidgets>
#include "component.h"

class Component;
class Mediator;

class User :  public Component
{

private:
    int id;
    QString login;
    QString password;

public:
    explicit User(const Mediator *mediator_);
    ~User();

    void setId(int id_);

    void setLogin(const QString &login_);

    void setPassword(const QString &password_);

    int getId();

    QString getLogin();

    QString getPassword();

};
