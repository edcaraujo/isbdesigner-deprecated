#include "qnsbobject.h"

QnsbObject::QnsbObject() : QnsbEntity()
{

}

QnsbObject::~QnsbObject()
{

}

QString QnsbObject::getId() const
{
    return id;
}

void QnsbObject::setId(QString id)
{
    this->id = id;
}

QnsbPanel* QnsbObject::getPanel() const
{
    return panel;
}

void QnsbObject::setPanel(QnsbPanel* panel)
{
    this->panel = panel;
}

QString QnsbObject::getInstanceId() const
{
    return instanceId;
}

void QnsbObject::setInstanceId(QString instanceId)
{
    this->instanceId = instanceId;
}

QString QnsbObject::getStatusId() const
{
    return statusId;
}

void QnsbObject::setStatusId(QString statusId)
{
    this->statusId = statusId;
}

QString QnsbObject::getRefer() const
{
    return refer;
}

void QnsbObject::setRefer(QString refer)
{
    this->refer = refer;
}

QString QnsbObject::getSrc() const
{
    return src;
}

void QnsbObject::setSrc(QString src)
{
    this->src = src;
}

QString QnsbObject::getSketch() const
{
    return sketch;
}

void QnsbObject::setSketch(QString sketch)
{
    this->sketch = sketch;
}

QString QnsbObject::getPreview() const
{
    return preview;
}

void QnsbObject::setPreview(QString preview)
{
    this->preview = preview;
}

QString QnsbObject::getType() const
{
    return type;
}

void QnsbObject::setType(QString type)
{
    this->type = type;
}


QString QnsbObject::getVarValue() const
{
    return varvalue;
}

void QnsbObject::setVarValue(QString varvalue)
{
    this->varvalue = varvalue;
}

QString QnsbObject::getVarName() const
{
    return varname;
}

void QnsbObject::setVarName(QString varname)
{
    this->varname = varname;
}
