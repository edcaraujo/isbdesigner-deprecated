#ifndef QNSBSKETCHCHAIN_H
#define QNSBSKETCHCHAIN_H

#include <QDebug>
#include <QVector>
#include <QGraphicsTextItem>

#include "ui/view/qnsbgraphicschain.h"

#include "qnsbsketchdimension.h"
#include "qnsbsketchpanel.h"
#include "qnsbsketchlink.h"
#include "qnsbsketchobject.h"

class QnsbSketchDimension;
class QnsbSketchPanel;
class QnsbSketchLink;
class QnsbSketchObject;

class QnsbSketchChain : public QnsbGraphicsChain
{
    Q_OBJECT

public:
    QnsbSketchChain(QObject* parent = 0);

    virtual ~QnsbSketchChain();

    int getnSequencialLink();

    int getnDistributiveLink();

    int getnReferencialLink();

    QString getTitle() const;

    void setTitle(QString  title);

    QString getType() const;

    void setType(QString type);

    QString getSInterface() const;

    void setSInterface(QString  sinterface);

    QnsbSketchChain* getPrevious();

    void setPrevious(QnsbSketchChain* previous);

    QnsbSketchChain* getMatrix();

    void setMatrix(QnsbSketchChain* matrix);

    QnsbSketchDimension* getInterface();

    void setInterface(QnsbSketchDimension* interface);

    QVector<QnsbSketchDimension*> getDimensions() const;

    void addDimension(QnsbSketchDimension* dimension);

    void removeDimension(QnsbSketchDimension* dimension);

    QVector<QnsbSketchLink*> getLinks() const;

    void addLink(QnsbSketchLink* link);

    void removeLink(QnsbSketchLink* link);

    virtual void adjust();

signals:
    void panelAdded(QnsbSketchPanel* panel);

    void panelChanged(QnsbSketchPanel* panel);

    void chainAdded(QnsbSketchChain* chain);

    void chainChange(QnsbSketchChain* chain);

    void objectRemoved(QnsbSketchObject* object);

    void chainSelected(QnsbSketchChain* chain);

    void dimensionAdded(QnsbSketchDimension* dimension);

    void linkAdded(QnsbSketchLink* link);

    void linkSelected(QnsbSketchLink* link);

    void panelSelected(QnsbSketchPanel* panel);

    void objectAdded(QnsbSketchObject* object);

    void objectChanged(QnsbSketchObject* object);

    void objectSelected(QnsbSketchObject* object);

private:
    QString title;

    QString type;

    QString sinterface;

    int nreflink;

    int ndistlink;

    int nseqlink;

    QnsbSketchDimension* interface;

    QnsbSketchChain* matrix;

    QnsbSketchChain* previous;

    QVector<QnsbSketchDimension*> dimensions;

    QVector<QnsbSketchLink*> links;
};

#endif // QNSBSKETCHCHAIN_H
