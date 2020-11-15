#include "queuewidget.h"

Element::Element(Tags *tags_) : QListWidgetItem() {
    widget = new QWidget;

    tags = tags_;

    layoutOuter = new QHBoxLayout(widget);
    layoutInner = new QVBoxLayout();

    labelAlbumCover = new QLabel();
    labelAlbumCover->setPixmap(tags->getImage()->scaled(40, 40));
    labelTitle = new QLabel(tags->getTitle().toString());
    labelArtist = new QLabel(tags->getArtist().toString());

    layoutOuter->addWidget(labelAlbumCover);
    layoutOuter->addLayout(layoutInner);
    layoutOuter->setSizeConstraint(QLayout::SetFixedSize);

    layoutInner->addWidget(labelTitle);
    layoutInner->addWidget(labelArtist);

    setSizeHint(widget->sizeHint());
}

Element::~Element() {
    delete widget;
}

Tags *Element::getTags(void) const {
    return tags;
}

QWidget *Element::getWidget(void) const {
    return widget;
}

QueueWidget::QueueWidget(Mediator *mediator, QWidget *parent) : QListWidget(parent), Component(mediator) {
    remove_item_menu = new QMenu(this);
    remove_item_action = new QAction("Remove song from queue", this);
    remove_item_menu->addAction(remove_item_action);
    current_song = 0;

    connect(this, SIGNAL(itemDoubleClicked(QListWidgetItem *)), this, SLOT(sendNextSong(QListWidgetItem *)));
    connect(remove_item_action, SIGNAL(triggered()), this, SLOT(removeFromQueue()));
}

QueueWidget::~QueueWidget() {
    clearElements();
    delete remove_item_menu;
    delete remove_item_action;
}

void QueueWidget::setQueue(const std::deque<Tags *>& queue_, Qt::SortOrder order, int tag) {
    current_song = 0;
    queue.createQueue(queue_, order, tag);
    showQueue();

    if (!elements.empty())
        emit sendFirstSongToPlayer(elements[0]->getTags());
};

void QueueWidget::showQueue() {
    clearElements();
    const std::deque<Tags *>& queue_ = queue.getQueue();

    for (auto it = queue_.begin() + current_song; it != queue_.end(); ++it) {
        Tags *tags = *it;
        Element *el = new Element(tags);
        addItem(reinterpret_cast<QListWidgetItem *>(el));
        setItemWidget(reinterpret_cast<QListWidgetItem *>(el), el->getWidget());
        elements.push_back(el);
        if (repeat_mode == REPEAT_SONG)
            return;
    }

    if (repeat_mode == REPEAT_PLAYLIST) {
        for (auto it = queue_.begin(); it != queue_.end() && it != queue_.begin() + current_song; ++it) {
            Element *el = new Element(*it);
            addItem(reinterpret_cast<QListWidgetItem *>(el));
            setItemWidget(reinterpret_cast<QListWidgetItem *>(el), el->getWidget());
            elements.push_back(el);
        }
    }
}

void QueueWidget::clearElements() {
    if (elements.empty())
        return;

    for (Element *el : elements)
        delete el;

    elements.clear();
}

void QueueWidget::nextSong() {
    if (elements.empty())
        return;
    else if (repeat_mode == REPEAT_SONG && !elements.empty()) {
        emit sendSongToPlayer(elements[0]->getTags());
        return;
    }
    takeItem(0);
    delete elements[0];
    elements.pop_front();
    current_song += 1;

    if (repeat_mode == REPEAT_PLAYLIST) {
        if (current_song >= queue.getQueueSize()) {
            current_song = 0;
        }
        showQueue();
    }

    if (!elements.empty())
        emit sendSongToPlayer(elements[0]->getTags());
}

Tags *QueueWidget::getNextSong(void) {
    nextSong();

    if (!elements.empty()) {
        return elements[0]->getTags();
    }

    return nullptr;
}

void QueueWidget::prevSong() {
    if (repeat_mode == REPEAT_SONG) {
        // call player to start the song over
    }
    else if ((current_song > 0 && queue.getQueueSize() > 0) || (repeat_mode == REPEAT_PLAYLIST)) {
        int new_index = current_song == 0 ? queue.getQueueSize() - 1 : current_song - 1;
        Element *el = new Element(queue.getQueue()[new_index]);

        insertItem(0, reinterpret_cast<QListWidgetItem *>(el));
        setItemWidget(reinterpret_cast<QListWidgetItem *>(el), el->getWidget());
        elements.push_front(el);

        current_song = new_index;
    }

    if (repeat_mode == REPEAT_PLAYLIST)
        showQueue();

    if (!elements.empty())
        emit sendSongToPlayer(elements[0]->getTags());
}

void QueueWidget::changeRepeatMode(int index) {
    repeat_mode = index;
    showQueue();
}

void QueueWidget::changeShuffleMode(int index) {
    Tags *current_tag = queue.getQueue()[current_song];

    if (index == 0) {
        shuffle = false;
        queue.sort();
    }
    else {
        shuffle = true;
        queue.shuffle();
    }

    queue.setShuffle(shuffle);
    current_song = queue.getIndexByTag(current_tag);
    if (current_song == -1) {
        qDebug() << "getIndexByTag returned -1!";
        current_song = 0;
    }
    showQueue();
}

void QueueWidget::sendNextSong(QListWidgetItem *item) {
    current_song += indexFromItem(item).row();
    emit sendSongToPlayer(reinterpret_cast<Element *>(item)->getTags());
    showQueue();
}

void QueueWidget::insertToQueue(Tags *song) {
    int queue_index = queue.addToQueue(song);

    if (shuffle)
        showQueue();
    else {
        if (queue_index > current_song || (queue_index == 0 && current_song == 0)) {
            Element *el = new Element(song);
            insertItem(queue_index - current_song, el);
            setItemWidget(reinterpret_cast<QListWidgetItem *>(el), el->getWidget());
            elements.push_back(el);
        }
        else {
            current_song += 1;
        }
    }
}

void QueueWidget::jumpToSong(Tags *song) {
    const std::deque<Tags *>& queue_ = queue.getQueue();
    int i = 0;
    bool found = false;

    for (const Tags *tag : queue_) {
        if (tag == song) {
            current_song = i;
            showQueue();
            found = true;
            break;
        }
        ++i;
    }

    if (!found) {
        insertToQueue(song);
        jumpToSong(song);
    }
}

void QueueWidget::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::RightButton) {
        setCurrentItem(itemAt(event->pos()));
        remove_item_menu->popup(this->mapToGlobal(event->pos()));
    } else {
        QListWidget::mousePressEvent(event);
    }
}

void QueueWidget::removeFromQueue() {
    QListWidgetItem *item = currentItem();
    int index = currentRow();

    takeItem(index);
    elements.erase(elements.begin() + index);
    queue.removeFromQueue(current_song + index);

    delete item;
}
