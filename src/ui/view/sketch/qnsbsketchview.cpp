#include "qnsbsketchview.h"

#include <QGraphicsScene>

QnsbSketchView::QnsbSketchView(QWidget* parent)
    : QnsbGraphicsView(parent)
{
    setImage(":bg/sketch/view");

    selectedPanel = NULL;

    selectedObject = NULL;

    selectedLink = NULL;

    nchain = 0;

    nobg = 0;
}

QnsbSketchView::~QnsbSketchView()
{

}

void QnsbSketchView::clean()
{
    // qDebug() << "QnsbSketchView::clean()";

    // TODO: QnsbSketchView::clean()
}

QMap<QString, QnsbSketchChain*> QnsbSketchView::getChains()
{
    return chains;
}

void QnsbSketchView::addChain(QString uid, QMap<QString,QString> properties)
{
    if (!chains.contains(uid)){
        QnsbSketchChain* chain = new QnsbSketchChain(this);
        chain->setView(this);
        chain->setUid(uid);
        chain->setTitle(properties["id"]);
        chain->setType(properties["type"]);
        chain->setSInterface(properties["interface"]);

        if (chains.contains(properties["matrix"])){
            chain->setMatrix(chains[properties["matrix"]]);
        }

        nchain++;

        connect(chain,SIGNAL(panelAdded(QnsbSketchPanel*)),
                SLOT(notifiesPanelAddtion(QnsbSketchPanel*)));

        connect(chain,SIGNAL(panelChanged(QnsbSketchPanel*)),
                SLOT(notifiesPanelChange(QnsbSketchPanel*)));

        connect(chain, SIGNAL(panelSelected(QnsbSketchPanel*)),
                SLOT(notifiesPanelSelection(QnsbSketchPanel*)));

        connect(chain, SIGNAL(chainAdded(QnsbSketchChain*)),
                SLOT(notifiesChainAddtion(QnsbSketchChain*)));

        connect(chain, SIGNAL(chainChange(QnsbSketchChain*)),
                SLOT(notifiesChainChange(QnsbSketchChain*)));

        connect(chain, SIGNAL(chainSelected(QnsbSketchChain*)),
                SLOT(notifiesChainSelection(QnsbSketchChain*)));

        connect(chain, SIGNAL(dimensionAdded(QnsbSketchDimension*)),
                SLOT(notifiesDimensionAddtion(QnsbSketchDimension*)));

        connect(chain, SIGNAL(linkSelected(QnsbSketchLink*)),
                SLOT(notifiesLinkSelection(QnsbSketchLink*)));

        connect(chain, SIGNAL(linkAdded(QnsbSketchLink*)),
                SLOT(notifiesLinkAddtion(QnsbSketchLink*)));

        connect(chain, SIGNAL(objectAdded(QnsbSketchObject*)),
                SLOT(notifiesObjectAddition(QnsbSketchObject*)));

        connect(chain, SIGNAL(objectRemoved(QnsbSketchObject*)),
                SLOT(notifiesObjectRemove(QnsbSketchObject*)));

        connect(chain, SIGNAL(objectChanged(QnsbSketchObject*)),
                SLOT(notifiesObjectChange(QnsbSketchObject*)));

        connect(chain, SIGNAL(objectSelected(QnsbSketchObject*)),
                SLOT(notifiesObjectSelection(QnsbSketchObject*)));

        // TODO: Set properties.

        chains[uid] = chain;
    }
}

void QnsbSketchView::removeChain(QString uid)
{
    if (chains.contains(uid)){
        chains.remove(uid);
    }
}

void QnsbSketchView::changeChain(QString uid, QMap<QString,QString> properties)
{
    // TODO: Set properties.

    if (chains.contains(uid)){
        QnsbSketchChain* chain = chains[uid];

        if (chains.contains(properties["matrix"])){
            chain->setMatrix(chains[properties["matrix"]]);
        }
    }
}

void QnsbSketchView::selectChain(QString uid)
{
    if (chains.contains(uid)){
        QnsbSketchChain* chain = chains[uid];

        if (chain->getType() != "referencial"){
            setScene(chain);
        }else{
            setScene(chain->getMatrix());
        }

        if (selectedPanel != NULL){
            selectedPanel->setSelected(false);
            selectedPanel = NULL;
        }

        if (selectedObject != NULL){
            selectedObject->setSelected(false);
            selectedObject = NULL;
        }

        if (selectedLink != NULL){
            selectedLink->setSelected(false);
            selectedLink->update();
            selectedLink = NULL;
        }

        if (chain->getType() != "referencial"){
            centerOn(0,chain->getHeight()/2);
        }else{
            centerOn(0,chain->getMatrix()->getHeight()/2);
        }
    }
}

void QnsbSketchView::addDimension(QString uid, QString parent, QMap<QString,QString> properties)
{
    // qDebug() << "QnsbSketchView::addDimension()";

    if (chains.contains(parent)){
        if (!dimensions.contains(uid)){
            QnsbSketchChain* chain = chains.value(parent);

            QnsbSketchDimension* dimension = new QnsbSketchDimension();
            dimension->setChain(chain);
            dimension->setUid(uid);
            dimension->adjust();

            chain->addDimension(dimension);

            dimensions[uid] = dimension;
        }
    }
}

void QnsbSketchView::removeDimension(QString uid)
{
    // qDebug() << "QnsbSketchView::removeDimension()";
}

void QnsbSketchView::changeDimension(QString uid, QMap<QString,QString> properties)
{
    // qDebug() << "QnsbSketchView::changeDimension()";
}

void QnsbSketchView::selectDimension(QString uid)
{
    // qDebug() << "QnsbSketchView::selectDimension()";
}

void QnsbSketchView::addLink(QString uid, QString parent, QMap<QString,QString> properties)
{
    if (chains.contains(parent) && chains.contains(properties["targetUID"])){
        if (!links.contains(uid)){

            QnsbSketchChain* chain = chains.value(parent);
            QnsbSketchChain* target = chains.value(properties["targetUID"]);

            target->setPrevious(chain);

            QnsbSketchLink* link = new QnsbSketchLink();
            link->setChain(chain);
            link->setUid(uid);
            link->setType(properties["type"]);
            link->setTarget(target);
            link->setKey(properties["key"]);
            link->setVarName(properties["varname"]);
            link->setOp(properties["op"]);
            link->setVarValue(properties["varvalue"]);

            if (objects.contains(properties["triggerUID"])){
                link->setTrigger(objects[properties["triggerUID"]]);
            }

            link->adjust();

            chain->addLink(link);

            links[uid] = link;
        }
    }
}

void QnsbSketchView::removeLink(QString uid)
{
    // qDebug() << "QnsbSketchView::removeLink()";
}

void QnsbSketchView::changeLink(QString uid, QMap<QString,QString> properties)
{
    // qDebug() << "QnsbSketchView::changeLink()";

    if (links.contains(uid) && chains.contains(properties["targetUID"])){
        QnsbSketchLink* link = links[uid];

        link->setType(properties["type"]);
        link->setKey(properties["key"]);

        link->setVarName(properties["varname"]);
        link->setOp(properties["op"]);
        link->setVarValue(properties["varvalue"]);

        link->setTarget(chains[properties["targetUID"]]);

        if (objects.contains(properties["triggerUID"])){
            link->setTrigger(objects[properties["triggerUID"]]);
        }
    }
}

void QnsbSketchView::selectLink(QString uid)
{
    // qDebug() << "QnsbSketchView::selectLink()";

    if (links.contains(uid)){
        if (selectedPanel != NULL){
            selectedPanel->setSelected(false);
            selectedPanel = NULL;
        }

        if (selectedObject != NULL){
            selectedObject->setSelected(false);
            selectedObject = NULL;
        }

        if (selectedLink != NULL){
            selectedLink->setSelected(false);
            selectedLink = NULL;
        }

        links[uid]->setSelected(true);

        selectedLink =  links[uid];
    }
}

void QnsbSketchView::addPanel(QString uid, QString parent, QMap<QString,QString> properties)
{
    // qDebug() << "QnsbSketchView::addPanel()";

    if (dimensions.contains(parent)){
        if (!panels.contains(uid)){
            QnsbSketchDimension* dimension = dimensions.value(parent);

            QnsbSketchPanel* panel = new QnsbSketchPanel(dimension);
            panel->setDimension(dimension);
            panel->setUid(uid);

            if (properties["notes"] != ""){
                panel->setNotes(properties["notes"]);
            }

            panel->setTBegin(properties["begin"]);
            panel->setTEnd(properties["end"]);

            dimension->addPanel(panel);

            panels[uid] = panel;
        }
    }
}

void QnsbSketchView::removePanel(QString uid)
{
    // qDebug() << "QnsbSketchView::removePanel()";
}

void QnsbSketchView::changePanel(QString uid, QMap<QString,QString> properties)
{
    // qDebug() << "QnsbSketchView::changePanel()";

    if (panels.contains(uid)){
        QnsbSketchPanel* panel =  panels[uid];

        panel->setTBegin(properties["begin"]);
        panel->setTEnd(properties["end"]);
        panel->setNotes(properties["notes"]);
    }
}

void QnsbSketchView::selectPanel(QString uid)
{
    // qDebug() << "QnsbSketchView::selectPanel()";

    if (panels.contains(uid)){
        if (selectedPanel != NULL){
            selectedPanel->setSelected(false);
            selectedPanel = NULL;
        }

        if (selectedObject != NULL){
            selectedObject->setSelected(false);
            selectedObject = NULL;
        }

        if (selectedLink != NULL){
            selectedLink->setSelected(false);
            selectedLink->update();
            selectedLink = NULL;
        }

        panels[uid]->setSelected(true);

        selectedPanel =  panels[uid];
    }
}

void QnsbSketchView::addObject(QString uid, QString parent, QMap<QString,QString> properties)
{
    if (!objects.contains(uid) && panels.contains(parent)){
         qDebug() << "QnsbSketchView::addObject()" << "sketch" << ":" << properties["sketch"];

        QnsbSketchPanel* panel = panels[parent];

        QnsbSketchObject* object = new QnsbSketchObject();
        object->setUid(uid);
        object->setPanel(panel);
        object->setId(properties["id"]);
        object->setType(properties["type"]);
        object->setInstanceID(properties["instance"]);
        object->setStatusID(properties["status"]);
        object->setSketch(properties["sketch"]);
        object->setPreview(properties["preview"]);
        object->setSrc(properties["src"]);
        object->setVarName(properties["varname"]);
        object->setVarValue(properties["varvalue"]);

        QString attribute;

        attribute = properties["top"]; attribute.remove(attribute.length()-1,1);
        object->setTop(attribute.toDouble()/100*256);

        attribute = properties["left"]; attribute.remove(attribute.length()-1,1);
        object->setLeft(attribute.toDouble()/100*panel->getWidth());

        attribute = properties["width"]; attribute.remove(attribute.length()-1,1);
        object->setWidth(attribute.toDouble()/100*panel->getWidth());

        attribute = properties["height"]; attribute.remove(attribute.length()-1,1);
        object->setHeight(attribute.toDouble()/100*256);

        panel->addObject(object);

        objects[object->getUid()] = object;

        if (!objectsInstance.contains(object->getInstanceID())){
            objectsInstance[object->getInstanceID()] = object;
            nobg++;
        }
    }
}

void QnsbSketchView::removeObject(QString uid)
{
    // qDebug() << "QnsbSketchView::removeObject()";
}

void QnsbSketchView::changeObject(QString uid, QMap<QString,QString> properties)
{
    // qDebug() << "QnsbSketchView::changeObject()";

    if (objects.contains(uid) && objects[uid]->getStatusID() != properties["status"]){
        QnsbSketchObject* object = objects[uid];

        object->setId(properties["id"]);
        object->setType(properties["type"]);
        object->setStatusID(properties["status"]);
        object->setSrc(properties["src"]);
        object->setSketch(properties["sketch"]);
        object->setPreview(properties["preview"]);
        object->setVarName(properties["varname"]);
        object->setVarValue(properties["varvalue"]);

        QString attribute;

        attribute = properties["top"]; attribute.remove(attribute.length()-1,1);
        object->setTop(attribute.toDouble()/100*256);

        attribute = properties["left"]; attribute.remove(attribute.length()-1,1);
        object->setLeft(attribute.toDouble()/100*object->getPanel()->getWidth());

        attribute = properties["width"]; attribute.remove(attribute.length()-1,1);
        object->setWidth(attribute.toDouble()/100*object->getPanel()->getWidth());

        attribute = properties["height"]; attribute.remove(attribute.length()-1,1);
        object->setHeight(attribute.toDouble()/100*256);
    }
}

void QnsbSketchView::selectObject(QString uid)
{
    // qDebug() << "QnsbSketchView::selectObject()";

    if (objects.contains(uid)){
        if (selectedObject != NULL){
            selectedObject->setSelected(false);
        }

        if (selectedLink != NULL){
            selectedLink->setSelected(false);
            selectedLink->update();
            selectedLink = NULL;
        }

        objects[uid]->setSelected(true);

        selectedObject = objects[uid];
    }
}

void QnsbSketchView::notifiesChainAddtion(QnsbSketchChain* chain)
{
    chain->setView(this);
    chain->setTitle("seq"+QString::number(nchain++));

    connect(chain,SIGNAL(panelAdded(QnsbSketchPanel*)),
            SLOT(notifiesPanelAddtion(QnsbSketchPanel*)));

    connect(chain,SIGNAL(panelChanged(QnsbSketchPanel*)),
            SLOT(notifiesPanelChange(QnsbSketchPanel*)));

    connect(chain, SIGNAL(chainAdded(QnsbSketchChain*)),
            SLOT(notifiesChainAddtion(QnsbSketchChain*)));

    connect(chain, SIGNAL(chainChange(QnsbSketchChain*)),
            SLOT(notifiesChainChange(QnsbSketchChain*)));

    connect(chain, SIGNAL(chainSelected(QnsbSketchChain*)),
            SLOT(notifiesChainSelection(QnsbSketchChain*)));

    connect(chain, SIGNAL(dimensionAdded(QnsbSketchDimension*)),
            SLOT(notifiesDimensionAddtion(QnsbSketchDimension*)));

    connect(chain, SIGNAL(linkAdded(QnsbSketchLink*)),
            SLOT(notifiesLinkAddtion(QnsbSketchLink*)));

    connect(chain, SIGNAL(linkSelected(QnsbSketchLink*)),
            SLOT(notifiesLinkSelection(QnsbSketchLink*)));

    connect(chain, SIGNAL(panelSelected(QnsbSketchPanel*)),
            SLOT(notifiesPanelSelection(QnsbSketchPanel*)));

    connect(chain, SIGNAL(objectAdded(QnsbSketchObject*)),
            SLOT(notifiesObjectAddition(QnsbSketchObject*)));

    connect(chain, SIGNAL(objectChanged(QnsbSketchObject*)),
            SLOT(notifiesObjectChange(QnsbSketchObject*)));

    connect(chain, SIGNAL(objectRemoved(QnsbSketchObject*)),
            SLOT(notifiesObjectRemove(QnsbSketchObject*)));

    connect(chain, SIGNAL(objectSelected(QnsbSketchObject*)),
            SLOT(notifiesObjectSelection(QnsbSketchObject*)));

    chains[chain->getUid()] = chain;

    QMap<QString,QString> properties;

    properties["id"] = chain->getTitle();
    properties["type"] = chain->getType();

    if (chain->getMatrix() != NULL){
        properties["matrix"] = chain->getMatrix()->getUid();
    }

    if (chain->getInterface() != NULL){
        properties["interface"] = chain->getInterface()->getUid();
    }else{
        properties["interface"] = "";
    }

    emit chainAdded(chain->getUid(), properties);
}

void QnsbSketchView::notifiesChainChange(QnsbSketchChain* chain)
{
    QMap<QString,QString> properties;

    properties["id"] = chain->getTitle();
    properties["type"] = chain->getType();
    properties["interface"] = chain->getInterface()->getName();

    emit chainChanged(chain->getUid(), properties);
}

void QnsbSketchView::notifiesChainSelection(QnsbSketchChain* chain)
{
    // qDebug() << "QnsbSketchView::notifiesChainSelection()";

    if (chains.contains(chain->getUid())){
        setScene(chain);

        if (selectedPanel != NULL){
            selectedPanel->setSelected(false);
            selectedPanel = NULL;
        }

        if (selectedObject != NULL){
            selectedObject->setSelected(false);
            selectedObject = NULL;
        }

        if (selectedLink != NULL){
            selectedLink->setSelected(false);
            selectedLink->update();
            selectedLink = NULL;
        }

        emit chainSelected(chain->getUid());
    }
}

void QnsbSketchView::notifiesDimensionAddtion(QnsbSketchDimension* dimension)
{
    dimensions[dimension->getUid()] = dimension;

    QMap<QString,QString> properties;

    if (dimension->getChain()->getDimensions().size() == 1){
        dimension->setName("main");
    }else{
        dimension->setName("sec"+QString::number(dimension->getChain()->getDimensions().size()));
    }

    properties["name"] = dimension->getName();

    emit dimensionAdded(dimension->getUid(),
                        dimension->getChain()->getUid(),
                        properties);
}

void QnsbSketchView::notifiesLinkAddtion(QnsbSketchLink* link)
{
    links[link->getUid()] = link;

    QMap<QString,QString> properties;

    properties["target"] = link->getTarget()->getTitle();
    properties["targetUID"] = link->getTarget()->getUid();
    properties["type"] = link->getType();

    emit linkAdded(link->getUid(), link->getChain()->getUid(), properties);
}

void QnsbSketchView::notifiesLinkSelection(QnsbSketchLink* link)
{
    if (selectedLink != link){
        if (selectedPanel != NULL){
            selectedPanel->setSelected(false);
            selectedPanel = NULL;
        }

        if (selectedObject != NULL){
            selectedObject->setSelected(false);
            selectedObject = NULL;
        }

        if (selectedLink != NULL){
            selectedLink->setSelected(false);
        }

        selectedLink =  link;

        link->getChain()->update();

        emit linkSelected(link->getUid());
    }
}

void QnsbSketchView::notifiesPanelAddtion(QnsbSketchPanel* panel)
{
    panels[panel->getUid()] = panel;

    emit panelAdded(panel->getUid(), panel->getDimension()->getUid(), QMap<QString,QString>());
}

void QnsbSketchView::notifiesPanelChange(QnsbSketchPanel* panel)
{
    QMap<QString,QString> properties;

    properties["begin"] = panel->getTBegin();
    properties["end"] = panel->getTEnd();
    properties["notes"] = panel->getNotes();

    emit panelChanged(panel->getUid(),properties);
}

void QnsbSketchView::notifiesPanelSelection(QnsbSketchPanel* panel)
{
    if (panel != selectedPanel){
        if (selectedPanel != NULL){
            selectedPanel->setSelected(false);
        }

        selectedPanel =  panel;

        panel->getDimension()->update();

        emit panelSelected(panel->getUid());
    }

    if (selectedObject != NULL){
        selectedObject->setSelected(false);

        selectedObject = NULL;
    }

    if (selectedLink != NULL){
        selectedLink->setSelected(false);
        selectedLink->update();
        selectedLink = NULL;
    }
}

void QnsbSketchView::notifiesObjectAddition(QnsbSketchObject* object)
{
    objects[object->getUid()] = object;

    if (!objectsInstance.contains(object->getInstanceID())){
        object->setId("object"+QString::number(nobg++));

        objectsInstance[object->getUid()] = object;
    }else{
        object->setId(objectsInstance[object->getInstanceID()]->getId());
    }

    QMap<QString,QString> properties;

    properties["top"] = QString::number(100*object->getTop()/256, 'f', 2) + "%";
    properties["left"] = QString::number(100*object->getLeft()/object->getPanel()->getWidth(), 'f', 2) + "%";
    properties["width"] = QString::number(100*object->getWidth()/object->getPanel()->getWidth(), 'f', 2) + "%";
    properties["height"] = QString::number(100*object->getHeight()/256, 'f', 2) + "%";

    properties["id"] = object->getId();
    properties["type"] = object->getType();
    properties["instance"] = object->getInstanceID();
    properties["status"] = object->getStatusID();
    properties["sketch"] = object->getSketch();
    properties["preview"] = object->getPreview();
    properties["src"] = object->getSrc();

    emit objectAdded(object->getUid(), object->getPanel()->getUid(),properties);
}

void QnsbSketchView::notifiesObjectRemove(QnsbSketchObject* object)
{
    if (object != NULL){
        if (objects.contains(object->getUid())){
            if (objectsInstance.contains(object->getUid())){
                objectsInstance.remove(object->getUid());
            }

            objects.remove(object->getUid());

            object->getPanel()->removeObject(object);
            object->getPanel()->update();


            emit objectRemoved(object->getUid());
        }
    }
}

void QnsbSketchView::notifiesObjectChange(QnsbSketchObject* object)
{
    if (objects.contains(object->getUid())){
        QMap<QString,QString> properties;

        properties["top"] = QString::number(100*object->getTop()/256, 'f', 2) + "%";
        properties["left"] = QString::number(100*object->getLeft()/object->getPanel()->getWidth(), 'f', 2) + "%";
        properties["width"] = QString::number(100*object->getWidth()/object->getPanel()->getWidth(), 'f', 2) + "%";
        properties["height"] = QString::number(100*object->getHeight()/256, 'f', 2) + "%";

        properties["id"] = object->getId();
        properties["type"] = object->getType();
        properties["instance"] = object->getInstanceID();
        properties["status"] = object->getStatusID();
        properties["src"] = object->getSrc();
        properties["sketch"] = object->getSketch();
        properties["preview"] = object->getPreview();
        properties["varname"] = object->getVarName();
        properties["varvalue"] = object->getVarValue();

        emit objectChanged(object->getUid(), properties);

        if (object->getPanel()->getNext() != NULL){
            adjustNextPanelObject(object, object->getPanel()->getNext());

        }else{
            foreach(QnsbSketchLink* link, object->getPanel()->getDimension()->getChain()->getLinks()){
                foreach(QnsbSketchDimension* dim, link->getTarget()->getDimensions()){

                    if (object->getPanel()->getDimension()->getName() == dim->getName()){
                        adjustNextPanelObject(object, dim->getPanels().first());
                    }
                }
            }
        }

        object->getPanel()->getDimension()->update();
    }
}

void QnsbSketchView::adjustNextPanelObject(QnsbSketchObject* reference, QnsbSketchPanel* panel)
{
    bool alreadyChange = true;

    foreach(QnsbSketchObject* object, panel->getObjects()){
        if (object->getStatusID() == reference->getLastStatusID()){
            object->setTop(reference->getTop());
            object->setLeft(reference->getLeft());
            object->setWidth(reference->getWidth());
            object->setHeight(reference->getHeight());

            object->setType(reference->getType());
            object->setSrc(reference->getSrc());


            if (reference->getType() != "video"){
                object->setSketch(reference->getSketch());
                object->setPreview(reference->getPreview());
            }

            object->setStatusID(reference->getStatusID());
            object->setVarName(reference->getVarName());
            object->setVarValue(reference->getVarValue());

            alreadyChange = false;

            QMap<QString,QString> properties;

            properties["top"] = QString::number(100*object->getTop()/256, 'f', 2) + "%";
            properties["left"] = QString::number(100*object->getLeft()/object->getPanel()->getWidth(), 'f', 2) + "%";
            properties["width"] = QString::number(100*object->getWidth()/object->getPanel()->getWidth(), 'f', 2) + "%";
            properties["height"] = QString::number(100*object->getHeight()/256, 'f', 2) + "%";

            properties["id"] = object->getId();
            properties["type"] = object->getType();
            properties["instance"] = object->getInstanceID();
            properties["status"] = object->getStatusID();
            properties["src"] = object->getSrc();
            properties["preview"] = object->getPreview();
            properties["sketch"] = object->getSketch();
            properties["varname"] = object->getVarName();
            properties["varvalue"] = object->getVarValue();

            emit objectChanged(object->getUid(), properties);
        }
    }

    if (!alreadyChange){
        if (panel->getNext() != NULL){
            adjustNextPanelObject(reference, panel->getNext());

        }else{
            foreach(QnsbSketchLink* link, panel->getDimension()->getChain()->getLinks()){
                foreach(QnsbSketchDimension* dim, link->getTarget()->getDimensions()){
                    if (reference->getPanel()->getDimension()->getName() == dim->getName()){
                        adjustNextPanelObject(reference, dim->getPanels().first());
                    }
                }
            }
        }
    }
}

void QnsbSketchView::notifiesObjectSelection(QnsbSketchObject* object)
{
    // qDebug() << "QnsbSketchView::notifiesObjectSelection()";

    if (selectedObject != object){
        object->getPanel()->setSelected(true);
        object->getPanel()->getDimension()->update();

        notifiesPanelSelection(object->getPanel());

        if (selectedObject != NULL){
            selectedObject->setSelected(false);
        }

        selectedObject =  object;

        if (selectedLink != NULL){
            selectedLink->setSelected(false);
            selectedLink->update();
            selectedLink = NULL;
        }

        emit objectSelected(object->getUid());
    }
}

void QnsbSketchView::resizeEvent(QResizeEvent* event)
{
    QnsbGraphicsView::resizeEvent(event);

    qreal width = event->size().width();
    qreal height = event->size().height();

    foreach (QnsbGraphicsChain* chain, chains.values()) {
        chain->setMinimumWidth(width);
        chain->setMinimumHeight(height);

        chain->setWidth(width+18);
        chain->setHeight(height+18);

        chain->adjust();
    }
}
