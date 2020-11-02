#include "qplayer.h"

#include <iostream>

QPlayer::QPlayer(const Mediator *mediator, QWidget *parent) : Component(mediator) {
    setMaximumHeight(140);
    button_play = new QSuperButton(ButtonType::Play);
    button_prev = new QToolButton();
    button_next = new QToolButton();
    button_skip_fwd = new QToolButton();
    button_skip_bck = new QToolButton();

    button_prev->setIcon(QIcon(":/prev.png"));
    button_next->setIcon(QIcon(":/next.png"));
    button_skip_fwd->setIcon(QIcon(":/skip_fwd.png"));
    button_skip_bck->setIcon(QIcon(":/skip_back.png"));
    button_prev->setIconSize({30, 30});
    button_next->setIconSize({30, 30});
    button_skip_fwd->setIconSize({30, 30});
    button_skip_bck->setIconSize({30, 30});

    button_shuffle = new QSuperButton(ButtonType::Shuffle);
    button_loop = new QSuperButton(ButtonType::Loop);

    label_title = new QLabel("Title of this awesome song");
    label_artist = new QLabel("Artist Name");
    label_start_time = new QLabel("00:00");
    label_end_time = new QLabel("99:99");

    icon_quiet = new QLabel();
    icon_loud = new QLabel();
    slider_song = new QSlider(Qt::Horizontal);

    player_widget = new QWidget();
    player_widget->setObjectName("Player");
    player_widget->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    setupLayouts();

    icon_quiet->setPixmap(QPixmap(":/quiet.png").scaled(30, 30));
    icon_loud->setPixmap(QPixmap(":/loud.png").scaled(30, 30));

    slider_sound = new QSlider(Qt::Horizontal);
    slider_sound->setMinimumSize(100, 10);
    slider_sound->setMaximumSize(100, 10);
    icon_quiet->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    button_playlist = new QSuperButton(ButtonType::Playlist);

    edit_search = new QLineEdit();
    edit_search->setPlaceholderText("Search");
    edit_search->setMinimumWidth(100);
    edit_search->setMaximumWidth(300);

    main->addSpacing(30);
    main->addWidget(button_prev);
    main->addWidget(button_skip_bck);
    main->addWidget(button_play);
    main->addWidget(button_skip_fwd);
    main->addWidget(button_next);
    main->addSpacing(80);
    main->addWidget(player_widget);

    player->addWidget(button_shuffle, 0, 0, 1, 1);
    player->addWidget(button_loop, 0, 3, 1, 1);
    player->addWidget(label_title, 0, 1, 1, 2, Qt::AlignCenter);
    player->addWidget(label_artist, 1, 1, 1, 2, Qt::AlignCenter);
    player->addWidget(label_start_time, 2, 0, 1, 1, Qt::AlignCenter);
    player->addWidget(label_end_time, 2, 3, 1, 1, Qt::AlignCenter);
    player->addWidget(slider_song, 3, 0, 1, 5);

    main->addSpacing(80);
    main->addWidget(icon_quiet);
    main->addWidget(slider_sound);
    main->addWidget(icon_loud);
    main->addSpacing(30);
    main->addWidget(edit_search);
    main->addSpacing(30);
    main->addWidget(button_playlist);
    main->addSpacing(30);

    QObject::connect(button_playlist, SIGNAL(clicked()), this, SLOT(playlistButtonClicked()));
    QObject::connect(button_next, SIGNAL(clicked()), mediator, SLOT(playNextSong()));
    QObject::connect(button_prev, SIGNAL(clicked()), mediator, SLOT(playPrevSong()));
}

QPlayer::~QPlayer() {
    delete main;
}

void QPlayer::setupLayouts() {
    main = new QHBoxLayout(this);
    player = new QGridLayout(player_widget);
}

void QPlayer::playlistButtonClicked() {
    emit toggleQueueSignal();
}
