#include "mediator.h"

Mediator::Mediator() : QObject() {
    mainWindow = new MainWindow(this);
    loginScreen = new LoginScreen(this);
    mainWindow->layoutOuter->addWidget(loginScreen);
    registrationScreen = new RegistrationScreen(this);
    mainWindow->layoutOuter->addWidget(registrationScreen);
    generalScreen = new GeneralScreen(this);
    mainWindow->layoutOuter->addWidget(generalScreen);
    
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