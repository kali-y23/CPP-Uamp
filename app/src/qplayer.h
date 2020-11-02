#pragma once

#include <QtWidgets>

#include "bass.h"

#include "component.h"
#include "qsuperbutton.h"
#include "tags.h"

class QSuperButton;
class QPlayButton;
class Component;
class Tags;

class QPlayer : public QWidget, public Component {
    Q_OBJECT

    QHBoxLayout *main;
    QGridLayout *player;

    QWidget *player_widget;

    QSlider *slider_song;
    QSlider *slider_sound;

    QPlayButton *button_play;
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

    Tags *data = nullptr;
    HSTREAM stream;
public:
    QPlayer(const Mediator *mediator, QWidget *parent = nullptr);
    ~QPlayer();

    void setData(Tags *tags);
    void updateData(Tags *tags);

public slots:
    void playSound();
    void stopSound();

private:
    void setupLayouts(void);
};