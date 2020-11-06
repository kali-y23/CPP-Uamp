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

    playerEnabled = new QWidget();
    playerDisabled = new QWidget();
    playerDisabled->setMaximumHeight(100);

    label1 = new QLabel("ucode");
    label1->setObjectName("label_1");
    label2 = new QLabel("amp");
    label2->setObjectName("label_2");

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

    label->addWidget(label1, 0, 0, 1, 1);
    label->addWidget(label2, 0, 1, 1, 1);

    main->addSpacing(80);
    main->addWidget(icon_quiet);
    main->addWidget(slider_sound);

    sliderTest = new QSlider(Qt::Vertical);
    main->addWidget(sliderTest);
    sliderTest1 = new QSlider(Qt::Vertical);
    main->addWidget(sliderTest1);
    sliderTest2 = new QSlider(Qt::Vertical);
    main->addWidget(sliderTest2);

    main->addWidget(icon_loud);
    main->addSpacing(30);
    main->addWidget(edit_search);
    main->addSpacing(30);
    main->addWidget(button_playlist);
    main->addSpacing(30);

    connect(button_playlist, SIGNAL(clicked()), this, SLOT(playlistButtonClicked()));
    connect(button_next, SIGNAL(clicked()), mediator, SLOT(playNextSong()));
    connect(button_prev, SIGNAL(clicked()), mediator, SLOT(playPrevSong()));
    connect(button_loop, SIGNAL(clicked()), button_loop, SLOT(emitIndex()));
    connect(button_loop, SIGNAL(indexChanged(int)), mediator, SLOT(emitRepeatModeIndex(int)));
    connect(button_play, SIGNAL(play()), this, SLOT(playSound()));
    connect(button_play, SIGNAL(stop()), this, SLOT(stopSound()));
    connect(button_skip_fwd, SIGNAL(clicked()), this, SLOT(skipFwd()));
    connect(button_skip_bck, SIGNAL(clicked()), this, SLOT(skipBck()));
    connect(slider_song, SIGNAL(sliderMoved(int)), this, SLOT(setPosition(int)));
    connect(slider_song, SIGNAL(sliderPressed()), this, SLOT(setPosition()));
    connect(slider_song, SIGNAL(valueChanged(int)), this, SLOT(displayData(int)));
    connect(this, SIGNAL(changeWidget(QWidget *, bool)), SLOT(setWidget(QWidget *, bool)));

    connect(this, SIGNAL(test()), this, SLOT(test1()));
}

QPlayer::~QPlayer() {
    delete main;
}

void QPlayer::setupLayouts() {
    main = new QHBoxLayout(this);
    player = new QGridLayout(playerEnabled);
    label = new QGridLayout(playerDisabled);
    layoutOuter = new QStackedLayout(player_widget);
    layoutOuter->addWidget(playerDisabled);
    layoutOuter->addWidget(playerEnabled);
    layoutOuter->setCurrentWidget(playerDisabled);
}


void QPlayer::setData(Tags *tags) {
    data = tags;
    label_title->setText(data->getTitle().toString());
    label_artist->setText(data->getArtist().toString());
    BASS_StreamFree(
        stream
    );
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
    if (stream) {
        layoutOuter->setCurrentWidget(playerEnabled);
        BASS_ChannelPlay(stream, FALSE);
        playing = 1;
    }
    else {
        button_play->setIcon(button_play->list[0]);
        button_play->index = 0;
    }
}

void QPlayer::stopSound() {
    BASS_ChannelStop(stream);
    playing = 0;
}

void QPlayer::setPosition(int pos) {
    QWORD time = BASS_ChannelGetLength(stream, BASS_POS_BYTE);
    int delta = 0;

    while (1) {
        if (BASS_ChannelSetPosition(
            stream,
            pos - delta,
            BASS_POS_BYTE
        )) {
            break;
        }
        delta += 20000;
    }
}

void QPlayer::setPosition() {
    QWORD time = BASS_ChannelGetLength(stream, BASS_POS_BYTE);
    QWORD pos = slider_song->value();
    int delta = 0;

    while (1) {
        if (BASS_ChannelSetPosition(
            stream,
            pos - delta,
            BASS_POS_BYTE
            )) {
            break;
        }
        delta += 10000;
    }
}

std::string toStrTime(int time) {
    std::string str = std::to_string(time);
    if (str.length() < 2) {
        str.insert(0, "0");
    }
    return str;
}

std::string transformTime(int time) {
    int iMin = time / 60;
    int iSec = time - iMin * 60;
    std::string min = toStrTime(iMin);
    std::string sec = toStrTime(iSec);

    return min + ":" + sec;
}

void QPlayer::displayData(int pos) {
    QWORD time = BASS_ChannelGetLength(stream, BASS_POS_BYTE);
    double dTime = BASS_ChannelBytes2Seconds(stream, time);
    double dPos = BASS_ChannelBytes2Seconds(stream, pos);
    int iTime = round(dTime);
    int iPos = round(dPos);

    label_start_time->setText(transformTime(iPos).c_str());
    label_end_time->setText(transformTime(iTime - iPos).c_str());
}


void QPlayer::threadFunction() {
    while (1) {
        if (playing && stream) {

            float fft[512]; // fft data buffer
            BASS_ChannelGetData(stream, fft, BASS_DATA_FFT1024);
            sliderTest->setMaximum(static_cast<int>(100));
            sliderTest1->setMaximum(static_cast<int>(100));
            sliderTest2->setMaximum(static_cast<int>(100));
            sliderTest->setValue(static_cast<int>(fft[0] * 100));
            sliderTest1->setValue(static_cast<int>(fft[1] * 100));
            sliderTest2->setValue(static_cast<int>(fft[2] * 100));


            QWORD time = BASS_ChannelGetLength(stream, BASS_POS_BYTE);
            QWORD pos = BASS_ChannelGetPosition(stream, BASS_POS_BYTE);

            if (slider_song->maximum() != static_cast<int>(time)) {
                slider_song->setMaximum(static_cast<int>(time));
            }
            if (!slider_song->isSliderDown()) {
                slider_song->setValue(static_cast<int>(pos));
            }
            if (pos >= time) {
                emit test();
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void QPlayer::test1() {
    Tags *next_tags = mediator->getGeneralScreen()->getQueue()->getNextSong();
    if(next_tags)
        updateData(next_tags);
    else{
        playing = 0;
        stream = 0;
        setWidget(playerDisabled, 1);
    }
}


void QPlayer::setWidget(QWidget *widget, bool play) {
    layoutOuter->setCurrentWidget(widget);
    if (play) {
        emit button_play->clicked();
    }
}

void QPlayer::skipFwd() {
    QWORD time = BASS_ChannelGetLength(stream, BASS_POS_BYTE);
    QWORD currentPos = BASS_ChannelGetPosition(stream, BASS_POS_BYTE);
    QWORD delta = BASS_ChannelSeconds2Bytes(stream, 10);
    QWORD pos = currentPos + delta < time ? currentPos + delta : time - 1;

    BASS_ChannelSetPosition(
        stream,
        pos,
        BASS_POS_BYTE
    );
    slider_song->setValue(static_cast<int>(pos));
}

void QPlayer::skipBck() {
    QWORD currentPos = BASS_ChannelGetPosition(stream, BASS_POS_BYTE);
    QWORD delta = BASS_ChannelSeconds2Bytes(stream, 10);
    QWORD pos = delta > currentPos ? BASS_ChannelSeconds2Bytes(stream, 0) : currentPos - delta;

    BASS_ChannelSetPosition(
        stream,
        pos,
        BASS_POS_BYTE
    );
    slider_song->setValue(static_cast<int>(pos));
}

void QPlayer::playlistButtonClicked(void) {
    emit toggleQueueSignal();
}
