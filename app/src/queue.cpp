#include "queue.h"

Queue::Queue() {
    //
}

Queue::~Queue() {
    clearQueue();
}

void Queue::createQueue(const std::deque<Tags *>& queue_, Qt::SortOrder order_, int tag_) {
    if (!queue.empty())
        clearQueue();

    queue = std::deque<Tags *>(queue_);
    order = order_;
    tag = static_cast<SortBy>(tag_);
}

void Queue::clearQueue(void) {
    if (queue.empty())
        return;

    queue.clear();
}

int Queue::addToQueue(Tags *song) {
    queue.push_back(song);
    if (queue.size() > 1) {
        if (shuffled) {    
    
            shuffle();
    
            return -1;
        }
        else {
    
            sort();
    
            return getIndexByTag(song);
        }
    }

    return 0;


    // if (queue.empty()) {
    //     queue.push_back(song);
    //     return -1;
    // }

    // int i = 0;
    // int size = queue.size();

    // int intTag = 0;
    // QString strTag;
    // int intOtherTag = 0;
    // QString strOtherTag;

    // while (i < size) {
    //     if (tag == SortBy::Title) {
    //         strTag = song->getTitle().toString();
    //         strOtherTag = queue[i]->getTitle().toString();
    //     }
    //     else if (tag == SortBy::Genre) {
    //         strTag = song->getGenre().toString();
    //         strOtherTag = queue[i]->getGenre().toString();
    //     }
    //     else if (tag == SortBy::Artist) {
    //         strTag = song->getArtist().toString();
    //         strOtherTag = queue[i]->getArtist().toString();
    //     }
    //     else if (tag == SortBy::Album) {
    //         strTag = song->getAlbum().toString();
    //         strOtherTag = queue[i]->getAlbum().toString();
    //     }
    //     else if (tag == SortBy::Year) {
    //         intTag = song->getYear().toInt();
    //         intOtherTag = queue[i]->getYear().toInt();
    //     }
    //     else if (tag == SortBy::Track) {
    //         intTag = song->getTrack().toInt();
    //         intOtherTag = queue[i]->getTrack().toInt();
    //     }

    //     if (order == Qt::DescendingOrder) {
    //         if (tag == SortBy::Track || tag == SortBy::Year) {
    //             if (intTag < intOtherTag) {
    //                 queue.insert(queue.begin() + i, song);
    //                 return i;
    //             }
    //         }
    //         else {
    //             if (strTag < strOtherTag) {
    //                 queue.insert(queue.begin() + i, song);
    //                 return i;
    //             }
    //         }
    //     }
    //     else {
    //         if (tag == SortBy::Track || tag == SortBy::Year) {
    //             if (intTag > intOtherTag) {
    //                 queue.insert(queue.begin() + i, song);
    //                 return i;
    //             }
    //         } 
    //         else {
    //             if (strTag > strOtherTag) {
    //                 queue.insert(queue.begin() + i, song);
    //                 return i;
    //             }
    //         }
    //     }
    //     if (i == size - 1) {
    //         queue.push_back(song);
    //         return size;
    //     }
    //     ++i;
    // }
    // return -2;
}

void Queue::removeFromQueue(Tags *song) {
    for (auto it = queue.begin(); it != queue.end(); ++it) {
        if (*it == song) {
            queue.erase(it);
            break;
        }
    }
}

void Queue::removeFromQueue(int index) {
    if (index < queue.size())
        queue.erase(queue.begin() + index);
}

const std::deque<Tags *>& Queue::getQueue(void) const {
    return queue;
}

int Queue::getQueueSize(void) const {
    return queue.size();
}

void Queue::shuffle() {
    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(queue.begin(), queue.end(), g);
}

void Queue::setShuffle(bool shuffle_) {
    shuffled = shuffle_;
}

void Queue::sort() {
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

int Queue::getIndexByTag(Tags *tag) {
    int i = 0;

    for (Tags *t : queue) {
        if (t == tag)
            return i;
        ++i;
    }

    return -1;
}
