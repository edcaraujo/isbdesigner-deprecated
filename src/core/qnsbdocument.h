#ifndef QNSBDOCUMENT_H
#define QNSBDOCUMENT_H

#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QDomDocument>
#include <QDir>

#include "qnsbnarrative.h"

class QnsbDocument : public QObject, public QnsbNarrative
{
    Q_OBJECT

public:
    QnsbDocument(QObject* parent = 0);

    virtual ~QnsbDocument();

    void save(QString location);

    void load(QString location);

    void exportToNCL(QString location);

    void clean();

    QString getExportData();

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

signals:
    void chainAdded(QString uid, QMap<QString,QString> properties);

    void chainRemoved(QString uid);

    void chainChanged(QString uid, QMap<QString,QString> properties);

    void chainSelected(QString uid);

    void dimensionAdded(QString uid, QString parent, QMap<QString,QString> properties);

    void dimensionRemoved(QString uid);

    void dimensionChanged(QString uid, QMap<QString,QString> properties);

    void dimensionSelected(QString uid);

    void linkAdded(QString uid, QString parent, QMap<QString,QString> properties);

    void linkRemoved(QString uid);

    void linkChanged(QString uid, QMap<QString,QString> properties);

    void linkSelected(QString uid);

    void panelAdded(QString uid, QString parent, QMap<QString,QString> properties);

    void panelRemoved(QString uid);

    void panelChanged(QString uid, QMap<QString,QString> properties);

    void panelSelected(QString uid);

    void objectAdded(QString uid, QString parent, QMap<QString,QString> properties);

    void objectRemoved(QString uid);

    void objectChanged(QString uid, QMap<QString,QString> properties);

    void objectSelected(QString uid);

private:
    void read();

    void readChain(QDomElement e, QnsbChain* chain);

    void readChainLink(QDomElement e);

    void readDimension(QDomElement e, QnsbDimension* dimension);

    void readPanel(QDomElement e, QnsbPanel* panel);

    void readObject(QDomElement e, QnsbObject* object);

    void readObjectReference(QDomElement e, QnsbObject* object);

    void readObjectProperty(QDomElement e, QnsbObject* parent);

    void readPanelProperty(QDomElement e, QnsbPanel* parent);

    void readLinkProperty(QDomElement e, QnsbLink* parent);

    void write();

    void writeChain(QnsbChain* chain, QDomElement parent);

    void writeDimension(QnsbDimension* dimension, QDomElement parent);

    void writeLink(QnsbLink* link, QDomElement parent);

    void writePanel(QnsbPanel* panel, QDomElement parent);

    void writeObject(QnsbObject* object, QDomElement parent);

    void writeObjectReference(QnsbObject* object, QDomElement parent);

    void writeProperty(QString name, QString value, QDomElement parent);

    void writeNCL();

    void writeNCLConnectors(QDomElement parent);

    void writeNCLOnBeginStartStopSet(QDomElement parent);

    void writeNCLOnEndSetStopStart(QDomElement parent);

    void writeNCLOnBeginTestSetStopStart(QDomElement parent);

    void writeNCLOnEndTestSetStopStart(QDomElement parent);

    void writeNCLOnEndTestNSetStopStart(QDomElement parent);

    void writeNCLOnKeySelectionStartStopSet(QDomElement parent);

    void writeNCLPort(QDomElement parent);

    void writeNCLMedias(QDomElement parent);

    void writeNCLLinks(QDomElement parent);

    void writeNCLLinks(QnsbChain* chain, QDomElement parent);

    void writeNCLActionsBind(QnsbPanel* panel, QDomElement parent);

    void writeNCLRefActionsBind(QnsbPanel* panel, QDomElement parent);

    void notifiesChainAddition(QnsbChain* chain);

    void notifiesChainChange(QnsbChain* chain);

    void notifiesDimensionAddition(QnsbDimension* dimension);

    void notifiesLinkAddition(QnsbLink* link);

    void notifiesPanelAddition(QnsbPanel* panel);

    void notifiesObjectAddition(QnsbObject* object);

    bool compare(QnsbObject* a, QnsbObject* b);

    QnsbObject* containsSimilar(QnsbPanel* p, QnsbObject* o);

private:
    QMap<QString, QnsbChain*> chains;

    QMap<QString, QnsbDimension*> dimensions;

    QMap<QString, QnsbLink*> links;

    QMap<QString, QnsbPanel*> panels;

    QMap<QString, QnsbObject*> objects;

    QMap<QString, QnsbObject*> objectsInstance;

    QDomDocument* domdoc;

    QDir savedir;

    QnsbPanel* xauxpanel_last;

    QnsbChain* rhome;

    QMap<QString,QString> wnlinkaux;

    QMap<QString,QString> rchainaux;

    QMap<QString,QString> robjectaux;

    QMap<QString, QnsbObject*> robjectaux_last;

    QMap<QString, QnsbObject*> robjectaux_instance;
};

#endif // QNSBDOCUMENT_H
