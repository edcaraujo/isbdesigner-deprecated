#include "qnsbauthorview.h"

#include <QGraphicsScene>

QnsbAuthorView::QnsbAuthorView(QWidget* parent)
    : QnsbGraphicsView(parent)
{
    setImage(":bg/author/view");

    nobg = 0;

    selectedPanel = NULL;

    selectedObject = NULL;

    selectedLink = NULL;
}

QnsbAuthorView::~QnsbAuthorView()
{

}

void QnsbAuthorView::clean()
{
    // qDebug() << "QnsbAuthorView::clean()";
}

QMap<QString, QnsbAuthorChain*> QnsbAuthorView::getChains() const
{
    return chains;
}

void QnsbAuthorView::addChain(QString uid, QMap<QString,QString> properties)
{
//    // qDebug() << "QnsbAuthorView::addChain()";

    if (!chains.contains(uid)){
        QnsbAuthorChain* chain = new QnsbAuthorChain(this);
        chain->setUid(uid);
        chain->setView(this);

        if (properties["interface"] != ""){
            chain->setInterface(dimensions[properties["interface"]]);
        }

        if (chains.contains(properties["matrix"])){
            chain->setMatrix(chains[properties["matrix"]]);
        }

        chain->setId(properties["id"]);
        chain->setType(properties["type"]);

        connect(chain, SIGNAL(chainSelected(QnsbAuthorChain*)),
                SLOT(notifiesChainSelection(QnsbAuthorChain*)));

        connect(chain, SIGNAL(linkSelected(QnsbAuthorLink*)),
                SLOT(notifiesLinkSelection(QnsbAuthorLink*)));

        connect(chain, SIGNAL(linkChanged(QnsbAuthorLink*)),
                SLOT(notifiesLinkChange(QnsbAuthorLink*)));

        connect(chain,SIGNAL(panelChanged(QnsbAuthorPanel*)),
                SLOT(notifiesPanelChange(QnsbAuthorPanel*)));

        connect(chain, SIGNAL(panelSelected(QnsbAuthorPanel*)),
                SLOT(notifiesPanelSelection(QnsbAuthorPanel*)));

        connect(chain, SIGNAL(objectAdded(QnsbAuthorObject*)),
                SLOT(notifiesObjectAddtion(QnsbAuthorObject*)));

        connect(chain, SIGNAL(objectChanged(QnsbAuthorObject*)),
                SLOT(notifiesObjectChange(QnsbAuthorObject*)));

        connect(chain, SIGNAL(objectSelected(QnsbAuthorObject*)),
                SLOT(notifiesObjectSelection(QnsbAuthorObject*)));

        chains[uid] = chain;
    }
}

void QnsbAuthorView::removeChain(QString uid)
{
    // qDebug() << "QnsbAuthorView::removeChain()";
}

void QnsbAuthorView::changeChain(QString uid, QMap<QString,QString> properties)
{
    // qDebug() << "QnsbAuthorView::changeChain()";

    if (chains.contains(uid)){
        QnsbAuthorChain* chain = chains[uid];

        if (chains.contains(properties["matrix"])){
            chain->setMatrix(chains[properties["matrix"]]);
        }
    }
}

void QnsbAuthorView::selectChain(QString uid)
{
    // qDebug() << "QnsbAuthorView::selectChain()";

    if (chains.contains(uid)){
        QnsbAuthorChain* chain = chains[uid];

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

void QnsbAuthorView::addDimension(QString uid, QString parent, QMap<QString,QString> properties)
{
    // qDebug() << "QnsbAuthorView::addDimension()";

    if (!dimensions.contains(uid) && chains.contains(parent)){
        QnsbAuthorChain* chain = chains[parent];

        QnsbAuthorDimension* dimension = new QnsbAuthorDimension();
        dimension->setUid(uid);
        dimension->setChain(chain);

        dimension->setName(properties["name"]);

        chain->addDimension(dimension);

        dimensions[uid] = dimension;
    }
}

void QnsbAuthorView::removeDimension(QString uid)
{
    // qDebug() << "QnsbAuthorView::removeDimension()";
}

void QnsbAuthorView::changeDimension(QString uid, QMap<QString,QString> properties)
{
    // qDebug() << "QnsbAuthorView::changeDimension()";
}

void QnsbAuthorView::selectDimension(QString uid)
{
    // qDebug() << "QnsbAuthorView::selectDimension()";
}

void QnsbAuthorView::addLink(QString uid, QString parent, QMap<QString,QString> properties)
{
    // qDebug() << "QnsbAuthorView::addLink()";

    if (!links.contains(uid) && chains.contains(parent) && chains.contains(properties["targetUID"])){
        QnsbAuthorChain* chain = chains[parent];
        QnsbAuthorChain* target = chains[properties["targetUID"]];

        target->setPrevious(chain);

        QnsbAuthorLink* link = new QnsbAuthorLink();
        link->setUid(uid);
        link->setChain(chain);
        link->setTarget(target);
        link->setType(properties["type"]);
        link->setKey(properties["key"]);
        link->setVarName(properties["varname"]);

        link->setOp(properties["op"]);
        link->setVarValue(properties["varvalue"]);

        if (objects.contains(properties["triggerUID"])){
            link->setTrigger(objects[properties["triggerUID"]]);
        }

        chain->addLink(link);

        links[uid] = link;
    }
}

void QnsbAuthorView::removeLink(QString uid)
{
    // qDebug() << "QnsbAuthorView::removeLink()";
}

void QnsbAuthorView::changeLink(QString uid, QMap<QString,QString> properties)
{
    // qDebug() << "QnsbAuthorView::changeLink()";

    if (links.contains(uid) && chains.contains(properties["targetUID"])){
        QnsbAuthorLink* link = links[uid];

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

void QnsbAuthorView::selectLink(QString uid)
{
    // qDebug() << "QnsbAuthorView::selectLink()";

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
        }

        links[uid]->setSelected(true);

        selectedLink =  links[uid];
    }
}

void QnsbAuthorView::addPanel(QString uid, QString parent, QMap<QString,QString> properties)
{
    // qDebug() << "QnsbAuthorView::addPanel()";

    if (!panels.contains(uid) && dimensions.contains(parent)){
        QnsbAuthorDimension* dimension = dimensions[parent];

        QnsbAuthorPanel* panel = new QnsbAuthorPanel();
        panel->setUid(uid);
        panel->setDimension(dimension);

        QString attribute;

        attribute = properties["begin"]; attribute.remove(attribute.length()-1,1);
        panel->setBegin(attribute.toDouble());

        attribute = properties["end"]; attribute.remove(attribute.length()-1,1);
        panel->setEnd(attribute.toDouble());

        panel->setNotes(properties["notes"]);

        dimension->addPanel(panel);

        panels[uid] = panel;
    }
}

void QnsbAuthorView::removePanel(QString uid)
{
    // qDebug() << "QnsbAuthorView::removePanel()";
}

void QnsbAuthorView::changePanel(QString uid, QMap<QString,QString> properties)
{
    // qDebug() << "QnsbAuthorView::changePanel()";

    if (panels.contains(uid)){
        QnsbAuthorPanel* panel =  panels[uid];

        QString attribute;

        attribute = properties["begin"]; attribute.remove(attribute.length()-1,1);
        panel->setBegin(attribute.toDouble());

        attribute = properties["end"]; attribute.remove(attribute.length()-1,1);
        panel->setEnd(attribute.toDouble());

        panel->setNotes(properties["notes"]);
    }
}

void QnsbAuthorView::selectPanel(QString uid)
{
    // qDebug() << "QnsbAuthorView::selectPanel()";

    if (panels.contains(uid)){
        if (selectedPanel != NULL){
            selectedPanel->setSelected(false);
        }

        if (selectedObject != NULL){
            selectedObject->setSelected(false);
            selectedObject = NULL;
        }

        if (selectedLink != NULL){
            selectedLink->setSelected(false);
            selectedLink = NULL;
        }

        panels[uid]->setSelected(true);

        selectedPanel = panels[uid];
    }
}

void QnsbAuthorView::addObject(QString uid, QString parent, QMap<QString,QString> properties)
{
    // qDebug() << "QnsbAuthorView::addObject()";

    if (!objects.contains(uid) && panels.contains(parent)){
        QnsbAuthorPanel* panel = panels[parent];

        QnsbAuthorObject* object = new QnsbAuthorObject();
        object->setUid(uid);
        object->setPanel(panel);
        object->setId(properties["id"]);
        object->setType(properties["type"]);
        object->setInstanceID(properties["instance"]);
        object->setStatusID(properties["status"]);
        object->setSrc(properties["src"]);
        object->setSketch(properties["sketch"]);
        object->setPreview(properties["preview"]);
        object->setVarName(properties["varname"]);
        object->setVarValue(properties["varvalue"]);

        QString attribute;

        attribute = properties["top"]; attribute.remove(attribute.length()-1,1);
        object->setTop(attribute.toDouble()/100*256+32);

        attribute = properties["left"]; attribute.remove(attribute.length()-1,1);
        object->setLeft(attribute.toDouble()/100*panel->getWidth());

        attribute = properties["width"]; attribute.remove(attribute.length()-1,1);
        object->setWidth(attribute.toDouble()/100*panel->getWidth());

        attribute = properties["height"]; attribute.remove(attribute.length()-1,1);
        object->setHeight(attribute.toDouble()/100*256);

        panel->addObject(object);

        objects[uid] = object;

        if (!objectsInstance.contains(object->getInstanceID())){
            objectsInstance[object->getInstanceID()] = object;
            nobg++;
        }
    }
}

void QnsbAuthorView::removeObject(QString uid)
{
    // qDebug() << "QnsbAuthorView::removeObject()";

    if (objects.contains(uid)){
        if (selectedObject == objects[uid]){
            selectedObject->setSelected(false);

            selectedObject = NULL;
        }

        objects[uid]->getPanel()->removeObject(objects[uid]);

        objects.remove(uid);
    }
}

void QnsbAuthorView::changeObject(QString uid, QMap<QString,QString> properties)
{
    // qDebug() << "QnsbAuthorView::changeObject()";

    if (objects.contains(uid) && objects[uid]->getStatusID() != properties["status"]){
        QnsbAuthorObject* object = objects[uid];

        object->setId(properties["id"]);
        object->setType(properties["type"]);
        object->setInstanceID(properties["instance"]);
        object->setStatusID(properties["status"]);
        object->setSrc(properties["src"]);
        object->setSketch(properties["sketch"]);
        object->setPreview(properties["preview"]);
        object->setVarName(properties["varname"]);
        object->setVarValue(properties["varvalue"]);

        QString attribute;

        attribute = properties["top"]; attribute.remove(attribute.length()-1,1);
        object->setTop(attribute.toDouble()/100*256+32);

        attribute = properties["left"]; attribute.remove(attribute.length()-1,1);
        object->setLeft(attribute.toDouble()/100*object->getPanel()->getWidth());

        attribute = properties["width"]; attribute.remove(attribute.length()-1,1);
        object->setWidth(attribute.toDouble()/100*object->getPanel()->getWidth());

        attribute = properties["height"]; attribute.remove(attribute.length()-1,1);
        object->setHeight(attribute.toDouble()/100*256);

        object->getPanel()->update();
    }
}

void QnsbAuthorView::selectObject(QString uid)
{
    // qDebug() << "QnsbAuthorView::selectObject()";

    if (objects.contains(uid)){
        if (selectedObject != NULL){
            selectedObject->setSelected(false);
        }

        if (selectedLink != NULL){
            selectedLink->setSelected(false);

            selectedLink = NULL;
        }

        objects[uid]->setSelected(true);

        selectedObject = objects[uid];
    }
}

void QnsbAuthorView::notifiesChainSelection(QnsbAuthorChain* chain)
{
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
            selectedLink = NULL;
        }

        emit chainSelected(chain->getUid());
    }
}

void QnsbAuthorView::notifiesLinkSelection(QnsbAuthorLink* link)
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

        selectedLink = link;

        link->getChain()->update();

        emit linkSelected(link->getUid());
    }
}

void QnsbAuthorView::notifiesLinkChange(QnsbAuthorLink* link)
{
    QMap<QString,QString> properties;

    properties["target"] = link->getTarget()->getId();
    properties["targetUID"] = link->getTarget()->getUid();

    if (link->getTrigger() != NULL){
        properties["trigger"] = link->getTrigger()->getId();
        properties["triggerUID"] = link->getTrigger()->getUid();
    }

    properties["type"] = link->getType();
    properties["key"] = link->getKey();

    properties["varname"] = link->getVarName();
    properties["op"] = link->getOp();
    properties["varvalue"] = link->getVarValue();

    emit linkChanged(link->getUid(),properties);
}

void QnsbAuthorView::notifiesPanelChange(QnsbAuthorPanel* panel)
{
    QMap<QString,QString> properties;

    properties["begin"] = QString::number(panel->getBegin(),'f', 2)+"s";
    properties["end"] = QString::number(panel->getEnd(),'f', 2)+"s";
    properties["notes"] = panel->getNotes();

    emit panelChanged(panel->getUid(),properties);
}

void QnsbAuthorView::notifiesPanelSelection(QnsbAuthorPanel* panel)
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

void QnsbAuthorView::notifiesObjectAddtion(QnsbAuthorObject* object)
{
    if (!objects.contains(object->getUid())){

        if (!objectsInstance.contains(object->getInstanceID())){
            object->setId("object"+QString::number(nobg++));

            objectsInstance[object->getUid()] = object;
        }else{
            object->setId(objectsInstance[object->getInstanceID()]->getId());
        }

        QMap<QString,QString> properties;

        properties["top"] = QString::number(100*(object->getTop()-32)/256, 'f', 2) + "%";
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

        objects[object->getUid()] = object;

        emit objectAdded(object->getUid(), object->getPanel()->getUid(),properties);
    }
}

void QnsbAuthorView::notifiesObjectChange(QnsbAuthorObject* object)
{
    // qDebug() << "QnsbAuthorView::notifiesObjectChange()";

    if (objects.contains(object->getUid())){
        QMap<QString,QString> properties;

        properties["top"] = QString::number(100*(object->getTop()-32)/256, 'f', 2) + "%";
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


        if (!object->isInstanceChange()){
            if (object->getPanel()->getNext() != NULL){
                adjustNextPanelObject(object, object->getPanel()->getNext());
            }else{
                foreach(QnsbAuthorLink* link, object->getPanel()->getDimension()->getChain()->getLinks()){
                    foreach(QnsbAuthorDimension* dim, link->getTarget()->getDimensions()){
                        if (object->getPanel()->getDimension()->getName() == dim->getName()){
                            adjustNextPanelObject(object, dim->getPanels().first());
                        }
                    }
                }
            }
        }else{
            foreach(QnsbAuthorObject* obj, objects.values()){
                if (object->getInstanceID() == obj->getInstanceID()){
                    obj->setSrc(object->getSrc());

                    QMap<QString,QString> properties;

                    properties["top"] = QString::number(100*(obj->getTop()-32)/256, 'f', 2) + "%";
                    properties["left"] = QString::number(100*obj->getLeft()/object->getPanel()->getWidth(), 'f', 2) + "%";
                    properties["width"] = QString::number(100*obj->getWidth()/object->getPanel()->getWidth(), 'f', 2) + "%";
                    properties["height"] = QString::number(100*obj->getHeight()/256, 'f', 2) + "%";

                    properties["id"] = obj->getId();
                    properties["type"] = obj->getType();
                    properties["instance"] = obj->getInstanceID();
                    properties["status"] = obj->getStatusID();
                    properties["src"] = obj->getSrc();
                    properties["sketch"] = object->getSketch();
                    properties["preview"] = object->getPreview();
                    properties["varname"] = obj->getVarName();
                    properties["varvalue"] = obj->getVarValue();

                    emit objectChanged(obj->getUid(), properties);
                }
            }
        }

        object->getPanel()->getDimension()->update();

        object->setInstanceChange(false);
    }
}

void QnsbAuthorView::notifiesObjectSelection(QnsbAuthorObject* object)
{
    if (selectedObject != object){
        if (selectedLink != NULL){
            selectedLink->setSelected(false);
            selectedLink->update();
            selectedLink = NULL;
        }

        object->getPanel()->setSelected(true);
        object->getPanel()->getDimension()->update();

        notifiesPanelSelection(object->getPanel());

        if (selectedObject != NULL){
            selectedObject->setSelected(false);
        }

        selectedObject =  object;

        emit objectSelected(object->getUid());
    }
}

void QnsbAuthorView::adjustNextPanelObject(QnsbAuthorObject* reference, QnsbAuthorPanel* panel)
{
    bool alreadyChange = true;

    foreach(QnsbAuthorObject* object, panel->getObjects()){
        if (object->getStatusID() == reference->getLastStatusID()){

            object->setTop(reference->getTop());
            object->setLeft(reference->getLeft());
            object->setWidth(reference->getWidth());
            object->setHeight(reference->getHeight());

            object->setSrc(reference->getSrc());
            object->setVarName(reference->getVarName());
            object->setVarValue(reference->getVarValue());
            object->setStatusID(reference->getStatusID());

            alreadyChange = false;

            QMap<QString,QString> properties;

            properties["top"] = QString::number(100*(object->getTop()-32)/256, 'f', 2) + "%";
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
        }
    }

    if (!alreadyChange){
        if (panel->getNext() != NULL){
            adjustNextPanelObject(reference, panel->getNext());

        }else{
            foreach(QnsbAuthorLink* link, panel->getDimension()->getChain()->getLinks()){
                foreach(QnsbAuthorDimension* dim, link->getTarget()->getDimensions()){
                    if (reference->getPanel()->getDimension()->getName() == dim->getName()){
                        adjustNextPanelObject(reference, dim->getPanels().first());
                    }
                }
            }
        }
    }
}

void QnsbAuthorView::resizeEvent(QResizeEvent* event)
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
