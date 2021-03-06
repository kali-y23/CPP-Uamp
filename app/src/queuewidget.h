// I started using ifndef instead of pragma once because of the info in the link I sent you
// And you should do so too
// Don't fuck with me about it
// In return, I promise all new variables that I create will be in camelcase

// xoxo Yulia

#ifndef QUEUE_WIDGET
#define QUEUE_WIDGET

#include <QtWidgets>
#include <string>

#include "queue.h"
#include "component.h"

#define NO_REPEAT 0
#define REPEAT_PLAYLIST 1
#define REPEAT_SONG 2

#define NO_SHUFFLE 0
#define SHUFFLE 1

class Component;
class Queue;

class Element : public QListWidgetItem {
    QWidget *widget;

    QHBoxLayout *layoutOuter;
    QVBoxLayout *layoutInner;

    QLabel *labelAlbumCover;
    QLabel *labelTitle;
    QLabel *labelArtist;

    Tags *tags;

public:
    Element(Tags *tags_);
    ~Element();

    QWidget *getWidget(void) const;
    Tags *getTags(void) const;
};



class QueueWidget : public QListWidget, public Component {
    Q_OBJECT

    unsigned int current_song = 0;
    Queue queue;
    std::deque<Element *> elements;
    int repeat_mode = NO_REPEAT;
    bool shuffle = false;

    QMenu *remove_item_menu;
    QAction *remove_item_action;

public:
    QueueWidget(Mediator *mediator, QWidget *parent = nullptr);
    ~QueueWidget();

    Tags *getNextSong(void);

private:
    void showQueue();
    void clearElements();
    void mousePressEvent(QMouseEvent *event);

public slots:
    void setQueue(const std::deque<Tags *>& queue_, Qt::SortOrder order, int tag);
    void sendNextSong(QListWidgetItem *item);
    void nextSong();
    void prevSong();
    void changeRepeatMode(int index);
    void changeShuffleMode(int index);
    void insertToQueue(Tags *song);
    void jumpToSong(Tags *song);
    void removeFromQueue(Tags *song = nullptr);
 
signals:
    void sendFirstSongToPlayer(Tags *tags);
    void sendSongToPlayer(Tags *tags);
    void rightClick(QPoint *pos);
};

#endif