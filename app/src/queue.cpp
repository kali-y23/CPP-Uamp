#include "queue.h"

Queue::Queue() {
    //
}

Queue::~Queue() {
    clearQueue();
}

void Queue::createQueue(const std::deque<Tags *>& queue_, Qt::SortOrder order_, int tag) {
    if (!queue.empty())
        clearQueue();

    queue = std::deque<Tags *>(queue_);
    order = order_;
    mode = static_cast<SortBy>(tag);
}

void Queue::clearQueue(void) {
    if (queue.empty())
        return;

    queue.clear();
}

int Queue::addToQueue(Tags *song) {
    if (shuffle) {
        queue.push_back(song);
        // shuffleSongs(song);
        return -1;
    }

    int i = 0;
    int size = queue.size();

    int intTag = 0;
    QString strTag;
    int intOtherTag = 0;
    QString strOtherTag;

    while (i < size) {
        if (mode == SortBy::Title) {
            strTag = song->getTitle().toString();
            strOtherTag = queue[i]->getTitle().toString();
        }
        else if (mode == SortBy::Genre) {
            strTag = song->getGenre().toString();
            strOtherTag = queue[i]->getGenre().toString();
        }
        else if (mode == SortBy::Artist) {
            strTag = song->getArtist().toString();
            strOtherTag = queue[i]->getArtist().toString();
        }
        else if (mode == SortBy::Album) {
            strTag = song->getAlbum().toString();
            strOtherTag = queue[i]->getAlbum().toString();
        }
        else if (mode == SortBy::Year) {
            intTag = song->getYear().toInt();
            intOtherTag = queue[i]->getYear().toInt();
        }
        else if (mode == SortBy::Track) {
            intTag = song->getTrack().toInt();
            intOtherTag = queue[i]->getTrack().toInt();
        }

        if (order == Qt::DescendingOrder) {
            if (mode == SortBy::Track || mode == SortBy::Year) {
                if (intTag < intOtherTag) {
                    queue.insert(queue.begin() + i, song);
                    return i;
                }
            }
            else {
                if (strTag < strOtherTag) {
                    queue.insert(queue.begin() + i, song);
                    return i;
                }
            }
        }
        else {
            if (mode == SortBy::Track || mode == SortBy::Year) {
                if (intTag > intOtherTag) {
                    queue.insert(queue.begin() + i, song);
                    return i;
                }
            } 
            else {
                if (strTag > strOtherTag) {
                    queue.insert(queue.begin() + i, song);
                    return i;
                }
            }
        }
        ++i;
    }
    return -2;
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

void Queue::setShuffle(bool shuffle_) {
    shuffle = shuffle_;
}


