#ifndef QNSBDIMENSION_H
#define QNSBDIMENSION_H

#include <QList>

#include "qnsbentity.h"
#include "qnsbpanel.h"
#include "qnsbchain.h"

class QnsbChain;
class QnsbPanel;

class QnsbDimension : public QnsbEntity
{
public:
    QnsbDimension();

    virtual ~QnsbDimension();

    QString getName() const;

    void setName(QString name);

    QnsbChain* getChain() const;

    void setChain(QnsbChain* chain);

    QList<QnsbPanel*> gePanels() const;

    void addPanel(QnsbPanel* panel);

    void removePanel(QnsbPanel* panel);

private:
    QString name;

    QnsbChain* chain;

    QList<QnsbPanel*> panels;
};

#endif // QNSBDIMENSION_H
