#ifndef QNSBENTITY_H
#define QNSBENTITY_H

#include <QMap>
#include <QString>
#include <QUuid>

#include "qnsb.h"

class QnsbEntity
{
public:
    QnsbEntity();

    virtual ~QnsbEntity();

    QString getUid() const;

    void setUid(QString uid);

    QString getProperty(QString name) const;

    QMap<QString,QString> getProperties() const;

    void addProperty(QString name, QString value);

    void removeProperty(QString name);

private:
    QString uid;

    QMap<QString,QString> properties;
};

#endif // QNSBENTITY_H
