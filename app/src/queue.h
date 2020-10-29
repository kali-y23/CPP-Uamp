// I started using ifndef instead of pragma once because of the info in the link I sent you
// And you should do so too
// Don't fuck with me about it
// In return, I promise all new variables that I create will be in camelcase

// xoxo Yulia

#ifndef QUEUE
#define QUEUE

#include <deque>
#include <algorithm>

#include "tags.h"

enum class SortBy {
    Title,
    Artist,
    Album,
    Genre,
    Year
};

class Component;

class Queue {
    std::deque<Tags *> queue;

public:
    Queue();
    ~Queue();

    void createQueue(const std::deque<Tags *>& queue_);
    void clearQueue(void);

    void addToQueue(Tags *song);
    void removeFromQueue(Tags *song);
    void removeFromQueue(std::deque<Tags *>::iterator song);

    const std::deque<Tags *>& getQueue(void) const;

    // void shuffleSongs(Tags *song);
    void sortByTag(SortBy tag);
};

#endif