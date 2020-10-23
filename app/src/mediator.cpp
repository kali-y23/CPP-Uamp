#include "mediator.h"

Mediator::Mediator() : QObject() {
    qDebug() << "a0";
    mainWindow = new MainWindow(this);
    loginScreen = new LoginScreen(this);
    qDebug() << "a1";
    mainWindow->layoutOuter->addWidget(loginScreen);
    qDebug() << "a2";
    registrationScreen = new RegistrationScreen(this);
    mainWindow->layoutOuter->addWidget(registrationScreen);
    qDebug() << "a3";
    generalScreen = new GeneralScreen(this);
    qDebug() << "a3.5";
    mainWindow->layoutOuter->addWidget(generalScreen);
    qDebug() << "a4";

    mainWindow->layoutOuter->setCurrentWidget(loginScreen);
    mainWindow->show();

    connect(this, SIGNAL(changeWidget(QWidget *, bool)), mainWindow, SLOT(setWidget(QWidget *, bool)));
}


Mediator::~Mediator() {
    //
}

void Mediator::signIn() {
    emit changeWidget(generalScreen, true);
}

void Mediator::registrationOpen() {
    emit changeWidget(registrationScreen, false);
}

void Mediator::backToSignIn() {
    emit changeWidget(loginScreen, false);
}
