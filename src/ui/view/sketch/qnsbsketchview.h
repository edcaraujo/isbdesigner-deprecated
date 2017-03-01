#ifndef QNSBSKETCHVIEW_H
#define QNSBSKETCHVIEW_H

#include <QDebug>

#include "ui/view/qnsbgraphicsview.h"

#include "qnsbsketchchain.h"
#include "qnsbsketchdimension.h"
#include "qnsbsketchpanel.h"
#include "qnsbsketchobject.h"

class QnsbSketchChain;
class QnsbSketchDimension;
class QnsbSketchPanel;
class QnsbSketchLink;
class QnsbSketchObject;

class QnsbSketchView : public QnsbGraphicsView
{
    Q_OBJECT

public:
    QnsbSketchView(QWidget* parent = 0);

    virtual ~QnsbSketchView();

    void clean();

    QMap<QString, QnsbSketchChain*> getChains();

public slots:
    void addChain(QString uid, QMap<QString,QString> properties);

    void removeChain(QString uid);

    void changeChain(QString uid, QMap<QString,QString> properties);

    void selectChain(QString uid);

    void addDimension(QString uid, QString parent, QMap<QString,QString> properties);

    void removeDimension(QString uid);

    void changeDimension(QString uid, QMap<QString,QString> properties);

    void selectDimension(QString uid);

    void addLink(QString uid, QString parent, QMap<QString,QString> properties);

    void removeLink(QString uid);

    void changeLink(QString uid, QMap<QString,QString> properties);

    void selectLink(QString uid);

    void addPanel(QString uid, QString parent, QMap<QString,QString> properties);

    void removePanel(QString uid);

    void changePanel(QString uid, QMap<QString,QString> properties);

    void selectPanel(QString uid);

    void addObject(QString uid, QString parent, QMap<QString,QString> properties);

    void removeObject(QString uid);

    void changeObject(QString uid, QMap<QString,QString> properties);

    void selectObject(QString uid);

    void notifiesChainAddtion(QnsbSketchChain* chain);

    void notifiesChainChange(QnsbSketchChain* chain);

    void notifiesChainSelection(QnsbSketchChain* chain);

    void notifiesDimensionAddtion(QnsbSketchDimension* dimension);

    void notifiesLinkAddtion(QnsbSketchLink* link);

    void notifiesLinkSelection(QnsbSketchLink* link);

    void notifiesPanelAddtion(QnsbSketchPanel* panel);

    void notifiesPanelChange(QnsbSketchPanel* panel);

    void notifiesPanelSelection(QnsbSketchPanel* panel);

    void notifiesObjectAddition(QnsbSketchObject* object);

    void notifiesObjectRemove(QnsbSketchObject* object);

    void notifiesObjectChange(QnsbSketchObject* object);

    void notifiesObjectSelection(QnsbSketchObject* object);

protected:
    void resizeEvent(QResizeEvent* event);

private:
    void adjustNextPanelObject(QnsbSketchObject* reference, QnsbSketchPanel* panel);

    QnsbSketchLink* selectedLink;

    QnsbSketchPanel* selectedPanel;

    QnsbSketchObject* selectedObject;

    int nchain;

    int nobg;

    QMap<QString, QnsbSketchChain*> chains;

    QMap<QString, QnsbSketchDimension*> dimensions;

    QMap<QString, QnsbSketchLink*> links;

    QMap<QString, QnsbSketchPanel*> panels;

    QMap<QString, QnsbSketchObject*> objects;

    QMap<QString, QnsbSketchObject*> objectsInstance;
};

#endif // QNSBSKETCHVIEW_H
