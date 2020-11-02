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
    // Tags t1("/Users/ybondarenk/Desktop/Music/1.mp3");
    // Tags t2("/Users/ybondarenk/Desktop/Music/2.mp3");
    // Tags t3("/Users/ybondarenk/Desktop/Music/3.mp3");

    // Element *el1 = new Element(t1);
    // Element *el2 = new Element(t2);
    // Element *el3 = new Element(t3);

    // addItem(reinterpret_cast<QListWidgetItem *>(el1));
    // setItemWidget(reinterpret_cast<QListWidgetItem *>(el1), el1->getWidget());

    // addItem(reinterpret_cast<QListWidgetItem *>(el2));
    // setItemWidget(reinterpret_cast<QListWidgetItem *>(el2), el2->getWidget());

    // addItem(reinterpret_cast<QListWidgetItem *>(el3));
    // setItemWidget(reinterpret_cast<QListWidgetItem *>(el3), el3->getWidget());
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

void QueueWidget::nextSong(void) {
    delete elements[0];
    takeItem(0);
    current_song += 1;

    if (current_song >= elements.size()) {
        current_song = 0;
        showQueue();
    }
}

void QueueWidget::prevSong(void) {
    if (current_song > 0) {
        Element *el = new Element(*queue.getQueue()[current_song - 1]);

        addItem(reinterpret_cast<QListWidgetItem *>(el));
        setItemWidget(reinterpret_cast<QListWidgetItem *>(el), el->getWidget());
        elements.push_front(el);
    }
}
