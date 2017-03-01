#ifndef QNSBOBJECT_H
#define QNSBOBJECT_H

#include "qnsbentity.h"
#include "qnsbpanel.h"

class QnsbPanel;

class QnsbObject : public QnsbEntity
{
public:
    QnsbObject();

    virtual ~QnsbObject();

    QString getId() const;

    void setId(QString id);

    QnsbPanel* getPanel() const;

    void setPanel(QnsbPanel* panel);

    QString getInstanceId() const;

    void setInstanceId(QString instanceId);

    QString getStatusId() const;

    void setStatusId(QString statusId);

    QString getRefer() const;

    void setRefer(QString refer);

    QString getSrc() const;

    void setSrc(QString src);

    QString getSketch() const;

    void setSketch(QString sketch);

    QString getPreview() const;

    void setPreview(QString preview);

    QString getType() const;

    void setType(QString type);

    QString getVarValue() const;

    void setVarValue(QString varvalue);

    QString getVarName() const;

    void setVarName(QString varname);

private:
    QString id;

    QString refer;

    QString src;

    QString sketch;

    QString preview;

    QString type;

    QString instanceId;

    QString statusId;

    QnsbPanel* panel;

    QString varname;

    QString varvalue;
};

#endif // QNSBOBJECT_H
