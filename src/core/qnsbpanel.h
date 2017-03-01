#ifndef QNSBPANEL_H
#define QNSBPANEL_H

#include <QList>
#include <QVector>

#include "qnsbentity.h"
#include "qnsbdimension.h"
#include "qnsbobject.h"

class QnsbDimension;
class QnsbPanel;
class QnsbObject;

class QnsbPanel : public QnsbEntity
{
public:
    QnsbPanel();

    virtual ~QnsbPanel();

    QString getBegin() const;

    void setBegin(QString begin);

    QString getEnd() const;

    void setEnd(QString end);

    QString getNotes() const;

    void setNotes(QString notes);

    QnsbDimension* getDimension() const;

    void setDimension(QnsbDimension* dimension);

    QVector<QnsbObject*> getObjects() const;

    void addObject(QnsbObject* object);

    void removeObject(QnsbObject* object);

private:
    QString begin;

    QString end;

    QString notes;

    QnsbDimension* dimension;

    QVector<QnsbObject*> objects;
};

#endif // QNSBPANEL_H
