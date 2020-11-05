#include "queuewidget.h"

Element::Element(const Tags& tags) : QListWidgetItem() {
    widget = new QWidget;

    path = tags.getPath().toString().toStdString();

    layoutOuter = new QHBoxLayout(widget);
    layoutInner = new QVBoxLayout();

    labelAlbumCover = new QLabel("ALBUM COVER\nWILL BE HERE");
    labelTitle = new QLabel(tags.getTitle().toString());
    labelArtist = new QLabel(tags.getArtist().toString());

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

std::string Element::getPath(void) const {
    return path;
}

QWidget *Element::getWidget(void) const {
    return widget;
}

QueueWidget::QueueWidget(Mediator *mediator, QWidget *parent) : QListWidget(parent), Component(mediator) {
    // QObject::connect(this, SIGNAL(nextSong()), mediator, SLOT(nextSong));
}

QueueWidget::~QueueWidget() {
    clearElements();
}

void QueueWidget::setQueue(const std::deque<Tags *>& queue_) {
    current_song = 0;
    queue.createQueue(queue_);
    showQueue();
};

void QueueWidget::showQueue() {
    clearElements();
    const std::deque<Tags *> queue_ = queue.getQueue();

    for (auto it = queue_.begin() + current_song; it != queue_.end(); ++it) {
        Element *el = new Element(**it);
        addItem(reinterpret_cast<QListWidgetItem *>(el));
        setItemWidget(reinterpret_cast<QListWidgetItem *>(el), el->getWidget());
        elements.push_back(el);
        if (repeat_mode == REPEAT_SONG)
            return;
    }

    if (repeat_mode == REPEAT_PLAYLIST) {
        for (auto it = queue_.begin(); it != queue_.end() && it != queue_.begin() + current_song; ++it) {
            Element *el = new Element(**it);
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

void QueueWidget::prevSong() {
    if (repeat_mode == REPEAT_SONG) {
        // call player to start the song over
    }
    else if ((current_song > 0 && queue.getQueueSize() > 0) || (repeat_mode == REPEAT_PLAYLIST)) {
        int new_index = current_song == 0 ? queue.getQueueSize() - 1 : current_song - 1;
        Element *el = new Element(*queue.getQueue()[new_index]);

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
