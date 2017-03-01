#ifndef QNSBNARRATIVELINK_H
#define QNSBNARRATIVELINK_H

#include "ui/view/qnsbgraphicslink.h"
#include "qnsbnarrativechain.h"

class QnsbNarrativeChain;

class QnsbNarrativeLink : public QnsbGraphicsLink
{
    Q_OBJECT

public:
    QnsbNarrativeLink(QnsbGraphicsItem* parent = 0);

    virtual ~QnsbNarrativeLink();

    QString getType() const;

    void setType(QString type);

    QnsbNarrativeChain* getChain() const;

    void setChain(QnsbNarrativeChain* chain);

    QnsbNarrativeChain* getTarget() const;

    void setTarget(QnsbNarrativeChain* target);

    QString getKey() const;

    void setKey(QString key);

    QString getVarValue() const;

    void setVarValue(QString varvalue);

    QString getVarName() const;

    void setVarName(QString varname);

    QString getOp() const;

    void setOp(QString op);

    void adjust();

protected:
    void draw(QPainter* painter);

    void delineate(QPainterPath* painter) const;

private:
    QString key;

    QString varname;

    QString op;

    QString varvalue;

    QString type;

    QnsbNarrativeChain* chain;

    QnsbNarrativeChain* target;
};

#endif // QNSBNARRATIVELINK_H
