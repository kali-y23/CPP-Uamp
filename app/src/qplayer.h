#pragma once

#include "mainwindow.h"
#include "qsuperbutton.h"

class QSuperButton;

class QPlayer : public QWidget {
    Q_OBJECT

    QProgressBar *progress_bar_song;
    QProgressBar *progress_bar_sound;

    QSuperButton *button_play;
    QSuperButton *button_next;
    QSuperButton *button_prev;
    QSuperButton *button_shuffle;
    QSuperButton *button_loop;

    QLabel *label_title;
    QLabel *label_artist;

    QIcon *icon_quiet;
    QIcon *icon_loud;
public:
    QPlayer(QWidget *parent = nullptr);
    ~QPlayer();


};