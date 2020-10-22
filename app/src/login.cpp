#include "login.h"

LoginScreen::LoginScreen(const Mediator *mediator_, QWidget *parent) :
                        QWidget(parent), Component(mediator_)
{
    layoutOuter = new QVBoxLayout(this);
    loginField = new QLineEdit(this);
    passwordField = new QLineEdit(this);
    signInButton = new QPushButton("Sign in", this);
    registrationButton = new QPushButton("Registration", this);

    layoutOuter->addWidget(loginField);
    layoutOuter->addWidget(passwordField);
    layoutOuter->addWidget(signInButton);
    layoutOuter->addWidget(registrationButton);

    connect(signInButton, SIGNAL(clicked()), reinterpret_cast<const QObject *> (mediator), SLOT(signIn()));
}

LoginScreen::~LoginScreen()
{

}