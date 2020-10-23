#include "registration.h"

RegistrationScreen::RegistrationScreen(const Mediator *mediator_, QWidget *parent) :
                        QWidget(parent), Component(mediator_)
{
    layoutOuter = new QGridLayout(this);

    loginField = new QLineEdit(this);
    loginField->setPlaceholderText("Enter login");
    loginField->setMinimumWidth(300);
    passwordField = new QLineEdit(this);
    passwordField->setPlaceholderText("Enter password");
    passwordRepeatField = new QLineEdit(this);
    passwordRepeatField->setPlaceholderText("Repeat password");
    registrationButton = new QPushButton("Sign up", this);
    signInButton = new QPushButton("Go back", this);

    layoutOuter->addWidget(loginField, 1, 1, 1, 2);
    layoutOuter->addWidget(passwordField, 2, 1, 1, 2);
    layoutOuter->addWidget(passwordRepeatField, 3, 1, 1, 2);
    layoutOuter->addWidget(registrationButton, 4, 1);
    layoutOuter->addWidget(signInButton, 4, 2);

    layoutOuter->setColumnStretch(0, 2);
    layoutOuter->setColumnStretch(layoutOuter->columnCount(), 2);
    layoutOuter->setRowStretch(0, 2);
    layoutOuter->setRowStretch(layoutOuter->rowCount(), 2);

    layoutOuter->setVerticalSpacing(20);

    loginField->setMinimumHeight(50);
    passwordField->setMinimumHeight(50);
    passwordRepeatField->setMinimumHeight(50);
    signInButton->setMinimumHeight(50);
    registrationButton->setMinimumHeight(50);

    connect(signInButton, SIGNAL(clicked()), reinterpret_cast<const QObject *> (mediator), SLOT(backToSignIn()));
    connect(registrationButton, SIGNAL(clicked()), reinterpret_cast<const QObject *> (mediator), SLOT(registrationTry()));
}

RegistrationScreen::~RegistrationScreen()
{

}

Qstring RegistrationScreen::getLogin(){
    return loginField->text();
}

Qstring RegistrationScreen::getPassword() {
    return passwordField->text();
}
Qstring RegistrationScreen::getPasswordRepeat(){
    return passwordRepeatField->text();
}

void RegistrationScreen::clearData() {
    loginField->clear();
    passwordField->clear();
    passwordRepeatField->clear();
}