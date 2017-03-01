#ifndef QNSBNARRATIVE_H
#define QNSBNARRATIVE_H

#include <QVector>
#include <QString>

#include "qnsbentity.h"
#include "qnsbchain.h"
#include "qnsbobject.h"

class QnsbNarrative : public QnsbEntity
{
public:
    QnsbNarrative();

    virtual ~QnsbNarrative();

    QVector<QnsbChain*> getChains() const;

    void addChain(QnsbChain* chain);

    void removeChain(QnsbChain* chain);

private:
    QVector<QnsbChain*> chains;
};

#endif // QNSBNARRATIVE_H
