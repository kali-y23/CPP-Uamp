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
    if (shuffle) {
        queue.push_back(song);
        shuffleSongs(song);
        return;
    }

    int i = 0;
    int size = queue.size();

    while (i < size) {
        
    }
}

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
        if (order == Qt::DescendingOrder) {
            std::sort(queue.begin(), queue.end(), [](const Tags* a1, const Tags* a2) {
                return a1->getTitle().toString() < a2->getTitle().toString();
            });
        }
        else {
            std::sort(queue.begin(), queue.end(), [](const Tags* a1, const Tags* a2) {
                return a1->getTitle().toString() > a2->getTitle().toString();
            });
        }
    }
    else if (tag == SortBy::Artist) {
        if (order == Qt::DescendingOrder) {
            std::sort(queue.begin(), queue.end(), [](const Tags* a1, const Tags* a2) {
                return a1->getArtist().toString() < a2->getTitle().toString();
            });
        }
        else {
            std::sort(queue.begin(), queue.end(), [](const Tags* a1, const Tags* a2) {
                return a1->getArtist().toString() > a2->getTitle().toString();
            });
        }
    }
    else if (tag == SortBy::Album) {
        if (order == Qt::DescendingOrder) {
            std::sort(queue.begin(), queue.end(), [](const Tags* a1, const Tags* a2) {
                return a1->getAlbum().toString() < a2->getTitle().toString();
            });
        }
        else {
            std::sort(queue.begin(), queue.end(), [](const Tags* a1, const Tags* a2) {
                return a1->getAlbum().toString() > a2->getTitle().toString();
            });
        }
    }
    else if (tag == SortBy::Genre) {
        if (order == Qt::DescendingOrder) {
            std::sort(queue.begin(), queue.end(), [](const Tags* a1, const Tags* a2) {
                return a1->getGenre().toString() < a2->getTitle().toString();
            });
        }
        else {
            std::sort(queue.begin(), queue.end(), [](const Tags* a1, const Tags* a2) {
                return a1->getGenre().toString() > a2->getTitle().toString();
            });
        }
    }
    else if (tag == SortBy::Year) {
        if (order == Qt::DescendingOrder) {
            std::sort(queue.begin(), queue.end(), [](const Tags* a1, const Tags* a2) {
                return a1->getYear().toInt() < a2->getTitle().toInt();
            });
        }
        else {
            std::sort(queue.begin(), queue.end(), [](const Tags* a1, const Tags* a2) {
                return a1->getYear().toInt() > a2->getTitle().toInt();
            });
        }
    }
}




