#include "qplayer.h"

QPlayer::QPlayer(QWidget *parent) {
    // progress_bar_song = new QProgressBar(box);
    // QProgressBar *progress_bar_sound;

    QSuperButton *button_play = new QSuperButton(ButtonType::Play, this);
    // QSuperButton *button_next;
    // QSuperButton *button_prev;
    // QSuperButton *button_shuffle;
    // QSuperButton *button_loop;

    // QLabel *label_title;
    // QLabel *label_artist;

    // QIcon *icon_quiet;
    // QIcon *icon_loud;

    QHBoxLayout *l = new QHBoxLayout(this);
    l->addWidget(button_play);
}

QPlayer::~QPlayer() {
    //
}
