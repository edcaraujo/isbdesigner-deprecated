#ifndef QNSBLINK_H
#define QNSBLINK_H

#include "qnsbentity.h"
#include "qnsbchain.h"
#include "qnsbobject.h"

class QnsbChain;

class QnsbObject;

class QnsbLink : public QnsbEntity
{
public:
    QnsbLink();

    virtual ~QnsbLink();

    QnsbChain* getChain() const;

    void setChain(QnsbChain* chain);

    QnsbChain* geteTarget() const;

    void seteTarget(QnsbChain* etarget);

    QString getTarget() const;

    void setTarget(QString target);

    QnsbObject* getTrigger() const;

    void setTrigger(QnsbObject* trigger);

    QString getType() const;

    void setType(QString type);

    QString getKey() const;

    void setKey(QString key);

    QString getVarValue() const;

    void setVarValue(QString varvalue);

    QString getVarName() const;

    void setVarName(QString varname);

    QString getOp() const;

    void setOp(QString op);

private:
    QnsbChain* chain;

    QnsbChain* etarget;

    QnsbObject* trigger;

    QString target;

    QString varname;

    QString op;

    QString varvalue;

    QString type;

    QString key;
};

#endif // QNSBLINK_H
