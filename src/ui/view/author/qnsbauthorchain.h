#ifndef QNSBAUTHORCHAIN_H
#define QNSBAUTHORCHAIN_H

#include <QDebug>

#include "ui/view/qnsbgraphicschain.h"

#include "qnsbauthordimension.h"
#include "qnsbauthorlink.h"
#include "qnsbauthorobject.h"
#include "qnsbauthorpanel.h"

class QnsbAuthorDimension;
class QnsbAuthorLink;
class QnsbAuthorObject;
class QnsbAuthorPanel;


class QnsbAuthorChain : public QnsbGraphicsChain
{
    Q_OBJECT

public:
    QnsbAuthorChain(QObject* parent);

    ~QnsbAuthorChain();

    QString getId() const;

    void setId(QString id);

    QString getType() const;

    void setType(QString type);

    QnsbAuthorChain* getPrevious();

    void setPrevious(QnsbAuthorChain* previous);

    QnsbAuthorChain* getMatrix();

    void setMatrix(QnsbAuthorChain* matrix);

    QnsbAuthorDimension* getInterface();

    void setInterface(QnsbAuthorDimension* interface);

    QVector<QnsbAuthorDimension*> getDimensions() const;

    void addDimension(QnsbAuthorDimension* dimension);

    void removeDimension(QnsbAuthorDimension* dimension);

    QVector<QnsbAuthorLink*> getLinks() const;

    void addLink(QnsbAuthorLink* link);

    void removeLink(QnsbAuthorLink* link);

    void adjust();

signals:
    void chainSelected(QnsbAuthorChain* chain);

    void linkSelected(QnsbAuthorLink* link);

    void linkChanged(QnsbAuthorLink* link);

    void panelChanged(QnsbAuthorPanel* panel);

    void panelSelected(QnsbAuthorPanel* panel);

    void objectAdded(QnsbAuthorObject* object);

    void objectChanged(QnsbAuthorObject* object);

    void objectSelected(QnsbAuthorObject* object);

private:
    QString id;

    QString type;

    QnsbAuthorChain* matrix;

    QnsbAuthorChain* previous;

    QnsbAuthorDimension* interface;

    QVector<QnsbAuthorDimension*> dimensions;

    QVector<QnsbAuthorLink*> links;
};

#endif // QNSBAUTHORCHAIN_H
