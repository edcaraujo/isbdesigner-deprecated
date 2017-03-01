#include "qnsblink.h"

QnsbLink::QnsbLink()
{
    setKey("");
    setTrigger(NULL);
}

QnsbLink::~QnsbLink()
{

}

QnsbChain* QnsbLink::getChain() const
{
    return chain;
}

void QnsbLink::setChain(QnsbChain* chain)
{
    this->chain = chain;
}

QnsbChain* QnsbLink::geteTarget() const
{
    return etarget;
}

void QnsbLink::seteTarget(QnsbChain* etarget)
{
    this->etarget = etarget;
}

QString QnsbLink::getTarget() const
{
    return target;
}

void QnsbLink::setTarget(QString target)
{
    this->target = target;
}

QString QnsbLink::getVarValue() const
{
    return varvalue;
}

void QnsbLink::setVarValue(QString varvalue)
{
    this->varvalue = varvalue;
}

QString QnsbLink::getVarName() const
{
    return varname;
}

void QnsbLink::setVarName(QString varname)
{
    this->varname = varname;
}

QString QnsbLink::getOp() const
{
    return op;
}

void QnsbLink::setOp(QString op)
{
    this->op = op;
}

QnsbObject* QnsbLink::getTrigger() const
{
    return trigger;
}

void QnsbLink::setTrigger(QnsbObject* trigger)
{
    this->trigger = trigger;
}

QString QnsbLink::getType() const
{
    return type;
}

void QnsbLink::setType(QString type)
{
    this->type = type;
}

QString QnsbLink::getKey() const
{
    return key;
}

void QnsbLink::setKey(QString key)
{
    this->key = key;
}



