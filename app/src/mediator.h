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
#include "userManager.h"
#include "myDb.h"

#define LIBRARY 0
#define PLAYLISTS 1

class MainWindow;
class LoginScreen;
class RegistrationScreen;
class GeneralScreen;
class User;
class LibraryManager;
class UserManager;
class MyDb;

class Mediator : public QObject
{
    Q_OBJECT

private:
    MainWindow *mainWindow;

    LibraryManager *libraryManager;
    UserManager *userManager;

    LoginScreen *loginScreen;
    RegistrationScreen *registrationScreen;
    GeneralScreen *generalScreen;

public:
    Mediator();
    ~Mediator();

    User *user = nullptr;
    LibraryManager *getLibraryManager() const;
    GeneralScreen *getGeneralScreen() const;
    RegistrationScreen *getRegistrationScreen() const;
    MainWindow *getMainWindow() const;
    MyDb *db;
    int currentPlaylist = -1;

public slots:
    void signIn(int id, const QString &login);
    void signInTry();
    void registrationOpen();
    void registrationTry();
    void backToSignIn();
    void backToLibrary();
    void backToPlaylists();

    void initImport(const QString& path, bool recursive);
    void slotAddSong(Tags *tags);
    void slotAddPlaylist(Playlist *);
    void playNextSong();
    void playPrevSong();
    void emitRepeatModeIndex(int index);
    void createPlaylist(const QString& text);
    void selectPlaylist(int id);
    void removeSong(int id);
    void removePlaylist(int id);

signals:
    void changeWidget(QWidget *widget, bool tool);
    void registrationTry(QString login, QString password, QString passwordRepeat);
    void signInTry(QString login, QString password);
    void addSongsToLibrary(const QString& path, bool recursive);
    void showInLibrary(Tags *tags);
    void showInList(Playlist *playlists);
    void loadSongs(bool queue);
    void loadPlaylists();
    void nextSong();
    void prevSong();
    void repeatModeChanged(int index);
    void setPlayerData(const QModelIndex &index);
    void changeSidebar(int index);
    void createNewPlaylist(const QString& text);
};
