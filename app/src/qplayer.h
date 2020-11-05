#pragma once

#include <QtWidgets>
#include <utility>
#include <thread>
#include <chrono>

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
    QGridLayout *label;

    QWidget *player_widget;
    QWidget *playerEnabled;
    QWidget *playerDisabled;

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
    QLabel *label1;
    QLabel *label2;

    QLineEdit *edit_search;
    QStackedLayout *layoutOuter;

    Tags *data = nullptr;
    HSTREAM stream;
    bool playing = 0;
    std::thread thr;

public:
    QPlayer(const Mediator *mediator, QWidget *parent = nullptr);
    ~QPlayer();

    void updateData(Tags *tags);
    void setWidget(QWidget *widget);

signals:
    void changeWidget(QWidget *widget, bool play);
    void toggleQueueSignal(void);
    void nextSong();
    void prevSong();

public slots:
    void playSound();
    void stopSound();
    void setPosition(int pos);
    void setPosition();
    void skipFwd();
    void skipBck();
    void displayData(int pos);
    void setWidget(QWidget *widget, bool play);
    void playlistButtonClicked(void);
    void threadFunction();
    void setData(Tags *tags);

private:
    void setupLayouts(void);
};