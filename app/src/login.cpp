#include "login.h"

LoginScreen::LoginScreen(const Mediator *mediator_, QWidget *parent) :
                        QWidget(parent), Component(mediator_)
{
    layoutOuter = new QGridLayout(this);

    loginField = new QLineEdit(this);
    loginField->setPlaceholderText("Login");
    loginField->setMinimumWidth(300);
    passwordField = new QLineEdit(this);
    passwordField->setPlaceholderText("Password");
    passwordField->setEchoMode(QLineEdit::Password);
    signInButton = new QPushButton("Sign in", this);
    registrationButton = new QPushButton("Registration", this);


    layoutOuter->addWidget(loginField, 1, 1, 1, 2);
    layoutOuter->addWidget(passwordField, 2, 1, 1, 2);
    layoutOuter->addWidget(signInButton, 3, 1);
    layoutOuter->addWidget(registrationButton, 3, 2);

    layoutOuter->setColumnStretch(0, 2);
    layoutOuter->setColumnStretch(layoutOuter->columnCount(), 2);
    layoutOuter->setRowStretch(0, 2);
    layoutOuter->setRowStretch(layoutOuter->rowCount(), 2);

    layoutOuter->setVerticalSpacing(20);

    loginField->setMinimumHeight(50);
    passwordField->setMinimumHeight(50);
    signInButton->setMinimumHeight(50);
    registrationButton->setMinimumHeight(50);

    connect(signInButton, SIGNAL(clicked()), reinterpret_cast<const QObject *> (mediator), SLOT(signInTry()));
    connect(registrationButton, SIGNAL(clicked()), reinterpret_cast<const QObject *> (mediator), SLOT(registrationOpen()));
}

LoginScreen::~LoginScreen()
{

}

QString LoginScreen::getLogin(){
    return loginField->text();
}

QString LoginScreen::getPassword() {
    return passwordField->text();
}

void LoginScreen::clearData() {
    loginField->clear();
    passwordField->clear();
}