#include "queuewidget.h"

Element::Element(const Tags& tags) : QListWidgetItem() {
    widget = new QWidget;

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

QWidget *Element::getWidget(void) const {
    return widget;
}

QueueWidget::QueueWidget(Mediator *mediator, QWidget *parent) : QListWidget(parent), Component(mediator) {
    Tags t1("/Users/ybondarenk/Desktop/Music/1.mp3");
    Tags t2("/Users/ybondarenk/Desktop/Music/2.mp3");
    Tags t3("/Users/ybondarenk/Desktop/Music/3.mp3");

    Element *el1 = new Element(t1);
    Element *el2 = new Element(t2);
    Element *el3 = new Element(t3);

    addItem(reinterpret_cast<QListWidgetItem *>(el1));
    setItemWidget(reinterpret_cast<QListWidgetItem *>(el1), el1->getWidget());

    addItem(reinterpret_cast<QListWidgetItem *>(el2));
    setItemWidget(reinterpret_cast<QListWidgetItem *>(el2), el2->getWidget());

    addItem(reinterpret_cast<QListWidgetItem *>(el3));
    setItemWidget(reinterpret_cast<QListWidgetItem *>(el3), el3->getWidget());
}
