#include "queue.h"

Queue::Queue(Mediator *mediator) : Component(mediator) {
    //
}

Queue::~Queue() {
    clearQueue();
}

void Queue::createQueue(const std::list<Tags *>& queue_) {
    if (!queue.empty())
        clearQueue();

    queue = queue_;
}

void Queue::clearQueue(void) {
    if (queue.empty())
        return;

    for (Tags *tags : queue)
        delete tags;

    queue.clear();
}

void Queue::addToQueue(Tags *song) {
    queue.push_back(song);
}

void Queue::removeFromQueue(Tags *song) {
    for (auto it = queue.begin(); it != queue.end(); ++it) {
        if (*it == song) {
            queue.erase(it);
            break;
        }
    }
}

void Queue::removeFromQueue(std::list<Tags *>::iterator song) {
    queue.erase(song);
}

const std::list<Tags *>& getQueue(void) const {
    return queue;
}
