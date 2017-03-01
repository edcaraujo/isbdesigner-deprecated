#ifndef QNSBSKETCHLINK_H
#define QNSBSKETCHLINK_H

#include "ui/view/qnsbgraphicslink.h"

#include "qnsbsketchchain.h"
#include "qnsbsketchobject.h"

class QnsbSketchChain;
class QnsbSketchObject;

class QnsbSketchLink : public QnsbGraphicsLink
{
    Q_OBJECT
public:
    QnsbSketchLink(QnsbGraphicsItem* parent = 0);

    virtual ~QnsbSketchLink();

    bool isSelected();

    void setSelected(bool selected);

    QString getType() const;

    void setType(QString type);

    QnsbSketchChain* getChain() const;

    void setChain(QnsbSketchChain* chain);

    QnsbSketchChain* getTarget() const;

    void setTarget(QnsbSketchChain* target);

    QnsbSketchObject* getTrigger() const;

    void setTrigger(QnsbSketchObject* trigger);

    QString getKey() const;

    void setKey(QString key);

    QString getVarValue() const;

    void setVarValue(QString varvalue);

    QString getVarName() const;

    void setVarName(QString varname);

    QString getOp() const;

    void setOp(QString op);

    void adjust();

signals:
    void chainSelected(QnsbSketchChain* chain);

    void linkSelected(QnsbSketchLink* link);

protected:
    virtual void draw(QPainter* painter);

    virtual void delineate(QPainterPath* painter) const;

    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);

    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event);

private:
    QString key;

    QString varname;

    QString op;

    QString varvalue;

    QString type;

    bool selected;

    QString subtype;

    QnsbSketchChain* chain;

    QnsbSketchChain* target;

    QnsbSketchObject* trigger;
};

#endif // QNSBSKETCHLINK_H
