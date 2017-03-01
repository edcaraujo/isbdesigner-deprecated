#ifndef QNSBNARRATIVECHAIN_H
#define QNSBNARRATIVECHAIN_H

#include <QDebug>

#include "ui/view/qnsbgraphicsitem.h"

#include "qnsbnarrativelink.h"

class QnsbNarrativeLink;

class QnsbNarrativeChain : public QnsbGraphicsItem
{
    Q_OBJECT

public:
    QnsbNarrativeChain(QnsbGraphicsItem* parent = 0);

    virtual ~QnsbNarrativeChain();

    bool isSelected();

    void setSelected(bool selected);

    QnsbNarrativeChain* getMatrix();

    void setMatrix(QnsbNarrativeChain* matrix);

    QString getType();

    void setType(QString type);

    QString getTitle() const;

    void setTitle(QString  title);

    QVector<QnsbNarrativeLink*> getLinks() const;

    void addLink(QnsbNarrativeLink* link);

    void removeLink(QnsbNarrativeLink* link);

    void adjust();

signals:
    void chainSelected(QnsbNarrativeChain* chain);

protected:
    void draw(QPainter* painter);

    void delineate(QPainterPath* painter) const;

    void mousePressEvent(QGraphicsSceneMouseEvent* event);

private:
    QString type;

    QString title;

    bool selected;

    QnsbNarrativeChain* matrix;

    QVector<QnsbNarrativeLink*> links;
};

#endif // QNSBNARRATIVECHAIN_H
