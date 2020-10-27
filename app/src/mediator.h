#pragma once

#include <string>
#include <iostream>
#include <utility>

#include <QtWidgets>

#include "mainwindow.h"
#include "login.h"
#include "registration.h"
#include "general.h"
#include "user.h"
#include "libraryManager.h"

class MainWindow;
class LoginScreen;
class RegistrationScreen;
class GeneralScreen;
class User;

class Mediator : public QObject
{
    Q_OBJECT

private:
    MainWindow *mainWindow;

    LibraryManager *libraryManager;

    LoginScreen *loginScreen;
    RegistrationScreen *registrationScreen;
    GeneralScreen *generalScreen;

    User *user;

public:
    Mediator();
    ~Mediator();

public slots:
    void signIn();
    void registrationOpen();
    void registrationTry();
    void backToSignIn();

    // void loadSongsFromDB();
    void initImport(const QString& path);
    void slotAddSong(const Tags& tags);

signals:
    void changeWidget(QWidget *widget, bool tool);
    void registrationTry(QString login, QString password, QString passwordRepeat);
    void addSongsToLibrary(const QString& path);
};
