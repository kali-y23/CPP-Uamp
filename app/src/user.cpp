#include "user.h" 

User::User(const Mediator *mediator_) : Component(mediator_)
{

}

User::~User() {

}

void User::setId(int id_) {
    id = id_;
}

void User::setLogin(const QString &login_) {
    login = login_;
}

int User::getId() {
    return id;
}

QString User::getLogin() {
    return login;
}