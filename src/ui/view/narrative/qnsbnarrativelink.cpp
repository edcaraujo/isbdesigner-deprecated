#include "qnsbnarrativelink.h"

QnsbNarrativeLink::QnsbNarrativeLink(QnsbGraphicsItem* parent)
    : QnsbGraphicsLink(parent)
{
    setTop(0);
    setLeft(0);
    setWidth(0);
    setHeight(0);
}

QnsbNarrativeLink::~QnsbNarrativeLink()
{

}

QString QnsbNarrativeLink::getType() const
{
    return type;
}

void QnsbNarrativeLink::setType(QString type)
{
    this->type = type;
}

QnsbNarrativeChain* QnsbNarrativeLink::getChain() const
{
    return chain;
}

void QnsbNarrativeLink::setChain(QnsbNarrativeChain* chain)
{
    this->chain = chain;
}

QnsbNarrativeChain* QnsbNarrativeLink::getTarget() const
{
    return target;
}

void QnsbNarrativeLink::setTarget(QnsbNarrativeChain* target)
{
    this->target = target;
}

QString QnsbNarrativeLink::getVarValue() const
{
    return varvalue;
}

void QnsbNarrativeLink::setVarValue(QString varvalue)
{
    this->varvalue = varvalue;
}

QString QnsbNarrativeLink::getVarName() const
{
    return varname;
}

void QnsbNarrativeLink::setVarName(QString varname)
{
    this->varname = varname;
}

QString QnsbNarrativeLink::getOp() const
{
    return op;
}

void QnsbNarrativeLink::setOp(QString op)
{
    this->op = op;
}

QString QnsbNarrativeLink::getKey() const
{
    return key;
}

void QnsbNarrativeLink::setKey(QString key)
{
    this->key = key;
}

void QnsbNarrativeLink::adjust()
{
    setTop(chain->getTop()+24+32);
    setLeft(chain->getLeft()+24);

    if (chain->getTop() == target->getTop()){
        setTop(chain->getTop()+24+32-3);

        setWidth(target->getLeft() - chain->getLeft());
        setHeight(6);

    }else if (chain->getTop() < target->getTop()){
        setWidth(target->getLeft() - chain->getLeft());
        setHeight(target->getTop() - chain->getTop());

    }else if (chain->getTop() > target->getTop()){
        setTop(target->getTop()+24+32);

        setWidth(target->getLeft() - chain->getLeft());
        setHeight(chain->getTop() - target->getTop());
    }
}

void QnsbNarrativeLink::draw(QPainter* painter)
{
    painter->setPen(QPen(QColor("#FFFFFF"), 3));

    if (chain->getTop() == target->getTop()){
        painter->drawLine(0,getHeight()/2,getWidth(),getHeight()/2);

        QLineF line(0,getHeight()/2,getWidth(),getHeight()/2);
        QPointF p = line.pointAt(0.5);

        if (type == "interactive"){
            painter->drawPixmap(p.x() - 24/2,p.y() - 24/2,24,24,QPixmap(":/icon/miniint"));

        }else if (type == "adaptative"){
            painter->drawPixmap(p.x() - 24/2,p.y() - 24/2,24,24,QPixmap(":/icon/miniadp"));

        }else if (type == "sequencial"){
            painter->drawPixmap(p.x() - 24/2,p.y() - 24/2,24,24,QPixmap(":/icon/mininext"));
        }


    }else if (chain->getTop() < target->getTop()){
        painter->drawLine(0,0,getWidth(),getHeight());

        QLineF line(0,0,getWidth(),getHeight());
        QPointF p = line.pointAt(0.5);

        if (type == "interactive"){
            painter->drawPixmap(p.x() - 24/2,p.y() - 24/2,24,24,QPixmap(":/icon/miniint"));

        }else if (type == "adaptative"){
            painter->drawPixmap(p.x() - 24/2,p.y() - 24/2,24,24,QPixmap(":/icon/miniadp"));

        }else if (type == "sequencial"){
            painter->drawPixmap(p.x() - 24/2,p.y() - 24/2,24,24,QPixmap(":/icon/mininext"));
        }

    }else if (chain->getTop() > target->getTop()){
        painter->drawLine(0,getHeight(),getWidth(),0);

        QLineF line(0,getHeight(),getWidth(),0);
        QPointF p = line.pointAt(0.5);

        if (type == "interactive"){
            painter->drawPixmap(p.x() - 24/2,p.y() - 24/2,24,24,QPixmap(":/icon/miniint"));

        }else if (type == "adaptative"){
            painter->drawPixmap(p.x() - 24/2,p.y() - 24/2,24,24,QPixmap(":/icon/miniadp"));

        }else if (type == "sequencial"){
            painter->drawPixmap(p.x() - 24/2,p.y() - 24/2,24,24,QPixmap(":/icon/mininext"));
        }
    }
}

void QnsbNarrativeLink::delineate(QPainterPath* painter) const
{

}
