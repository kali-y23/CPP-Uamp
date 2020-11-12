#include "mediator.h"

Mediator::Mediator() : QObject() {
    db = new MyDb(this);
    libraryManager = new LibraryManager(this);
    userManager = new UserManager(this);

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
    connect(this, SIGNAL(loadSongs()), generalScreen, SLOT(loadSongs()));
    connect(this, SIGNAL(loadPlaylists()), generalScreen, SLOT(loadPlaylists()));
    connect(this, SIGNAL(addSongsToLibrary(const QString&, bool)), libraryManager, SLOT(addSongsToLibrary(const QString&, bool)));
    connect(this, SIGNAL(showInLibrary(Tags *)), generalScreen, SLOT(showInView(Tags *)));
    connect(this, SIGNAL(showInList(Playlist *)), generalScreen, SLOT(showInList(Playlist *)));
    connect(this, SIGNAL(nextSong()), generalScreen->getQueue(), SLOT(nextSong()));
    connect(this, SIGNAL(prevSong()), generalScreen->getQueue(), SLOT(prevSong()));
    connect(this, SIGNAL(repeatModeChanged(int)), generalScreen->getQueue(), SLOT(changeRepeatMode(int)));
    connect(generalScreen->getPlayer(), SIGNAL(toggleQueueSignal()), generalScreen, SLOT(toggleQueue()));
    connect(this, SIGNAL(registrationTry(const QString&, const QString&, const QString&)),
            userManager, SLOT(addUser(const QString&, const QString&, const QString&)));
    connect(userManager, SIGNAL(signUp()), this, SLOT(backToSignIn()));
    connect(this, SIGNAL(signInTry(const QString&, const QString&)),
            userManager, SLOT(checkUser(const QString&, const QString&)));
    connect(userManager, SIGNAL(signIn(int, const QString&)), this, SLOT(signIn(int, const QString&)));
    connect(this, SIGNAL(changeSidebar(int)), generalScreen, SLOT(changeSidebar(int)));
    connect(this, SIGNAL(createNewPlaylist(const QString&)), libraryManager, SLOT(createPlaylist(const QString&)));
}


Mediator::~Mediator() {
    //
}

LibraryManager *Mediator::getLibraryManager() const {
    return libraryManager;
}

GeneralScreen *Mediator::getGeneralScreen() const {
    return generalScreen;
}

RegistrationScreen *Mediator::getRegistrationScreen() const {
    return registrationScreen;
}

MainWindow *Mediator::getMainWindow() const {
    return mainWindow;
}

void Mediator::signIn(int id, const QString &login) {
    user = new User(this);
    user->setId(id);
    user->setLogin(login);

    currentPlaylist = -1;
    generalScreen->getSidebar()->getList()->getModel()->clear();
    generalScreen->getSidebar()->switchToTreeView();

    emit loadSongs();
    emit loadPlaylists();
    loginScreen->clearData();
    emit changeWidget(generalScreen, true);
}

void Mediator::signInTry() {
    emit signInTry(loginScreen->getLogin(),
                   loginScreen->getPassword()
                  );
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
    registrationScreen->clearData();
    if (user != nullptr) {
        delete user;
        user = nullptr;
    }
    emit changeWidget(loginScreen, false);
}

void Mediator::selectPlaylist(int id) {
    currentPlaylist = id;
    getGeneralScreen()->loadSongs(id);
}

void Mediator::initImport(const QString& path, bool recursive) {
    emit addSongsToLibrary(path, recursive);
}

void Mediator::backToLibrary() {
    currentPlaylist = -1;
    emit loadSongs();
    emit changeSidebar(LIBRARY);
}

void Mediator::backToPlaylists() {
    emit changeSidebar(PLAYLISTS);
}

void Mediator::slotAddSong(Tags *tags) {
    emit showInLibrary(tags);
}

void Mediator::slotAddPlaylist(Playlist *playlist) {
    emit showInList(playlist);
    // emit addPlaylistAction(playlist);
}

void Mediator::playNextSong() {
    emit nextSong();
}

void Mediator::playPrevSong() {
    emit prevSong();
}

void Mediator::emitRepeatModeIndex(int index) {
    emit repeatModeChanged(index);
}


void Mediator::createPlaylist(const QString& text) {
    emit createNewPlaylist(text);
}
