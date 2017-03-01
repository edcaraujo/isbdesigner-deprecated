#ifndef QNSBSKETCHDIMENSION_H
#define QNSBSKETCHDIMENSION_H

#include <QDebug>
#include <QDialog>
#include <QList>
#include <QGraphicsSceneMouseEvent>

#include "ui/view/qnsbgraphicsdimension.h"

#include "qnsbsketchchain.h"
#include "qnsbsketchpanel.h"
#include "qnsbsketchlink.h"
#include "qnsbsketchview.h"

#include "ui_QnsbSketchLinkTargetForm.h"

using namespace Ui;

class QnsbSketchChain;
class QnsbSketchPanel;
class QnsbSketchLink;

class QnsbSketchDimension : public QnsbGraphicsDimension
{
    Q_OBJECT

public:
    QnsbSketchDimension(QnsbGraphicsItem* parent = 0);

    virtual ~QnsbSketchDimension();

    void setLock(bool lock);

    QString getName();

    void setName(QString name);

    QnsbSketchChain* getChain() const;

    void setChain(QnsbSketchChain* chain);

    QList<QnsbSketchPanel*> getPanels() const;

    void addPanel(QnsbSketchPanel* panel);

    void removePanel(QnsbSketchPanel* panel);

    void adjust();

signals:
    void panelAdded(QnsbSketchPanel* panel);

    void panelChanged(QnsbSketchPanel* panel);

    void chainAdded(QnsbSketchChain* chain);

    void chainChange(QnsbSketchChain* chain);

    void chainSelected(QnsbSketchChain* chain);

    void dimensionAdded(QnsbSketchDimension* dimension);

    void linkAdded(QnsbSketchLink* link);

    void panelSelected(QnsbSketchPanel* panel);

    void objectAdded(QnsbSketchObject* object);

    void objectRemoved(QnsbSketchObject* object);

    void objectChanged(QnsbSketchObject* object);

    void objectSelected(QnsbSketchObject* object);

protected:
    void draw(QPainter* painter);

    void delineate(QPainterPath* painter) const;

    void mousePressEvent(QGraphicsSceneMouseEvent* event);

//    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event);

private:
    QString name;

    bool lock;

    bool iselected;

    QnsbSketchChain* chain;

    QDialog* d;

    QnsbSketchLinkTargetForm targerForm;

    QList<QnsbSketchPanel*> panels;
};

#endif // QNSBSKETCHDIMENSION_H
