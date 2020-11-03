#include "qplayer.h"

#include <iostream>

QPlayer::QPlayer(const Mediator *mediator, QWidget *parent) : Component(mediator), thr(&QPlayer::threadFunction, this) {
    setMaximumHeight(140);
    button_play = new QPlayButton(ButtonType::Play);
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

    connect(button_play, SIGNAL(play()), this, SLOT(playSound()));
    connect(button_play, SIGNAL(stop()), this, SLOT(stopSound()));
    connect(slider_song, SIGNAL(sliderMoved(int)), this, SLOT(setPosition(int)));
}

QPlayer::~QPlayer() {
    delete main;
}

void QPlayer::setupLayouts() {
    main = new QHBoxLayout(this);
    player = new QGridLayout(player_widget);

}


void QPlayer::setData(Tags *tags) {
    data = tags;
    label_title->setText(data->getTitle().toString());
    label_artist->setText(data->getArtist().toString());
    stream = BASS_StreamCreateFile(FALSE, data->getPath().toString().toStdString().c_str(), 0, 0, 0);
}

void QPlayer::updateData(Tags *tags) {
    stopSound();
    setData(tags);
    button_play->setIcon(button_play->list[1]);
    button_play->index = 1;
    playSound();
}

void QPlayer::playSound() {
    BASS_ChannelPlay(stream,FALSE);
    playing = 1;
}

void QPlayer::stopSound() {
    BASS_ChannelStop(stream);
    playing = 0;
}

void QPlayer::setPosition(int pos) {
    if (pos != static_cast<int>(BASS_ChannelGetPosition(stream, BASS_POS_BYTE))) {
        BASS_ChannelSetPosition(
            stream,
            pos,
            BASS_POS_BYTE
        );
    }
}

void QPlayer::threadFunction() {
    //std::terminate()
    while (1) {
        if (playing) {
            QWORD time = BASS_ChannelGetLength(stream, BASS_POS_BYTE); // the length in bytes
            QWORD pos = BASS_ChannelGetPosition(stream, BASS_POS_BYTE); // the length in bytes
            // double pos = BASS_ChannelBytes2Seconds(stream, len1); // the length in seconds
            // double time = BASS_ChannelBytes2Seconds(stream, len); // the length in seconds

            if (slider_song->maximum() != static_cast<int>(time)) {
                slider_song->setMaximum(static_cast<int>(time));
            }
            if(!slider_song->isSliderDown()) {
                slider_song->setValue(static_cast<int>(pos));
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }
}