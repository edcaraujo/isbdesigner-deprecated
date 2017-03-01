#include "qnsbentity.h"

QnsbEntity::QnsbEntity()
{
    setUid(QUuid::createUuid().toString());
}

QnsbEntity::~QnsbEntity()
{

}

QString QnsbEntity::getUid() const
{
    return uid;
}

void QnsbEntity::setUid(QString uid)
{
    this->uid = uid;
}

QMap<QString,QString> QnsbEntity::getProperties() const
{
    return properties;
}

QString QnsbEntity::getProperty(QString name) const
{
    return properties.value(name);
}

void QnsbEntity::addProperty(QString name, QString value)
{
    if (name != ""){
        properties[name] = value;
    }
}

void QnsbEntity::removeProperty(QString name)
{
    if (name != ""){
        properties.remove(name);
    }
}
