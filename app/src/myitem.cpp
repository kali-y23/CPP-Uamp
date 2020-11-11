#include "myitem.h"

MyItem::MyItem(int x_, int y_, Qt::GlobalColor colour_, QObject *parent)
    : QObject(parent), QGraphicsItem(), x(x_), y(y_), colour(colour_)
{

}

MyItem::~MyItem()
{

}

QRectF MyItem::boundingRect() const
{
    return QRectF(x, y, w, -h);
}

void MyItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(colour);
    painter->setPen(QPen(Qt::NoPen));
    painter->drawRect(QRectF(x, y, w, -h));
    Q_UNUSED(option);
    Q_UNUSED(widget);
}


void MyItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
}