#ifndef QNSBAUTHORVIEW_H
#define QNSBAUTHORVIEW_H

#include <QDebug>

#include "ui/view/qnsbgraphicsview.h"

#include "qnsbauthorchain.h"
#include "qnsbauthordimension.h"
#include "qnsbauthorlink.h"
#include "qnsbauthorpanel.h"
#include "qnsbauthorobject.h"

class QnsbAuthorLink;
class QnsbAuthorDimension;
class QnsbAuthorChain;
class QnsbAuthorObject;
class QnsbAuthorPanel;

class QnsbAuthorView : public QnsbGraphicsView
{
    Q_OBJECT

public:
    QnsbAuthorView(QWidget* parent = 0);

    virtual ~QnsbAuthorView();

    void clean();

    QMap<QString, QnsbAuthorChain*> getChains() const;

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

public slots:
    void notifiesChainSelection(QnsbAuthorChain* chain);

    void notifiesLinkSelection(QnsbAuthorLink* link);

    void notifiesLinkChange(QnsbAuthorLink* link);

    void notifiesPanelChange(QnsbAuthorPanel* panel);

    void notifiesPanelSelection(QnsbAuthorPanel* panel);

    void notifiesObjectAddtion(QnsbAuthorObject* object);

    void notifiesObjectChange(QnsbAuthorObject* object);

    void notifiesObjectSelection(QnsbAuthorObject* object);

protected:
    void resizeEvent(QResizeEvent* event);

private:
    void adjustNextPanelObject(QnsbAuthorObject* reference, QnsbAuthorPanel* panel);

    int nobg;

    QnsbAuthorLink* selectedLink;

    QnsbAuthorPanel* selectedPanel;

    QnsbAuthorObject* selectedObject;

    QMap<QString, QnsbAuthorChain*> chains;

    QMap<QString, QnsbAuthorDimension*> dimensions;

    QMap<QString, QnsbAuthorLink*> links;

    QMap<QString, QnsbAuthorPanel*> panels;

    QMap<QString, QnsbAuthorObject*> objects;

    QMap<QString, QnsbAuthorObject*> objectsInstance;
};

#endif // QNSBAUTHORVIEW_H
