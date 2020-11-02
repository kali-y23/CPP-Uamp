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
    delete layoutOuter;
    delete layoutInner;
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
    delete elements[0];
    takeItem(0);
    current_song += 1;

    if (current_song >= elements.size()) {
        current_song = 0;
        showQueue();
    }
}

void QueueWidget::prevSong() {
    if (current_song > 0) {
        Element *el = new Element(*queue.getQueue()[current_song - 1]);

        addItem(reinterpret_cast<QListWidgetItem *>(el));
        setItemWidget(reinterpret_cast<QListWidgetItem *>(el), el->getWidget());
        elements.push_front(el);
    }
}
