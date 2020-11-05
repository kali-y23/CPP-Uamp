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

class Component;
class Queue;

class Element : public QListWidgetItem {
    QWidget *widget;

    QHBoxLayout *layoutOuter;
    QVBoxLayout *layoutInner;

    QLabel *labelAlbumCover;
    QLabel *labelTitle;
    QLabel *labelArtist;

    std::string path;

public:
    Element(const Tags &tags);
    ~Element();

    QWidget *getWidget(void) const;
    std::string getPath(void) const;
};



class QueueWidget : public QListWidget, public Component {
    Q_OBJECT

    unsigned int current_song;
    Queue queue;
    std::deque<Element *> elements;
    int repeat_mode;

public:
    QueueWidget(Mediator *mediator, QWidget *parent = nullptr);
    ~QueueWidget();

private:
    void showQueue();
    void clearElements();

public slots:
    void setQueue(const std::deque<Tags *>& queue_);
    void nextSong();
    void prevSong();
    void changeRepeatMode(int index);
    // void chooseFromQueue(int index);
    // void removeFromQueue(int index);
};

#endif