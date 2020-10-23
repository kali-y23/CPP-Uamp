#pragma once

#include <string>
#include <iostream>

#include <QtWidgets>

#include "mainwindow.h"
#include "login.h"
#include "general.h"

class MainWindow;
class LoginScreen;
class GeneralScreen;

class Mediator : public QObject
{
    Q_OBJECT

private:
    MainWindow *mainWindow;
    LoginScreen *loginScreen;
    // RegistrationScreen *registrationS
    GeneralScreen *generalScreen;

public:
    Mediator();
    ~Mediator();

public slots:
    void signIn();

signals:
    void signIn(QWidget *widget, bool tool);
};
