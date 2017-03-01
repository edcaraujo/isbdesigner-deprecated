#ifndef QNSBNARRATIVEVIEW_H
#define QNSBNARRATIVEVIEW_H

#include <QDebug>

#include "ui/view/qnsbgraphicsview.h"

#include "qnsbnarrativechain.h"
#include "qnsbnarrativescene.h"
#include "qnsbnarrativelink.h"

class QnsbNarrativeView : public QnsbGraphicsView
{
    Q_OBJECT

public:
    QnsbNarrativeView(QWidget* parent = 0);

    virtual ~QnsbNarrativeView();

    void clean();

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

    void notifiesChainSelection(QnsbNarrativeChain* chain);

    void focusOnSelectedChain();

protected:
    void resizeEvent(QResizeEvent* event);

private:
    QnsbNarrativeChain* selectedChain;

    QnsbNarrativeScene* scene;

    QMap<QString, QnsbNarrativeChain*> chains;

    QMap<QString, QnsbNarrativeLink*> links;
};

#endif // QNSBNARRATIVEVIEW_H
