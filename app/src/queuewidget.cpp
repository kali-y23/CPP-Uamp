#include "queuewidget.h"

Element::Element(Tags *tags_) : QListWidgetItem() {
    widget = new QWidget;

    tags = tags_;

    layoutOuter = new QHBoxLayout(widget);
    layoutInner = new QVBoxLayout();

    labelAlbumCover = new QLabel("ALBUM COVER\nWILL BE HERE");
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
    connect(this, SIGNAL(itemDoubleClicked(QListWidgetItem *)), this, SLOT(sendNextSong(QListWidgetItem *)));
}

QueueWidget::~QueueWidget() {
    clearElements();
}

void QueueWidget::setQueue(const std::deque<Tags *>& queue_) {
    current_song = 0;
    queue.createQueue(queue_);
    showQueue();

    if (!elements.empty())
        emit sendFirstSongToPlayer(elements[0]->getTags());
};

void QueueWidget::showQueue() {
    clearElements();
    const std::deque<Tags *> queue_ = queue.getQueue();
    for (auto it = queue_.begin() + current_song; it != queue_.end(); ++it) {
        Element *el = new Element(*it);
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
    else if (repeat_mode == REPEAT_SONG) {
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
}

void QueueWidget::changeRepeatMode(int index) {
    repeat_mode = index;
    showQueue();
}

void QueueWidget::sendNextSong(QListWidgetItem *item) {
    // current_song = indexFromItem(item).row();
    // std::cout << current_song << std::endl;
    // showQueue();
    emit sendSongToPlayer(reinterpret_cast<Element *>(item)->getTags());
}
