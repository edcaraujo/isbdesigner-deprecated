#include "qnsbsketchlink.h"

QnsbSketchLink::QnsbSketchLink(QnsbGraphicsItem* parent)
    : QnsbGraphicsLink(parent)
{
    setTop(0);
    setLeft(0);
    setWidth(160);
    setHeight(90);

    setTrigger(NULL);

    selected = false;

    subtype = "";
}

QnsbSketchLink::~QnsbSketchLink()
{

}

QString QnsbSketchLink::getType() const
{
    return type;
}

void QnsbSketchLink::setType(QString type)
{
    this->type = type;
}

bool QnsbSketchLink::isSelected()
{
    return selected;
}

void QnsbSketchLink::setSelected(bool selected)
{
    this->selected = selected;
}

QnsbSketchChain* QnsbSketchLink::getChain() const
{
    return chain;
}

void QnsbSketchLink::setChain(QnsbSketchChain* chain)
{
    this->chain = chain;
}

QnsbSketchChain* QnsbSketchLink::getTarget() const
{
    return target;
}

void QnsbSketchLink::setTarget(QnsbSketchChain* target)
{
    this->target = target;
}

QnsbSketchObject* QnsbSketchLink::getTrigger() const
{
    return trigger;
}

void QnsbSketchLink::setTrigger(QnsbSketchObject* trigger)
{
    this->trigger = trigger;
}

QString QnsbSketchLink::getVarValue() const
{
    return varvalue;
}

void QnsbSketchLink::setVarValue(QString varvalue)
{
    this->varvalue = varvalue;
}

QString QnsbSketchLink::getVarName() const
{
    return varname;
}

void QnsbSketchLink::setVarName(QString varname)
{
    this->varname = varname;
}

QString QnsbSketchLink::getOp() const
{
    return op;
}

void QnsbSketchLink::setOp(QString op)
{
    this->op = op;
}

QString QnsbSketchLink::getKey() const
{
    return key;
}

void QnsbSketchLink::setKey(QString key)
{
    this->key = key;
}

void QnsbSketchLink::adjust()
{

}

void QnsbSketchLink::draw(QPainter* painter)
{
    painter->setBrush(QBrush(Qt::white));
    painter->drawRect(24/2,getHeight()/2 - 6/2,56, 6);

    if (selected){
        painter->setPen(QPen(QBrush(QColor("#FF9900")),2));
        painter->drawRect(24/2,getHeight()/2 - 6/2,56, 6);

        painter->setPen(QPen(QBrush(QColor("#FF9900")),5));
        painter->drawEllipse(0,getHeight()/2 - 24/2,24,24);
        painter->drawEllipse(24/2 + 56 - 48/2,getHeight()/2 - 48/2,48,48);
    }

    if (target->getType() == "linear"){
        painter->drawPixmap(24/2 + 56 - 48/2,getHeight()/2 - 48/2,48,48,QPixmap(":/icon/nalter"));

    }else if (target->getType() == "distributive"){
        painter->drawPixmap(24/2 + 56 - 48/2,getHeight()/2 - 48/2,48,48,QPixmap(":/icon/ndist"));

    }else if (target->getType() == "referencial"){
        painter->drawPixmap(24/2 + 56 - 48/2,getHeight()/2 - 48/2,48,48,QPixmap(":/icon/nref"));
    }

    if (type == "interactive"){
        painter->drawPixmap(0,getHeight()/2 - 24/2,24,24,QPixmap(":/icon/miniint"));

    }else if (type == "adaptative"){
        painter->drawPixmap(0,getHeight()/2 - 24/2,24,24,QPixmap(":/icon/miniadp"));

    }else if (type == "sequencial"){
        painter->drawPixmap(0,getHeight()/2 - 24/2,24,24,QPixmap(":/icon/mininext"));
    }

    painter->setPen(QColor("#FFFFFF"));

    if (target->getType() != "referencial"){
        painter->drawText(QRect(24/2 + 56 - 48/2 + 8,getHeight()/2 - 48/2 - 24,64,24),target->getTitle());
    }else{
        painter->drawText(QRect(24/2 + 56 - 48/2 + 8,getHeight()/2 - 48/2 - 24,64,24),target->getMatrix()->getTitle());
    }
}

void QnsbSketchLink::delineate(QPainterPath* painter) const
{
    painter->addRect(24/2,getHeight()/2 - 6/2,56, 6);

    painter->addRect(0,getHeight()/2 - 24/2,24,24);

    painter->addRect(24/2 + 56 - 48/2,getHeight()/2 - 48/2,48,48);
}

void QnsbSketchLink::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    QnsbGraphicsLink::mousePressEvent(event);

    if (!event->isAccepted()){
        if (event->button() == Qt::LeftButton){
            setSelected(true);

            emit linkSelected(this);
        }
    }
}

void QnsbSketchLink::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
{
    if (event->button() == Qt::LeftButton){
        if (target->getType() != "referencial"){
            emit chainSelected(target);

            target->getView()->centerOn(0,target->getHeight()/2);
        }else{
            emit chainSelected(target->getMatrix());

            target->getMatrix()->getView()->centerOn(0,target->getMatrix()->getHeight()/2);
        }
    }

    QnsbGraphicsLink::mouseDoubleClickEvent(event);
}
