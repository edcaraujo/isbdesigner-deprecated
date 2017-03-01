#ifndef QNSBCHAIN_H
#define QNSBCHAIN_H

#include <QVector>
#include <QString>

#include "qnsbentity.h"
#include "qnsbdimension.h"
#include "qnsblink.h"

class QnsbDimension;
class QnsbLink;

class QnsbChain : public QnsbEntity
{
public:
    QnsbChain();

    virtual ~QnsbChain();

    QString getId() const;

    void setId(QString id);

    QString getInterface() const;

    void setInterface(QString interface);

    QnsbChain* getMatrix();

    void setMatrix(QnsbChain* matrix);


    QString getsMatrix();

    void setsMatrix(QString smatrix);

    QString getType() const;

    void setType(QString type);

    QVector<QnsbDimension*> getDimensions() const;

    void addDimension(QnsbDimension* dimension);

    void removeDimension(QnsbDimension* dimension);

    QVector<QnsbLink*> getLinks() const;

    void addLink(QnsbLink* link);

    void removeLink(QnsbLink* link);

private:
    QString id;

    QString type;

    QString interface;

    QString smatrix;

    QnsbChain* matrix;

    QVector<QnsbDimension*> dimensions;

    QVector<QnsbLink*> links;
};

#endif // QNSBCHAIN_H
