#pragma once

#include "mainwindow.h"
#include "qsuperbutton.h"

class QSuperButton;

class QPlayer : public QWidget {
    Q_OBJECT

    QHBoxLayout *main;
    QHBoxLayout *left; // TODO: REFACTOR!!!
    QGridLayout *center; // TODO: REFACTOR!!!

    QWidget *player_widget;

    QSlider *slider_song;
    QSlider *slider_sound;

    QSuperButton *button_play;
    QToolButton *button_next;
    QToolButton *button_prev;
    QToolButton *button_skip_fwd;
    QToolButton *button_skip_bck;
    QSuperButton *button_shuffle;
    QSuperButton *button_loop;
    QSuperButton *button_playlist;

    QLabel *label_start_time;
    QLabel *label_end_time;
    QLabel *label_title;
    QLabel *label_artist;

    QLabel *icon_quiet;
    QLabel *icon_loud;

    QLineEdit *edit_search;
public:
    QPlayer(QWidget *parent = nullptr);
    ~QPlayer();

private:
    void setupLayouts(void);
};