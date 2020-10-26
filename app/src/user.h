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

public:
    explicit User(const Mediator *mediator_);
    ~User();

    void setId(int id_);

    void setLogin(const QString &login_);

    int getId();

    QString getLogin();

};
