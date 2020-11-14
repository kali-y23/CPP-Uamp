#include "qplayer.h"

QPlayer::QPlayer(const Mediator *mediator, QWidget *parent) : Component(mediator), thr(&QPlayer::threadFunction, this) {
    eq = new BASS_DX8_PARAMEQ();
    eq->fBandwidth = 12;
    eq->fCenter = 8000;

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

    label_title = new QLabel();
    label_artist = new QLabel();
    label_start_time = new QLabel();
    label_end_time = new QLabel();

    icon_quiet = new QLabel();
    icon_loud = new QLabel();
    slider_song = new QSlider(Qt::Horizontal);

    player_widget = new QWidget();
    player_widget->setObjectName("Player");

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
    slider_sound->setMaximum(100);
    slider_sound->setValue(50);

    slider_gain = new QSlider(Qt::Vertical);
    slider_gain->setMaximum(30);
    slider_gain->setValue(15);

    slider_bandwidth = new QSlider(Qt::Vertical);
    slider_bandwidth->setMaximum(16000);
    slider_bandwidth->setMinimum(1);
    slider_bandwidth->setValue(8000);

    slider_center = new QSlider(Qt::Vertical);
    slider_center->setMaximum(36);
    slider_bandwidth->setMinimum(1);
    slider_center->setValue(12);

    button_playlist = new QSuperButton(ButtonType::Playlist);

    edit_search = new QLineEdit();
    edit_search->setPlaceholderText("Search");
    edit_search->setMinimumWidth(100);
    edit_search->setMaximumWidth(300);

    main->addSpacing(20);
    main->addWidget(button_prev);
    main->addWidget(button_skip_bck);
    main->addWidget(button_play);
    main->addWidget(button_skip_fwd);
    main->addWidget(button_next);
    main->addSpacing(50);
    main->addWidget(player_widget);

    player->addWidget(button_shuffle, 0, 0, 1, 1);
    player->addWidget(button_loop, 0, 3, 1, 1);
    player->addWidget(label_title, 0, 1, 1, 2, Qt::AlignCenter);
    player->addWidget(label_artist, 1, 1, 1, 2, Qt::AlignCenter);
    player->addWidget(label_start_time, 2, 0, 1, 1, Qt::AlignCenter);
    player->addWidget(label_end_time, 2, 3, 1, 1, Qt::AlignCenter);
    player->addWidget(slider_song, 3, 0, 1, 4);

    label->addWidget(label1, 0, 0, 1, 1);
    label->addWidget(label2, 0, 1, 1, 1);

    main->addSpacing(30);
    main->addWidget(icon_quiet);
    main->addWidget(slider_sound);
    main->addWidget(icon_loud);
    main->addSpacing(30);
    initField();
    main->addWidget(slider_gain);
    main->addWidget(slider_bandwidth);
    main->addWidget(slider_center);
    main->addSpacing(20);
    main->addWidget(button_playlist);
    main->addSpacing(20);

    connect(button_playlist, SIGNAL(clicked()), this, SLOT(playlistButtonClicked()));
    connect(button_next, SIGNAL(clicked()), mediator, SLOT(playNextSong()));
    connect(button_prev, SIGNAL(clicked()), mediator, SLOT(playPrevSong()));
    connect(button_loop, SIGNAL(clicked()), button_loop, SLOT(emitIndex()));
    connect(button_loop, SIGNAL(indexChanged(int)), mediator, SLOT(emitRepeatModeIndex(int)));
    connect(button_play, SIGNAL(play()), this, SLOT(playSound()));
    connect(button_play, SIGNAL(stop()), this, SLOT(stopSound()));
    connect(button_skip_fwd, SIGNAL(clicked()), this, SLOT(skipFwd()));
    connect(button_skip_bck, SIGNAL(clicked()), this, SLOT(skipBck()));
    connect(slider_sound, SIGNAL(sliderMoved(int)), this, SLOT(setVolume(int)));
    connect(slider_gain, SIGNAL(sliderMoved(int)), this, SLOT(setBass(int)));
    connect(slider_bandwidth, SIGNAL(sliderMoved(int)), this, SLOT(setBandwidth(int)));
    connect(slider_center, SIGNAL(sliderMoved(int)), this, SLOT(setCenter(int)));
    connect(slider_song, SIGNAL(sliderMoved(int)), this, SLOT(setPosition(int)));
    connect(slider_song, SIGNAL(sliderPressed()), this, SLOT(setPosition()));
    connect(slider_song, SIGNAL(valueChanged(int)), this, SLOT(displayData(int)));
    connect(this, SIGNAL(changeWidget(QWidget *, bool)), SLOT(setWidget(QWidget *, bool)));
    connect(this, SIGNAL(signalEnd()), this, SLOT(processEndSong()));
}

QPlayer::~QPlayer() {
    delete main;
}

void QPlayer::initField() {
    scene = new QGraphicsScene;
    QGraphicsView *view = new QGraphicsView;

    for (int i = 0; i < 300; ++i) {
        items.push_back(new MyItem(i, 100, Qt::black));
        scene->addItem(items[i]);
    }
    scene->setSceneRect(0, 0, 300, 100);
    view->setFixedSize(300 + 2, 100 + 2);
    view->setScene(scene);
    main->addWidget(view);
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
    QFileInfo info(data->getPath().toString());
    stream = BASS_StreamCreateFile(FALSE, data->getPath().toString().toStdString().c_str(), 0, 0, 0);

    if (stream && info.exists() && info.isReadable()) {
        label_title->setText(data->getTitle().toString());
        label_artist->setText(data->getArtist().toString());
    }
    else {
        playing = 0;
        setWidget(playerDisabled, 1);
    }
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
        handle = BASS_ChannelSetFX(stream, BASS_FX_DX8_PARAMEQ, 1);
        BASS_ChannelSetAttribute(stream, BASS_ATTRIB_VOL, slider_sound->value() / 10);
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

void QPlayer::setBass(int pos) {
    eq->fGain = pos - 15;
    BASS_FXSetParameters(handle, eq);
}

void QPlayer::setBandwidth(int pos) {
    eq->fBandwidth = pos;
    BASS_FXSetParameters(handle, eq);
}

void QPlayer::setCenter(int pos) {
    eq->fCenter = pos;
    BASS_FXSetParameters(handle, eq);
}

void QPlayer::setVolume(int pos) {
    BASS_ChannelSetAttribute(stream, BASS_ATTRIB_VOL, static_cast<float>(pos) / 10);
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
            for (int i = 0; i < 300; ++i) {
                items[i]->h = (items[i]->h + std::abs(fft[i] * 100)) / 2;
            }
            scene->update();

            QWORD time = BASS_ChannelGetLength(stream, BASS_POS_BYTE);
            QWORD pos = BASS_ChannelGetPosition(stream, BASS_POS_BYTE);

            if (slider_song->maximum() != static_cast<int>(time)) {
                slider_song->setMaximum(static_cast<int>(time));
            }
            if (!slider_song->isSliderDown()) {
                slider_song->setValue(static_cast<int>(pos));
            }
            if (pos >= time) {
                emit signalEnd();
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

void QPlayer::processEndSong() {
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
