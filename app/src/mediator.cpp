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

    Tags tags("aaaa", "/Users/mlibovych/Desktop/P.I.M.P..mp3", true);
    generalScreen->getView()->getModel()->addData(std::move(tags));
}


Mediator::~Mediator() {
    //
}

void Mediator::signIn() {
    user = new User(this);
    user->setId(0);
    user->setLogin("Test");
    emit changeWidget(generalScreen, true);
}

void Mediator::registrationOpen() {
    emit changeWidget(registrationScreen, false);
}

void Mediator::registrationTry() {
    emit registrationTry(registrationScreen->getLogin(),
                         registrationScreen->getPassword(),
                         registrationScreen->getPasswordRepeat()
                        );
}

void Mediator::backToSignIn() {
    emit changeWidget(loginScreen, false);
}
