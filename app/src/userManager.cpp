#include "userManager.h"

UserManager::UserManager(Mediator *mediator) : Component(mediator) {

}

UserManager::~UserManager() {

}

void UserManager::addUser(const QString& login_, const QString& password_, const QString& passwordRepeat_) {
    if (login_.length() < 6 || password_.length() < 6 || passwordRepeat_.length() < 6 || password_ != passwordRepeat_) {
        QMessageBox::warning(mediator->getMainWindow(), "Alert", "Entered data is invalid.");
        return;
    }
    QSqlQuery query(QSqlDatabase::database("myDb"));

    query.prepare("SELECT id FROM users WHERE login=:login");
    query.bindValue(":login", login_);
    query.exec();
    if (query.first() && !query.value(0).isNull()) {
        QMessageBox::warning(mediator->getMainWindow(), "Alert", "This login is already registred.");
        return;
    }
    query.prepare("INSERT INTO users (login, password) "
                  "VALUES (:login, :password)");
    query.bindValue(":login", login_);
    query.bindValue(":password", password_);
    query.exec();
    QMessageBox::information(mediator->getMainWindow(), "Alert", "Registration sucseeded.");
    emit signUp();
}

void UserManager::checkUser(const QString& login_, const QString& password_) {
    QSqlQuery query(QSqlDatabase::database("myDb"));
    int id = 0;

    query.prepare("SELECT id FROM users WHERE login=:login AND password=:password");
    query.bindValue(":login", login_);
    query.bindValue(":password", password_);
    query.exec();
    if (!query.first()) {
        QMessageBox::warning(mediator->getMainWindow(), "Alert", "Entered data is invalid.");
        return;
    }
    query.first();
    id = query.value(0).toInt();
    emit signIn(id, login_);
}
