#pragma once

#include <QtWidgets>

class MyItem : public QObject, public QGraphicsItem {
    Q_OBJECT

public:
    explicit MyItem(int x_, int y_, Qt::GlobalColor colour_, QObject *parent = 0);
    ~MyItem();

    float w = 1;
    float h = 0;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    int x;
    int y;
    Qt::GlobalColor colour;
};