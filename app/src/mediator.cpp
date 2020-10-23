#include "mediator.h"

Mediator::Mediator() : QObject() {
    mainWindow = new MainWindow(this);
    loginScreen = new LoginScreen(this);
    generalScreen = new GeneralScreen(this);
    mainWindow->setCentralWidget(loginScreen);
    mainWindow->show();
    //reinterpret_cast<const QObject *> (mediator)
    connect(this, SIGNAL(signIn(QWidget *, bool)), mainWindow, SLOT(setWidget(QWidget *, bool)));
}

Mediator::~Mediator() {
    //
}

void Mediator::signIn() {
    emit signIn(generalScreen, true);
}