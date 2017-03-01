#ifndef QNSBAUTHORDIMENSION_H
#define QNSBAUTHORDIMENSION_H

#include <QGraphicsSceneMouseEvent>

#include "ui/view/qnsbgraphicsdimension.h"

#include "qnsbauthorchain.h"
#include "qnsbauthorpanel.h"

class QnsbAuthorChain;
class QnsbAuthorPanel;

class QnsbAuthorDimension : public QnsbGraphicsDimension
{
    Q_OBJECT

public:
    QnsbAuthorDimension(QnsbGraphicsItem* parent = 0);

    ~QnsbAuthorDimension();

    QString getName();

    void setName(QString name);

    QnsbAuthorChain* getChain() const;

    void setChain(QnsbAuthorChain* chain);

    QList<QnsbAuthorPanel*> getPanels() const;

    void addPanel(QnsbAuthorPanel* panel);

    void removePanel(QnsbAuthorPanel* panel);

    void adjust();

signals:
    void chainSelected(QnsbAuthorChain* chain);

    void panelChanged(QnsbAuthorPanel* panel);

    void panelSelected(QnsbAuthorPanel* panel);

    void objectAdded(QnsbAuthorObject* object);

    void objectChanged(QnsbAuthorObject* object);

    void objectSelected(QnsbAuthorObject* object);

protected:
    void draw(QPainter* painter);

    void delineate(QPainterPath* painter) const;

    void mousePressEvent(QGraphicsSceneMouseEvent* event);

private:
    QString name;

    QnsbAuthorChain* chain;

    QList<QnsbAuthorPanel*> panels;
};

#endif // QNSBAUTHORDIMENSION_H
