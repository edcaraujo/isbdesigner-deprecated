#include "qnsbgraphicsitem.h"

QnsbGraphicsItem::QnsbGraphicsItem(QnsbGraphicsItem* parent)
    : QGraphicsItem(parent)
{
    setUid(QUuid::createUuid().toString());
}

QnsbGraphicsItem::~QnsbGraphicsItem()
{

}

QString QnsbGraphicsItem::getUid() const
{
    return uid;
}

void QnsbGraphicsItem::setUid(QString uid)
{
    this->uid = uid;
}

qreal QnsbGraphicsItem::getTop() const
{
    return top;
}

void QnsbGraphicsItem::setTop(qreal top)
{
    this->top = top;

    setY(top);
}

qreal QnsbGraphicsItem::getLeft() const
{
    return left;
}

void QnsbGraphicsItem::setLeft(qreal left)
{
    this->left = left;

    setX(left);
}

qreal QnsbGraphicsItem::getRight() const
{
    return right;
}

void QnsbGraphicsItem::setRight(qreal right)
{
    this->right = right;
}

qreal QnsbGraphicsItem::getBottom() const
{
    return bottom;
}

void QnsbGraphicsItem::setBottom(qreal bottom)
{
    this->bottom = bottom;
}

qreal QnsbGraphicsItem::getWidth() const
{
    return width;
}

void QnsbGraphicsItem::setWidth(qreal width)
{
    this->width = width;
}

qreal QnsbGraphicsItem::getHeight() const
{
    return height;
}

void QnsbGraphicsItem::setHeight(qreal height)
{
    this->height = height;
}

QPainterPath QnsbGraphicsItem::shape() const
{
    QPainterPath painter;

    delineate(&painter);

    return painter;
}

QRectF QnsbGraphicsItem::boundingRect() const
{
    QRectF bounds;

    bounds.setX(0);
    bounds.setY(0);
    bounds.setWidth(width);
    bounds.setHeight(height);

    return bounds;
}

void QnsbGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing,true);
    painter->setRenderHint(QPainter::TextAntialiasing,true);
    painter->setRenderHint(QPainter::SmoothPixmapTransform,true);

    draw(painter);
}
