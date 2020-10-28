// I started using ifndef instead of pragma once because of the info in the link I sent you
// And you should do so too
// Don't fuck with me about it
// In return, I promise all new variables that I create will be in camelcase

// xoxo Yulia

#ifndef QUEUE
#define QUEUE

#include <QtWidgets>
#include <list>

#include "component.h"
#include "tags.h"

enum class SortBy {
    Title,
    Artist,
    Album,
    Genre,
    Year
};

class Component;

class Queue : public QObject, public Component {
    Q_OBJECT

    std::list<Tags *> queue;

public:
    Queue(Mediator *mediator);
    ~Queue();

    void createQueue(const std::list<Tags *>& queue_);
    void clearQueue(void);

    void addToQueue(Tags *song);
    void removeFromQueue(Tags *song);
    void Queue::removeFromQueue(std::list<Tags *>::iterator song);

    // void shuffleSongs(Tags *song);

    const std::list<Tags *>& getQueue(void) const;
};

#endif