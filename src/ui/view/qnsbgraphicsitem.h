#ifndef QNSBGRAPHICSITEM_H
#define QNSBGRAPHICSITEM_H

#include <QGraphicsItem>
#include <QPainter>
#include <QRectF>
#include <QPainterPath>
#include <QStyleOptionGraphicsItem>
#include <QWidget>
#include <QMap>
#include <QUuid>

class QnsbGraphicsItem : public QObject, public QGraphicsItem
{
public:
    QnsbGraphicsItem(QnsbGraphicsItem* parent = 0);

    virtual ~QnsbGraphicsItem();

    QString getUid() const;

    void setUid(QString uid);

    qreal getTop() const;

    void setTop(qreal top);

    qreal getLeft() const;

    void setLeft(qreal left);

    qreal getRight() const;

    void setRight(qreal right);

    qreal getBottom() const;

    void setBottom(qreal bottom);

    qreal getWidth() const;

    void setWidth(qreal width);

    qreal getHeight() const;

    void setHeight(qreal height);

    virtual void adjust() = 0;

protected:
    virtual void draw(QPainter* painter) = 0;

    virtual void delineate(QPainterPath* painter) const = 0;

    virtual QPainterPath shape() const;

    virtual QRectF boundingRect() const;

    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

private:
    QString uid;

    qreal top;

    qreal left;

    qreal right;

    qreal bottom;

    qreal width;

    qreal height;
};

#endif // QNSBGRAPHICSITEM_H
