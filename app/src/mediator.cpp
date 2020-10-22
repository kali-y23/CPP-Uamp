#include "mediator.h"

Mediator::Mediator() : QObject() {
    mainWindow = new MainWindow(this);
    loginScreen = new LoginScreen(this);
    generalScreen = new GeneralScreen(this);
    mainWindow->setCentralWidget(loginScreen);
    mainWindow->show();
}

Mediator::~Mediator() {
    //
}

void Mediator::signIn() {
    mainWindow->setCentralWidget(generalScreen);
}