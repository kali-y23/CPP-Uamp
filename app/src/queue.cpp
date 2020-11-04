#include "queue.h"

Queue::Queue() {
    //
}

Queue::~Queue() {
    clearQueue();
}

void Queue::createQueue(const std::deque<Tags *>& queue_) {
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

// Is it technically possible to guarantee exactly the same pointer comes to this function?
// Esp from the table view!! Think about it
void Queue::removeFromQueue(Tags *song) {
    for (auto it = queue.begin(); it != queue.end(); ++it) {
        if (*it == song) {
            queue.erase(it);
            break;
        }
    }
}

void Queue::removeFromQueue(std::deque<Tags *>::iterator song) {
    queue.erase(song);
}

const std::deque<Tags *>& Queue::getQueue(void) const {
    return queue;
}

int Queue::getQueueSize(void) const {
    return queue.size();
}

// void Queue::shuffleSongs(Tags *song) {

// }

void Queue::sortByTag(SortBy tag) {
    if (tag == SortBy::Title) {
        std::sort(queue.begin(), queue.end(), [](const Tags* a1, const Tags* a2) {
            return a1->getTitle().toString() < a2->getTitle().toString();
        });
    }
    else if (tag == SortBy::Artist) {
        std::sort(queue.begin(), queue.end(), [](const Tags* a1, const Tags* a2) {
            return a1->getArtist().toString() < a2->getTitle().toString();
        });
    }
    else if (tag == SortBy::Album) {
        std::sort(queue.begin(), queue.end(), [](const Tags* a1, const Tags* a2) {
            return a1->getAlbum().toString() < a2->getTitle().toString();
        });
    }
    else if (tag == SortBy::Genre) {
        std::sort(queue.begin(), queue.end(), [](const Tags* a1, const Tags* a2) {
            return a1->getGenre().toString() < a2->getTitle().toString();
        });
    }
    else if (tag == SortBy::Year) {
        std::sort(queue.begin(), queue.end(), [](const Tags* a1, const Tags* a2) {
            return a1->getYear().toInt() < a2->getTitle().toInt();
        });
    }
}




