#include "qnsbdocument.h"

QnsbDocument::QnsbDocument(QObject* parent)
    : QObject(parent)
{
    domdoc = NULL;

    rhome = NULL;

    xauxpanel_last = NULL;
}

QnsbDocument::~QnsbDocument()
{

}

void QnsbDocument::save(QString location)
{
    QFile* file = new QFile(location);

    if (file->open(QIODevice::WriteOnly | QIODevice::Text)){
        QTextStream stream(file);
        stream.setCodec("UTF-8");

        domdoc = new QDomDocument();

        write();

        domdoc->save(stream,4,QDomNode::EncodingFromTextStream);
    }

    delete file;
}

void QnsbDocument::load(QString location)
{
    QFile* file = new QFile(location);

    if (file->open(QIODevice::ReadOnly)){
        domdoc = new QDomDocument();

        if (domdoc->setContent(file)){
            read();
        }
    }

    delete file;
}

void QnsbDocument::exportToNCL(QString location)
{
    QFile* file = new QFile(location);

    QFileInfo finfo(location);

    savedir.setPath(finfo.absoluteDir().path());

    if (file->open(QIODevice::WriteOnly | QIODevice::Text)){
        QTextStream stream(file);
        stream.setCodec("UTF-8");

        domdoc = new QDomDocument();

        writeNCL();

        domdoc->save(stream,4,QDomNode::EncodingFromTextStream);
    }

    delete file;
}

QString QnsbDocument::getExportData()
{
    domdoc = new QDomDocument();

    writeNCL();

    return domdoc->toString();
}

void QnsbDocument::clean()
{
    // TODO: QnsbDocument::clean().
}

void QnsbDocument::addChain(QString uid, QMap<QString,QString> properties)
{
//    // qDebug() << "QnsbDocument::addChain";

    if (!chains.contains(uid)){
        QnsbChain* chain = new QnsbChain();
        chain->setUid(uid);
        chain->setId(properties["id"]);
        chain->setInterface(properties["interface"]);
        chain->setType(properties["type"]);

        if (chains.contains(properties["matrix"])){
            chain->setMatrix(chains[properties["matrix"]]);
        }

        QnsbNarrative::addChain(chain);

        chains[uid] = chain;
    }
}

void QnsbDocument::removeChain(QString uid)
{
    // qDebug() << "QnsbDocument::addChain";

    // TODO: QnsbDocument::removeChain().
}

void QnsbDocument::changeChain(QString uid, QMap<QString,QString> properties)
{
    // qDebug() << "QnsbDocument::changeChain()";

    if (chains.contains(uid)){
//        QnsbChain* chain = chains[uid];

//        chain->setId(properties["id"]);
//        chain->setType(properties["type"]);
//        chain->setInterface(properties["interface"]);
    }
}

void QnsbDocument::selectChain(QString uid)
{
    // qDebug() << "QnsbDocument::selectChain";

    // TODO: QnsbDocument::selectChain().
}

void QnsbDocument::addDimension(QString uid, QString parent, QMap<QString,QString> properties)
{
    if (chains.contains(parent) && !dimensions.contains(uid)){
        QnsbDimension* dimension = new QnsbDimension();
        dimension->setUid(uid);
        dimension->setName(properties["name"]);

        chains[parent]->addDimension(dimension);

        dimensions[uid] = dimension;
    }
}

void QnsbDocument::removeDimension(QString uid)
{
    // qDebug() << "QnsbDocument::removeDimension()";
}

void QnsbDocument::changeDimension(QString uid, QMap<QString,QString> properties)
{
    // qDebug() << "QnsbDocument::changeDimension()";
}

void QnsbDocument::selectDimension(QString uid)
{
    // qDebug() << "QnsbDocument::selectDimension()";
}

void QnsbDocument::addLink(QString uid, QString parent, QMap<QString,QString> properties)
{
    // qDebug() << "QnsbDocument::addLink()";

    if (chains.contains(parent) && !links.contains(uid)){
        QnsbLink* link = new QnsbLink();
        link->setUid(uid);
        link->setTarget(properties["target"]);
        link->setType(properties["type"]);
        link->setKey(properties["key"]);
        link->setVarName(properties["varname"]);
        link->setOp(properties["op"]);
        link->setVarValue(properties["varvalue"]);

        link->seteTarget(chains[properties["targetUID"]]);

        if (objects.contains(properties["triggerUID"])){
            link->setTrigger(objects[properties["triggerUID"]]);
        }

        chains[parent]->addLink(link);

        links[uid] = link;
    }
}

void QnsbDocument::removeLink(QString uid)
{
    // qDebug() << "QnsbDocument::removeLink()";
}

void QnsbDocument::changeLink(QString uid, QMap<QString,QString> properties)
{
    // qDebug() << "QnsbDocument::changeLink()";

    if (links.contains(uid) && chains.contains(properties["targetUID"])){
        QnsbLink* link = links[uid];

        link->setType(properties["type"]);
        link->setKey(properties["key"]);
        link->setVarName(properties["varname"]);
        link->setOp(properties["op"]);
        link->setVarValue(properties["varvalue"]);

        link->seteTarget(chains[properties["targetUID"]]);

        if (objects.contains(properties["triggerUID"])){
            link->setTrigger(objects[properties["triggerUID"]]);
        }
    }
}

void QnsbDocument::selectLink(QString uid)
{
    // qDebug() << "QnsbDocument::selectLink()";
}

void QnsbDocument::addPanel(QString uid, QString parent, QMap<QString,QString> properties)
{
    // qDebug() << "QnsbDocument::addPanel()";

    if (dimensions.contains(parent) && !panels.contains(uid)){
        QnsbPanel* panel = new QnsbPanel();
        panel->setUid(uid);

        panel->setBegin(properties["begin"]);
        panel->setEnd(properties["end"]);
        panel->setNotes(properties["notes"]);

        dimensions[parent]->addPanel(panel);

        panels[uid] = panel;
    }
}

void QnsbDocument::removePanel(QString uid)
{
    // qDebug() << "QnsbDocument::removePanel()";
}

void QnsbDocument::changePanel(QString uid, QMap<QString,QString> properties)
{
    // qDebug() << "QnsbDocument::changePanel()";

    if (panels.contains(uid)){
        QnsbPanel* panel =  panels[uid];

        panel->setBegin(properties["begin"]);
        panel->setEnd(properties["end"]);
        panel->setNotes(properties["notes"]);
    }

}

void QnsbDocument::selectPanel(QString uid)
{
    // qDebug() << "QnsbDocument::selectPanel()";
}

void QnsbDocument::addObject(QString uid, QString parent, QMap<QString,QString> properties)
{
    if (!objects.contains(uid) && panels.contains(parent)){
        // qDebug() << "QnsbDocument::addObject()";

        QnsbObject* object = new QnsbObject();
        object->setUid(uid);

        object->addProperty("top",properties["top"]);
        object->addProperty("left",properties["left"]);
        object->addProperty("width",properties["width"]);
        object->addProperty("height",properties["height"]);

        object->setType(properties["type"]);
        object->setId(properties["id"]);
        object->setInstanceId(properties["instance"]);
        object->setStatusId(properties["status"]);
        object->setPanel(panels[parent]);
        object->setSrc(properties["src"]);
        object->setSketch(properties["sketch"]);
        object->setPreview(properties["preview"]);

        panels[parent]->addObject(object);

        if (!objectsInstance.contains(properties["instance"])){
            objectsInstance[properties["instance"]] = object;
        }

        objects[uid] = object;
    }
}

void QnsbDocument::removeObject(QString uid)
{
    // qDebug() << "QnsbDocument::removeObject()";

    if (objects.contains(uid)){
        if (objectsInstance[objects[uid]->getInstanceId()]->getUid() == objects[uid]->getUid()){
            objectsInstance.remove(objects[uid]->getInstanceId());
        }

        objects[uid]->getPanel()->removeObject(objects[uid]);

        objects.remove(uid);
    }
}

void QnsbDocument::changeObject(QString uid, QMap<QString,QString> properties)
{
    if (objects.contains(uid)){
        // qDebug() << "QnsbDocument::changeObject()";

        QnsbObject* object = objects[uid];

        object->addProperty("top",properties["top"]);
        object->addProperty("left",properties["left"]);
        object->addProperty("width",properties["width"]);
        object->addProperty("height",properties["height"]);

        object->setType(properties["type"]);
        object->setId(properties["id"]);
        object->setInstanceId(properties["instance"]);
        object->setStatusId(properties["status"]);
        object->setSrc(properties["src"]);
        object->setSketch(properties["sketch"]);
        object->setPreview(properties["preview"]);
        object->setVarName(properties["varname"]);
        object->setVarValue(properties["varvalue"]);

    }
}

void QnsbDocument::selectObject(QString uid)
{
    // qDebug() << "QnsbDocument::selectObject()";
}

void QnsbDocument::notifiesChainAddition(QnsbChain* chain)
{
    QnsbNarrative::addChain(chain);

    chains[chain->getUid()] = chain;

    QMap<QString,QString> properties;

    properties["id"] = chain->getId();

    properties["type"] = chain->getType();

    properties["interface"] = chain->getInterface();

    emit chainAdded(chain->getUid(),properties);
}

void QnsbDocument::notifiesChainChange(QnsbChain* chain)
{
    QMap<QString,QString> properties;

    properties["matrix"] = chain->getMatrix()->getUid();

    emit chainChanged(chain->getUid(), properties);
}

void QnsbDocument::notifiesDimensionAddition(QnsbDimension* dimension)
{
    dimensions[dimension->getUid()] = dimension;

    QMap<QString,QString> properties;

    properties["name"] = dimension->getName();

    emit dimensionAdded(dimension->getUid(),dimension->getChain()->getUid(),properties);
}

void QnsbDocument::notifiesLinkAddition(QnsbLink* link)
{
    links[link->getUid()] = link;

    QMap<QString,QString> properties;

    properties["target"] = link->getTarget();
    properties["targetUID"] = link->geteTarget()->getUid();
    properties["type"] = link->getType();
    properties["key"] = link->getKey();
    properties["varname"] = link->getVarName();
    properties["op"] = link->getOp();
    properties["varvalue"] = link->getVarValue();

    if (link->getTrigger() != NULL){
        properties["triggerUID"] = link->getTrigger()->getUid();
    }

    emit linkAdded(link->getUid(),link->getChain()->getUid(),properties);
}

void QnsbDocument::notifiesPanelAddition(QnsbPanel* panel)
{
    panels[panel->getUid()] = panel;

    QMap<QString,QString> properties;

    properties["begin"] = panel->getBegin();
    properties["end"] = panel->getEnd();
    properties["notes"] = panel->getNotes();

    emit panelAdded(panel->getUid(), panel->getDimension()->getUid(),properties);
}

void QnsbDocument::notifiesObjectAddition(QnsbObject* object)
{
    // qDebug() << "QnsbDocument::notifiesObjectAddition";

    objects[object->getUid()] = object;

    if (!objectsInstance.contains(object->getInstanceId())){
        objectsInstance[object->getInstanceId()] = object;
    }

    QMap<QString,QString> properties;

    properties["top"] = object->getProperty("top");
    properties["left"] = object->getProperty("left");
    properties["width"] = object->getProperty("width");
    properties["height"] = object->getProperty("height");

    properties["id"] = object->getId();
    properties["type"] = object->getType();
    properties["instance"] = object->getInstanceId();
    properties["status"] = object->getStatusId();
    properties["src"]  = object->getSrc();
    properties["preview"]  = object->getPreview();
    properties["sketch"]  = object->getSketch();
    properties["varname"]  = object->getVarName();
    properties["varvalue"]  = object->getVarValue();

    emit objectAdded(object->getUid(), object->getPanel()->getUid(),properties);
}

void QnsbDocument::read()
{
    QDomElement parent = domdoc->firstChildElement();

    QDomNodeList list = parent.childNodes();

    for (unsigned int i=0;i<list.length();i++)
    {
        if (list.item(i).isElement())
        {
            QDomElement e = list.item(i).toElement();

            if (e.nodeName() == "chain"){
                readChain(e, new QnsbChain());
            }else if(e.nodeName() == "object"){
                readObject(e, new QnsbObject());
            }
        }
    }

    foreach(QnsbChain* chainn, getChains()){

        if (chainn->getType() == "referencial"){
            chainn->setMatrix(chains[rchainaux[chainn->getsMatrix()]]);

            notifiesChainChange(chainn);
        }
    }

    for (unsigned int i=0;i<list.length();i++)
    {
        if (list.item(i).isElement())
        {
            QDomElement e = list.item(i).toElement();

            if (e.nodeName() == "chain"){
                readChainLink(e);
            }
        }
    }

    emit chainSelected(rhome->getUid());

    rchainaux.clear();
    robjectaux.clear();
    robjectaux_last.clear();
    robjectaux_instance.clear();

    rhome = NULL;
}

void QnsbDocument::readChain(QDomElement e, QnsbChain* chain)
{
    if (rhome == NULL){
        rhome = chain;
    }

    if (e.attribute("id") != ""){
        chain->setId(e.attribute("id"));
    }

    if (e.attribute("interface") != ""){
        chain->setInterface(e.attribute("interface"));
    }

    if (e.attribute("type") != ""){
        chain->setType(e.attribute("type"));
    }

    if (e.attribute("refer") != ""){
        chain->setsMatrix(e.attribute("refer"));
    }

    rchainaux[chain->getId()] = chain->getUid();

    notifiesChainAddition(chain);

    QDomNodeList list = e.childNodes();

    for (unsigned int i=0;i<list.length();i++)
    {
        if (list.item(i).isElement())
        {
            QDomElement c = list.item(i).toElement();

            if (c.nodeName() == "dimension"){
                QnsbDimension* dimension = new QnsbDimension();

                chain->addDimension(dimension);

                readDimension(c, dimension);
            }
        }
    }
}

void QnsbDocument::readChainLink(QDomElement e)
{
    QDomNodeList list = e.childNodes();

    for (unsigned int i=0;i<list.length();i++)
    {
        if (list.item(i).isElement())
        {
            QDomElement c = list.item(i).toElement();

            if (c.nodeName() == "link"){
                QnsbChain* ch = chains[rchainaux[e.attribute("id")]];
                QnsbChain* t = chains[rchainaux[c.attribute("target")]];

                QnsbLink* link = new QnsbLink();
                link->setChain(ch);
                link->seteTarget(t);
                link->setTarget(c.attribute("target"));
                link->setType(c.attribute("type"));

                if (link->getType() == "interactive" || link->getType() == "adaptative"){
                    link->setTrigger(objects[robjectaux[c.attribute("trigger")]]);

                    QDomNodeList plist = c.childNodes();

                    for (unsigned int k=0;k<plist.length();k++)
                    {
                        if (plist.item(k).isElement())
                        {
                            QDomElement p = plist.item(k).toElement();

                            if (p.nodeName() == "property"){
                                readLinkProperty(p, link);
                            }
                        }
                    }
                }

                ch->addLink(link);

                notifiesLinkAddition(link);
            }
        }
    }
}

void QnsbDocument::readDimension(QDomElement e, QnsbDimension* dimension)
{
    if (e.attribute("name") != ""){
        dimension->setName(e.attribute("name"));
    }

    notifiesDimensionAddition(dimension);

    QDomNodeList list = e.childNodes();

    for (unsigned int i=0;i<list.length();i++)
    {
        if (list.item(i).isElement())
        {
            QDomElement c = list.item(i).toElement();

            if (c.nodeName() == "panel"){
                QnsbPanel* panel = new QnsbPanel();

                dimension->addPanel(panel);

                readPanel(c, panel);
            }
        }
    }
}

void QnsbDocument::readPanel(QDomElement e, QnsbPanel* panel)
{
    QDomNodeList listp = e.childNodes();

    for (unsigned int i=0;i<listp.length();i++)
    {
        if (listp.item(i).isElement())
        {
            QDomElement c = listp.item(i).toElement();

            if (c.nodeName() == "property"){
                readPanelProperty(c, panel);
            }
        }
    }

    notifiesPanelAddition(panel);

    QDomNodeList list = e.childNodes();

    for (unsigned int i=0;i<list.length();i++)
    {
        if (list.item(i).isElement())
        {
            QDomElement c = list.item(i).toElement();

            if (c.nodeName() == "object"){
                QnsbObject* object = new QnsbObject();
                object->setPanel(panel);

                panel->addObject(object);

                readObjectReference(c, object);
            }
        }
    }
}

void QnsbDocument::readObject(QDomElement e, QnsbObject* object)
{
    if (e.attribute("id") != ""){
        object->setId(e.attribute("id"));
    }

    if (e.attribute("type") != ""){
        object->setType(e.attribute("type"));
    }

    if (e.attribute("src") != ""){
        object->setSrc(e.attribute("src"));
    }

    if (e.attribute("preview") != ""){
        object->setPreview(e.attribute("preview"));
    }


    if (e.attribute("sketch") != ""){
        object->setSketch(e.attribute("sketch"));
    }


    object->setInstanceId(object->getUid());
    object->setStatusId(object->getUid());

    QDomNodeList list = e.childNodes();

    for (unsigned int i=0;i<list.length();i++)
    {
        if (list.item(i).isElement())
        {
            QDomElement c = list.item(i).toElement();

            if (c.nodeName() == "property"){
                readObjectProperty(c, object);
            }
        }
    }

    robjectaux_instance[object->getInstanceId()] = object;

    robjectaux[object->getId()] = object->getInstanceId();
}

void QnsbDocument::readObjectReference(QDomElement e, QnsbObject* object)
{
    QnsbObject* refer = robjectaux_instance[robjectaux[e.attribute("refer")]];

    object->setId(refer->getId());

    object->setType(refer->getType());
    object->setSrc(refer->getSrc());
    object->setInstanceId(refer->getInstanceId());
    object->setSketch(refer->getSketch());
    object->setPreview(refer->getPreview());

    QDomNodeList list = e.childNodes();

    for (unsigned int i=0;i<list.length();i++)
    {
        if (list.item(i).isElement())
        {
            QDomElement c = list.item(i).toElement();

            if (c.nodeName() == "property"){
                readObjectProperty(c, object);
            }
        }
    }

    if (robjectaux_last.contains(refer->getInstanceId())){
        if (compare(robjectaux_last[refer->getInstanceId()],object)){
            object->setStatusId(robjectaux_last[refer->getInstanceId()]->getStatusId());
        }else{
            object->setStatusId(QUuid::createUuid().toString());
        }
    }else{
        object->setUid(refer->getUid());
        object->setStatusId(refer->getStatusId());
    }

    robjectaux_last[refer->getInstanceId()] = object;

    notifiesObjectAddition(object);
}

void QnsbDocument::readObjectProperty(QDomElement e, QnsbObject* parent)
{
    if (e.attribute("name") != "" && e.attribute("value") != ""){
        if (e.attribute("name") == "name"){
            parent->setVarName(e.attribute("value"));

        }else if (e.attribute("name") == "value"){
            parent->setVarValue(e.attribute("value"));

        }else{
            parent->addProperty(e.attribute("name"), e.attribute("value"));
        }
    }
}

void QnsbDocument::readLinkProperty(QDomElement e, QnsbLink* parent)
{
    if (e.attribute("name") == "key"){
        parent->setKey(e.attribute("value"));

    }else if (e.attribute("name") == "variable"){
        parent->setVarName(e.attribute("value"));

    }else if (e.attribute("name") == "op"){
        parent->setOp(e.attribute("value"));

    }else if (e.attribute("name") == "value"){
        parent->setVarValue(e.attribute("value"));
    }
}

void QnsbDocument::readPanelProperty(QDomElement e, QnsbPanel* parent)
{
    if (e.attribute("name") != "" && e.attribute("value") != ""){
        if (e.attribute("name") == "begin"){
            parent->setBegin(e.attribute("value"));

        }else if (e.attribute("name") == "end"){
            parent->setEnd(e.attribute("value"));

        }else if (e.attribute("name") == "notes"){
            parent->setNotes(e.attribute("value"));
        }
    }
}

void QnsbDocument::write()
{
    QDomElement e = domdoc->createElement("inl");

    foreach (QnsbObject* object, objectsInstance.values()){
        writeObject(object, e);
    }

    foreach (QnsbChain* chain, getChains()){
        writeChain(chain, e);
    }

    domdoc->appendChild(e);
}

void QnsbDocument::writeChain(QnsbChain* chain, QDomElement parent)
{
    QDomElement e = domdoc->createElement("chain");

    e.setAttribute("id",chain->getId());

    e.setAttribute("type", chain->getType());

    if (chain->getType() != "referencial"){
        e.setAttribute("interface",chain->getInterface());

        foreach(QnsbDimension* dimension, chain->getDimensions()){
            writeDimension(dimension, e);
        }

        foreach(QnsbLink* link, chain->getLinks()){
            writeLink(link, e);
        }

    }else{
        e.setAttribute("refer", chain->getMatrix()->getId());
    }

    parent.appendChild(e);
}

void QnsbDocument::writeDimension(QnsbDimension* dimension, QDomElement parent)
{
    QDomElement e = domdoc->createElement("dimension");

    e.setAttribute("name",dimension->getName());

    foreach(QnsbPanel* panel, dimension->gePanels()){
        writePanel(panel, e);
    }

    parent.appendChild(e);
}

void QnsbDocument::writeLink(QnsbLink* link, QDomElement parent)
{
    QDomElement e = domdoc->createElement("link");

    e.setAttribute("type",link->getType());

    e.setAttribute("target",link->getTarget());

    if (link->getType() == "interactive"){
        e.setAttribute("trigger", link->getTrigger()->getId());

        writeProperty("key",link->getKey(), e);

    }else if (link->getType() == "adaptative"){
        e.setAttribute("trigger", link->getTrigger()->getId());

        writeProperty("variable",link->getVarName(), e);
        writeProperty("op",link->getOp(), e);
        writeProperty("value",link->getVarValue(), e);
    }

    parent.appendChild(e);
}

void QnsbDocument::writePanel(QnsbPanel* panel, QDomElement parent)
{
    QDomElement e = domdoc->createElement("panel");

    if (panel->getBegin() != ""){
        writeProperty("begin",panel->getBegin(),e);
    }

    if (panel->getEnd() != ""){
        writeProperty("end",panel->getEnd(),e);
    }

    if (panel->getNotes() != ""){
        writeProperty("notes",panel->getNotes(),e);
    }

    foreach (QnsbObject* object, panel->getObjects()){
        writeObjectReference(object, e);
    }

    parent.appendChild(e);
}

void QnsbDocument::writeObject(QnsbObject* object, QDomElement parent)
{
    QDomElement e = domdoc->createElement("object");

    e.setAttribute("id",object->getId());
    e.setAttribute("type",object->getType());

    if (object->getSrc() != ""){
        e.setAttribute("src", object->getSrc());
    }

    if (object->getPreview() != ""){
        e.setAttribute("preview", object->getPreview());
    }

    if (object->getSketch() != ""){
        e.setAttribute("sketch", object->getSketch());
    }

    if (object->getType() == "variable"){
        if (object->getVarName() != ""){
            writeProperty("name",object->getVarName(),e);
        }

        if (object->getVarValue() != ""){
            writeProperty("value",object->getVarValue(),e);
        }
    }

    foreach(QString key, object->getProperties().keys()){
        writeProperty(key,object->getProperty(key),e);
    }

    parent.appendChild(e);
}

void QnsbDocument::writeObjectReference(QnsbObject* object, QDomElement parent)
{
    QDomElement e = domdoc->createElement("object");

    e.setAttribute("refer",objectsInstance[object->getInstanceId()]->getId());

    if (object->getType() == "variable"){
        if (object->getVarName() != ""){
            writeProperty("name",object->getVarName(),e);
        }

        if (object->getVarValue() != ""){
            writeProperty("value",object->getVarValue(),e);
        }
    }

    foreach(QString key, object->getProperties().keys()){
        writeProperty(key,object->getProperty(key),e);
    }

    parent.appendChild(e);
}

void QnsbDocument::writeProperty(QString name, QString value, QDomElement parent)
{
    QDomElement e = domdoc->createElement("property");

    e.setAttribute("value",value);
    e.setAttribute("name",name);

    parent.appendChild(e);
}

void QnsbDocument::writeNCL()
{
    QDomElement e = domdoc->createElement("ncl");

    QDomElement head = domdoc->createElement("head");
    writeNCLConnectors(head);
    e.appendChild(head);

    QDomElement body = domdoc->createElement("body");
    writeNCLPort(body);
    writeNCLMedias(body);
    writeNCLLinks(body);
    e.appendChild(body);

    domdoc->appendChild(e);

    xauxpanel_last = NULL;
}

void QnsbDocument::writeNCLConnectors(QDomElement parent)
{
    QDomElement e = domdoc->createElement("connectorBase");

    writeNCLOnBeginStartStopSet(e);
    writeNCLOnEndSetStopStart(e);
    writeNCLOnKeySelectionStartStopSet(e);
    writeNCLOnEndTestSetStopStart(e);
    writeNCLOnBeginTestSetStopStart(e);
    writeNCLOnEndTestNSetStopStart(e);

    parent.appendChild(e);
}

/*
<causalConnector id="onBeginSetStopStart">
   <connectorParam name="var"/>
   <simpleCondition role="onBegin" max="unbounded"/>
   <compoundAction operator="seq">
       <simpleAction role="start" max="unbounded" qualifier="par"/>
       <simpleAction role="stop" max="unbounded" qualifier="par"/>
       <simpleAction role="set" value="$var" max="unbounded" qualifier="par"/>
   </compoundAction>
</causalConnector>
  */
void QnsbDocument::writeNCLOnBeginStartStopSet(QDomElement parent)
{
    QDomElement cc = domdoc->createElement("causalConnector");
    cc.setAttribute("id","onBeginSetStopStart");

        QDomElement cp = domdoc->createElement("connectorParam");
        cp.setAttribute("name","var");
        cc.appendChild(cp);

        QDomElement sc = domdoc->createElement("simpleCondition");
        sc.setAttribute("role","onBegin");
        sc.setAttribute("max","unbounded");
        cc.appendChild(sc);

        QDomElement ca = domdoc->createElement("compoundAction");
        ca.setAttribute("operator","seq");
        cc.appendChild(ca);

            QDomElement sa02 = domdoc->createElement("simpleAction");
            sa02.setAttribute("role","stop");
            sa02.setAttribute("max","unbounded");
            sa02.setAttribute("min","0");
            sa02.setAttribute("qualifier","par");
            ca.appendChild(sa02);

            QDomElement sa01 = domdoc->createElement("simpleAction");
            sa01.setAttribute("role","start");
            sa01.setAttribute("max","unbounded");
            sa01.setAttribute("min","0");
            sa01.setAttribute("qualifier","seq");
            ca.appendChild(sa01);

            QDomElement sa03 = domdoc->createElement("simpleAction");
            sa03.setAttribute("role","set");
            sa03.setAttribute("value","$var");
            sa03.setAttribute("max","unbounded");
            sa03.setAttribute("min","0");
            sa03.setAttribute("qualifier","par");
            ca.appendChild(sa03);

    parent.appendChild(cc);
}

void QnsbDocument::writeNCLOnBeginTestSetStopStart(QDomElement parent)
{
    QDomElement cc = domdoc->createElement("causalConnector");
    cc.setAttribute("id","onBeginTestSetStopStart");

        QDomElement cp01 = domdoc->createElement("connectorParam");
        cp01.setAttribute("name","var");
        cc.appendChild(cp01);

        QDomElement cp02 = domdoc->createElement("connectorParam");
        cp02.setAttribute("name","value");
        cc.appendChild(cp02);

        QDomElement ccd = domdoc->createElement("compoundCondition");
        ccd.setAttribute("operator","and");

            QDomElement sc01 = domdoc->createElement("simpleCondition");
            sc01.setAttribute("role","onBegin");
            sc01.setAttribute("max","unbounded");
            ccd.appendChild(sc01);

            QDomElement as = domdoc->createElement("assessmentStatement");
            as.setAttribute("comparator","eq");

                QDomElement aa = domdoc->createElement("attributeAssessment");
                aa.setAttribute("role","test");
                aa.setAttribute("eventType","attribution");
                aa.setAttribute("attributeType","nodeProperty");
                as.appendChild(aa);

                QDomElement av = domdoc->createElement("valueAssessment");
                av.setAttribute("value","$value");
                as.appendChild(av);

            ccd.appendChild(as);

        cc.appendChild(ccd);

        QDomElement ca = domdoc->createElement("compoundAction");
        ca.setAttribute("operator","seq");
        cc.appendChild(ca);

            QDomElement sa03 = domdoc->createElement("simpleAction");
            sa03.setAttribute("role","set");
            sa03.setAttribute("value","$var");
            sa03.setAttribute("max","unbounded");
            sa03.setAttribute("min","0");
            sa03.setAttribute("qualifier","par");
            ca.appendChild(sa03);

            QDomElement sa02 = domdoc->createElement("simpleAction");
            sa02.setAttribute("role","stop");
            sa02.setAttribute("max","unbounded");
            sa02.setAttribute("min","0");
            sa02.setAttribute("qualifier","par");
            ca.appendChild(sa02);

            QDomElement sa01 = domdoc->createElement("simpleAction");
            sa01.setAttribute("role","start");
            sa01.setAttribute("max","unbounded");
            sa01.setAttribute("min","0");
            sa01.setAttribute("qualifier","seq");
            ca.appendChild(sa01);

    parent.appendChild(cc);
}

void QnsbDocument::writeNCLOnEndTestSetStopStart(QDomElement parent)
{
    QDomElement cc = domdoc->createElement("causalConnector");
    cc.setAttribute("id","onEndTestSetStopStart");

        QDomElement cp01 = domdoc->createElement("connectorParam");
        cp01.setAttribute("name","var");
        cc.appendChild(cp01);

        QDomElement cp02 = domdoc->createElement("connectorParam");
        cp02.setAttribute("name","value");
        cc.appendChild(cp02);

        QDomElement ccd = domdoc->createElement("compoundCondition");
        ccd.setAttribute("operator","and");

            QDomElement sc01 = domdoc->createElement("simpleCondition");
            sc01.setAttribute("role","onEnd");
            sc01.setAttribute("max","unbounded");
            ccd.appendChild(sc01);

            QDomElement as = domdoc->createElement("assessmentStatement");
            as.setAttribute("comparator","eq");

                QDomElement aa = domdoc->createElement("attributeAssessment");
                aa.setAttribute("role","test");
                aa.setAttribute("eventType","attribution");
                aa.setAttribute("attributeType","nodeProperty");
                as.appendChild(aa);

                QDomElement av = domdoc->createElement("valueAssessment");
                av.setAttribute("value","$value");
                as.appendChild(av);

            ccd.appendChild(as);

        cc.appendChild(ccd);

        QDomElement ca = domdoc->createElement("compoundAction");
        ca.setAttribute("operator","seq");
        cc.appendChild(ca);

            QDomElement sa03 = domdoc->createElement("simpleAction");
            sa03.setAttribute("role","set");
            sa03.setAttribute("value","$var");
            sa03.setAttribute("max","unbounded");
            sa03.setAttribute("min","0");
            sa03.setAttribute("qualifier","par");
            ca.appendChild(sa03);

            QDomElement sa02 = domdoc->createElement("simpleAction");
            sa02.setAttribute("role","stop");
            sa02.setAttribute("max","unbounded");
            sa02.setAttribute("min","0");
            sa02.setAttribute("qualifier","par");
            ca.appendChild(sa02);

            QDomElement sa01 = domdoc->createElement("simpleAction");
            sa01.setAttribute("role","start");
            sa01.setAttribute("max","unbounded");
            sa01.setAttribute("min","0");
            sa01.setAttribute("qualifier","seq");
            ca.appendChild(sa01);

    parent.appendChild(cc);
}

void QnsbDocument::writeNCLOnEndTestNSetStopStart(QDomElement parent)
{
    QSet<int> connset;

    foreach(QnsbChain* chain, chains.values()){
        int N = chain->getLinks().size()-1;

        if (!connset.contains(N) && N > 0){
            connset.insert(N);

            QDomElement cc = domdoc->createElement("causalConnector");
            cc.setAttribute("id","onEndTest"+QString::number(N)+"SetStopStart");

                QDomElement cp01 = domdoc->createElement("connectorParam");
                cp01.setAttribute("name","var");
                cc.appendChild(cp01);

                QDomElement cp02 = domdoc->createElement("connectorParam");
                cp02.setAttribute("name","value");
                cc.appendChild(cp02);



                QDomElement ccd = domdoc->createElement("compoundCondition");
                ccd.setAttribute("operator","and");

                    QDomElement sc01 = domdoc->createElement("simpleCondition");
                    sc01.setAttribute("role","onEnd");
                    sc01.setAttribute("max","unbounded");
                    ccd.appendChild(sc01);

                    for(int i=0;i<N;i++){
                        QDomElement as = domdoc->createElement("assessmentStatement");
                        as.setAttribute("comparator","eq");

                            QDomElement aa = domdoc->createElement("attributeAssessment");
                            aa.setAttribute("role","test"+QString::number(i+1));
                            aa.setAttribute("eventType","attribution");
                            aa.setAttribute("attributeType","nodeProperty");
                            as.appendChild(aa);

                            QDomElement av = domdoc->createElement("valueAssessment");
                            av.setAttribute("value","$value");
                            as.appendChild(av);

                        ccd.appendChild(as);
                    }

                cc.appendChild(ccd);

                QDomElement ca = domdoc->createElement("compoundAction");
                ca.setAttribute("operator","seq");
                cc.appendChild(ca);

                    QDomElement sa03 = domdoc->createElement("simpleAction");
                    sa03.setAttribute("role","set");
                    sa03.setAttribute("value","$var");
                    sa03.setAttribute("max","unbounded");
                    sa03.setAttribute("min","0");
                    sa03.setAttribute("qualifier","par");
                    ca.appendChild(sa03);

                    QDomElement sa02 = domdoc->createElement("simpleAction");
                    sa02.setAttribute("role","stop");
                    sa02.setAttribute("max","unbounded");
                    sa02.setAttribute("min","0");
                    sa02.setAttribute("qualifier","par");
                    ca.appendChild(sa02);

                    QDomElement sa01 = domdoc->createElement("simpleAction");
                    sa01.setAttribute("role","start");
                    sa01.setAttribute("max","unbounded");
                    sa01.setAttribute("min","0");
                    sa01.setAttribute("qualifier","seq");
                    ca.appendChild(sa01);

            parent.appendChild(cc);
        }
    }
}

void QnsbDocument::writeNCLOnEndSetStopStart(QDomElement parent)
{
    QDomElement cc = domdoc->createElement("causalConnector");
    cc.setAttribute("id","onEndSetStopStart");

        QDomElement cp01 = domdoc->createElement("connectorParam");
        cp01.setAttribute("name","var");
        cc.appendChild(cp01);

        QDomElement sc = domdoc->createElement("simpleCondition");
        sc.setAttribute("role","onEnd");
        sc.setAttribute("max","unbounded");
        cc.appendChild(sc);

        QDomElement ca = domdoc->createElement("compoundAction");
        ca.setAttribute("operator","seq");
        cc.appendChild(ca);

            QDomElement sa02 = domdoc->createElement("simpleAction");
            sa02.setAttribute("role","stop");
            sa02.setAttribute("max","unbounded");
            sa02.setAttribute("min","0");
            sa02.setAttribute("qualifier","par");
            ca.appendChild(sa02);

            QDomElement sa01 = domdoc->createElement("simpleAction");
            sa01.setAttribute("role","start");
            sa01.setAttribute("max","unbounded");
            sa01.setAttribute("min","0");
            sa01.setAttribute("qualifier","seq");
            ca.appendChild(sa01);

            QDomElement sa03 = domdoc->createElement("simpleAction");
            sa03.setAttribute("role","set");
            sa03.setAttribute("value","$var");
            sa03.setAttribute("max","unbounded");
            sa03.setAttribute("min","0");
            sa03.setAttribute("qualifier","par");
            ca.appendChild(sa03);

    parent.appendChild(cc);
}

void QnsbDocument::writeNCLOnKeySelectionStartStopSet(QDomElement parent)
{
    QDomElement cc = domdoc->createElement("causalConnector");
    cc.setAttribute("id","onKeySelectionStartStopSet");

        QDomElement cp01 = domdoc->createElement("connectorParam");
        cp01.setAttribute("name","key");
        cc.appendChild(cp01);

        QDomElement cp02 = domdoc->createElement("connectorParam");
        cp02.setAttribute("name","var");
        cc.appendChild(cp02);

        QDomElement sc = domdoc->createElement("simpleCondition");
        sc.setAttribute("role","onSelection");
        sc.setAttribute("key","$key");
        sc.setAttribute("max","unbounded");
        cc.appendChild(sc);

        QDomElement ca = domdoc->createElement("compoundAction");
        ca.setAttribute("operator","seq");
        cc.appendChild(ca);

            QDomElement sa03 = domdoc->createElement("simpleAction");
            sa03.setAttribute("role","set");
            sa03.setAttribute("value","$var");
            sa03.setAttribute("max","unbounded");
            sa03.setAttribute("min","0");
            sa03.setAttribute("qualifier","par");
            ca.appendChild(sa03);

            QDomElement sa02 = domdoc->createElement("simpleAction");
            sa02.setAttribute("role","stop");
            sa02.setAttribute("max","unbounded");
            sa02.setAttribute("min","0");
            sa02.setAttribute("qualifier","par");
            ca.appendChild(sa02);

            QDomElement sa01 = domdoc->createElement("simpleAction");
            sa01.setAttribute("role","start");
            sa01.setAttribute("max","unbounded");
            sa01.setAttribute("min","0");
            sa01.setAttribute("qualifier","seq");
            ca.appendChild(sa01);

    parent.appendChild(cc);
}

void QnsbDocument::writeNCLPort(QDomElement parent)
{
    QDomElement e = domdoc->createElement("port");
    e.setAttribute("id","pMain");
    e.setAttribute("component", getChains().at(0)->getId());

    parent.appendChild(e);
}

void QnsbDocument::writeNCLMedias(QDomElement parent)
{
    foreach(QnsbChain* chain, getChains()){
        if (chain->getType() != "referencial"){
            QDomElement e = domdoc->createElement("media");
            e.setAttribute("id",chain->getId());

            int i = 0;

            // qDebug() << chain->getType();

            foreach(QnsbPanel* panel, chain->getDimensions().at(0)->gePanels()){
                QDomElement a = domdoc->createElement("area");
                a.setAttribute("id",chain->getId()+"_"+QString::number(++i));
                a.setAttribute("begin",panel->getBegin());
                a.setAttribute("end",panel->getEnd());

                e.appendChild(a);
            }

            parent.appendChild(e);
        }
    }

    int i = 0;

    foreach(QnsbLink* link, links.values()){
        if (link->getType() != "sequencial"){
            QString id = "mlink"+QString::number(i++);

            QDomElement e = domdoc->createElement("media");
            e.setAttribute("id",id);
            e.setAttribute("type","application/x-ginga-settings");

                QDomElement a = domdoc->createElement("property");
                a.setAttribute("name","service."+id);
                a.setAttribute("value",0);
                e.appendChild(a);

            parent.appendChild(e);

            wnlinkaux[link->getUid()] = id;
        }
    }

    foreach(QnsbObject* object, objectsInstance.values()){
        if (object->getType() == "variable"){
            QDomElement e = domdoc->createElement("media");
            e.setAttribute("id",object->getId());
            e.setAttribute("type","application/x-ginga-settings");

                QDomElement p01 = domdoc->createElement("property");
                p01.setAttribute("name",object->getVarName());
                if (object->getVarValue() != ""){
                    p01.setAttribute("value",object->getVarValue());
                }
                e.appendChild(p01);

            parent.appendChild(e);

        }else {
            QDomElement e = domdoc->createElement("media");
            e.setAttribute("id",object->getId());
            e.setAttribute("src",savedir.relativeFilePath(object->getSrc()));

                QDomElement p01 = domdoc->createElement("property");
                p01.setAttribute("name","top");
                p01.setAttribute("value",object->getProperty("top"));
                e.appendChild(p01);

                QDomElement p02 = domdoc->createElement("property");
                p02.setAttribute("name","left");
                p02.setAttribute("value",object->getProperty("left"));
                e.appendChild(p02);

                QDomElement p03 = domdoc->createElement("property");
                p03.setAttribute("name","width");
                p03.setAttribute("value",object->getProperty("width"));
                e.appendChild(p03);

                QDomElement p04 = domdoc->createElement("property");
                p04.setAttribute("name","height");
                p04.setAttribute("value",object->getProperty("height"));
                e.appendChild(p04);

                QDomElement p05 = domdoc->createElement("property");
                p05.setAttribute("name","bounds");
                e.appendChild(p05);

            parent.appendChild(e);
        }
    }
}

/*
  <link  id="lEndAdvert" xconnector="conEx#onEndSet">
          <bind role="onEnd" component="advert" interface="pShoes"/>
          <bind role="set" component="animation" interface="bounds">
                  <bindParam name="varSet" value="0,0,222.22%,222.22%"/>
          </bind>
  </link>
  */

void QnsbDocument::writeNCLLinks(QDomElement parent)
{
    writeNCLLinks(getChains().at(0),parent);
}

void QnsbDocument::writeNCLLinks(QnsbChain* chain, QDomElement parent)
{
    if (chain != NULL){
        int i = 0;

        QString chainID = chain->getId();

        if (chain->getType() == "referencial"){
            chainID = chain->getMatrix()->getId();
        }

        foreach(QnsbPanel* panel, chain->getDimensions().at(0)->gePanels()){
            QDomElement link = domdoc->createElement("link");
            link.setAttribute("xconnector","onBeginSetStopStart");

                QDomElement b = domdoc->createElement("bind");
                b.setAttribute("role","onBegin");
                b.setAttribute("component",chainID);
                b.setAttribute("interface",chainID+"_"+QString::number(++i));
                link.appendChild(b);

                writeNCLActionsBind(panel, link);

            if (link.childNodes().size() > 1){
                parent.appendChild(link);
            }
        }

        if (chain->getLinks().size() == 0){
            QDomElement link = domdoc->createElement("link");
            link.setAttribute("xconnector","onEndSetStopStart");

                QDomElement b01 = domdoc->createElement("bind");
                b01.setAttribute("role","onEnd");
                b01.setAttribute("component",chainID);
                b01.setAttribute("interface",chainID+"_"+QString::number(i));
                link.appendChild(b01);

                foreach(QnsbObject* object, chain->getDimensions().at(0)->gePanels().last()->getObjects()){
                    QDomElement b = domdoc->createElement("bind");
                    b.setAttribute("role","stop");
                    b.setAttribute("component",object->getId());
                    link.appendChild(b);
                }

                QDomElement b02 = domdoc->createElement("bind");
                b02.setAttribute("role","stop");
                b02.setAttribute("component",chainID);
                link.appendChild(b02);

            parent.appendChild(link);
        }else{
            foreach(QnsbLink* lobj, chain->getLinks()){
                QString targetID = lobj->getTarget();

                if (lobj->geteTarget()->getType() == "referencial"){
                    targetID = lobj->geteTarget()->getMatrix()->getId();
                }

                if (lobj->getType() == "sequencial"){
                    if (chain->getLinks().size() == 1){
                        QDomElement link = domdoc->createElement("link");
                        link.setAttribute("xconnector","onEndSetStopStart");

                            QDomElement b01 = domdoc->createElement("bind");
                            b01.setAttribute("role","onEnd");
                            b01.setAttribute("component",chainID);
                            b01.setAttribute("interface",chainID+"_"+QString::number(i));
                            link.appendChild(b01);

                            QDomElement b03 = domdoc->createElement("bind");
                            b03.setAttribute("role","stop");
                            b03.setAttribute("component",chainID);
                            link.appendChild(b03);

                            if (lobj->geteTarget()->getType() == "referencial"){
                                writeNCLRefActionsBind(lobj->geteTarget()->getMatrix()->getDimensions().at(0)->gePanels().at(0), link);
                            }

                            QDomElement b02 = domdoc->createElement("bind");
                            b02.setAttribute("role","start");
                            b02.setAttribute("component",targetID);
                            link.appendChild(b02);

                        parent.appendChild(link);
                    }else{
                        QDomElement link = domdoc->createElement("link");
                        link.setAttribute("xconnector","onEndTest"+QString::number(chain->getLinks().size()-1)+"SetStopStart");

                            QDomElement b01 = domdoc->createElement("bind");
                            b01.setAttribute("role","onEnd");
                            b01.setAttribute("component",chainID);
                            b01.setAttribute("interface",chainID+"_"+QString::number(i));
                            link.appendChild(b01);

                            int index = 1;

                            foreach(QnsbLink* lobj, chain->getLinks()){
                                if (lobj->getType() != "sequencial"){
                                    QDomElement b = domdoc->createElement("bind");
                                    b.setAttribute("role","test"+QString::number(index++));
                                    b.setAttribute("component",wnlinkaux[lobj->getUid()]);
                                    b.setAttribute("interface","service."+wnlinkaux[lobj->getUid()]);

                                        QDomElement bp = domdoc->createElement("bindParam");
                                        bp.setAttribute("name","value");
                                        bp.setAttribute("value","0");
                                        b.appendChild(bp);

                                    link.appendChild(b);
                                }
                            }

                            if (lobj->geteTarget()->getType() == "referencial"){
                                writeNCLRefActionsBind(lobj->geteTarget()->getMatrix()->getDimensions().at(0)->gePanels().at(0), link);
                            }

                            QDomElement b03 = domdoc->createElement("bind");
                            b03.setAttribute("role","stop");
                            b03.setAttribute("component",chainID);
                            link.appendChild(b03);

                            QDomElement b02 = domdoc->createElement("bind");
                            b02.setAttribute("role","start");
                            b02.setAttribute("component",targetID);
                            link.appendChild(b02);

                        parent.appendChild(link);
                    }

                }else if (lobj->getType() == "interactive"){
                    QDomElement link = domdoc->createElement("link");

                    if (lobj->getKey() != ""){
                        link.setAttribute("xconnector","onKeySelectionStartStopSet");

                        QDomElement b01 = domdoc->createElement("bind");
                        b01.setAttribute("role","onSelection");
                        b01.setAttribute("component",lobj->getTrigger()->getId());

                            QDomElement bp01 = domdoc->createElement("bindParam");
                            bp01.setAttribute("name","key");
                            bp01.setAttribute("value",lobj->getKey());
                            b01.appendChild(bp01);

                        link.appendChild(b01);

                        QDomElement b04 = domdoc->createElement("bind");
                        b04.setAttribute("role","set");
                        b04.setAttribute("component",wnlinkaux[lobj->getUid()]);
                        b04.setAttribute("interface","service."+wnlinkaux[lobj->getUid()]);

                            QDomElement bp02 = domdoc->createElement("bindParam");
                            bp02.setAttribute("name","var");
                            bp02.setAttribute("value","1");
                            b04.appendChild(bp02);

                        link.appendChild(b04);


                        foreach(QnsbLink* llo, chain->getLinks()){
                            if (llo->getUid() != lobj->getUid() && llo->getType() != "sequencial"){
                                QDomElement bdelta = domdoc->createElement("bind");
                                bdelta.setAttribute("role","set");
                                bdelta.setAttribute("component",wnlinkaux[llo->getUid()]);
                                bdelta.setAttribute("interface","service."+wnlinkaux[llo->getUid()]);

                                    QDomElement bpdelta = domdoc->createElement("bindParam");
                                    bpdelta.setAttribute("name","var");
                                    bpdelta.setAttribute("value","0");
                                    bdelta.appendChild(bpdelta);

                                link.appendChild(bdelta);
                            }
                        }

                        QDomElement b03 = domdoc->createElement("bind");
                        b03.setAttribute("role","stop");
                        b03.setAttribute("component",chainID);
                        link.appendChild(b03);

                        QDomElement b02 = domdoc->createElement("bind");
                        b02.setAttribute("role","start");
                        b02.setAttribute("component",targetID);
                        link.appendChild(b02);
                    }

                    parent.appendChild(link);

                }else if (lobj->getType() == "adaptative"){
                    QDomElement link0 = domdoc->createElement("link");
                    link0.setAttribute("xconnector","onBeginTestSetStopStart");

                        QDomElement b001 = domdoc->createElement("bind");
                        b001.setAttribute("role","onBegin");
                        b001.setAttribute("component",chainID);
                        b001.setAttribute("interface",chainID+"_"+QString::number(i));
                        link0.appendChild(b001);

                        QDomElement b004 = domdoc->createElement("bind");
                        b004.setAttribute("role","test");
                        b004.setAttribute("component",lobj->getTrigger()->getId());
                        b004.setAttribute("interface",lobj->getVarName());

                            QDomElement bp0 = domdoc->createElement("bindParam");
                            bp0.setAttribute("name","value");
                            bp0.setAttribute("value",lobj->getVarValue());
                            b004.appendChild(bp0);

                        link0.appendChild(b004);

                        QDomElement b005 = domdoc->createElement("bind");
                        b005.setAttribute("role","set");
                        b005.setAttribute("component",wnlinkaux[lobj->getUid()]);
                        b005.setAttribute("interface","service."+wnlinkaux[lobj->getUid()]);

                            QDomElement bp002 = domdoc->createElement("bindParam");
                            bp002.setAttribute("name","var");
                            bp002.setAttribute("value","1");
                            b005.appendChild(bp002);

                        link0.appendChild(b005);

                    parent.appendChild(link0);

                    QDomElement link = domdoc->createElement("link");
                    link.setAttribute("xconnector","onEndTestSetStopStart");

                        QDomElement b01 = domdoc->createElement("bind");
                        b01.setAttribute("role","onEnd");
                        b01.setAttribute("component",chainID);
                        b01.setAttribute("interface",chainID+"_"+QString::number(i));
                        link.appendChild(b01);

                        QDomElement b04 = domdoc->createElement("bind");
                        b04.setAttribute("role","test");
                        b04.setAttribute("component",lobj->getTrigger()->getId());
                        b04.setAttribute("interface",lobj->getVarName());

                            QDomElement bp = domdoc->createElement("bindParam");
                            bp.setAttribute("name","value");
                            bp.setAttribute("value",lobj->getVarValue());
                            b04.appendChild(bp);

                        link.appendChild(b04);

                        QDomElement b03 = domdoc->createElement("bind");
                        b03.setAttribute("role","stop");
                        b03.setAttribute("component",chainID);
                        link.appendChild(b03);

                        QDomElement b02 = domdoc->createElement("bind");
                        b02.setAttribute("role","start");
                        b02.setAttribute("component",targetID);
                        link.appendChild(b02);

                    parent.appendChild(link);
                }
            }

            foreach(QnsbLink* lobj, chain->getLinks()){
                if (lobj->geteTarget()->getType() != "referencial"){
                    foreach(QnsbDimension* dim, chain->getDimensions()){
                        if (dim->getName() == chain->getInterface()){
                            xauxpanel_last = dim->gePanels().last();
                        }
                    }

                    writeNCLLinks(lobj->geteTarget(),parent);
                }
            }
        }
    }
}

void QnsbDocument::writeNCLActionsBind(QnsbPanel* panel, QDomElement parent)
{
    if (xauxpanel_last != NULL){
        foreach(QnsbObject* object, xauxpanel_last->getObjects()){
            QnsbObject* simi = containsSimilar(panel,object);

            if (simi != NULL){
                if (!compare(simi, object)){
                    QDomElement b = domdoc->createElement("bind");
                    b.setAttribute("role","set");
                    b.setAttribute("component",object->getId());
                    b.setAttribute("interface","bounds");

                    QString btop = object->getProperty("top"); btop.remove(btop.length()-1,1);
                    QString bleft = object->getProperty("left"); bleft.remove(bleft.length()-1,1);
                    QString bwidth = object->getProperty("width"); bwidth.remove(bwidth.length()-1,1);
                    QString bheight = object->getProperty("height"); bheight.remove(bheight.length()-1,1);

                    QString ntop = simi->getProperty("top"); ntop.remove(ntop.length()-1,1);
                    QString nleft = simi->getProperty("left"); nleft.remove(nleft.length()-1,1);
                    QString nwidth = simi->getProperty("width"); nwidth.remove(nwidth.length()-1,1);
                    QString nheight = simi->getProperty("height"); nheight.remove(nheight.length()-1,1);


                    qreal rtop = 100*ntop.toDouble()/bheight.toDouble();
                    qreal rleft = 100*nleft.toDouble()/bwidth.toDouble();
                    qreal rwidth = 100*nwidth.toDouble()/bwidth.toDouble();
                    qreal rheight = 100*nheight.toDouble()/bheight.toDouble();

                    QDomElement bp = domdoc->createElement("bindParam");
                    bp.setAttribute("name","var");
                    bp.setAttribute("value",
                                    QString::number(rleft)+"%,"+
                                    QString::number(rtop)+"%,"+
                                    QString::number(rwidth)+"%,"+
                                    QString::number(rheight)+"%");

                    b.appendChild(bp);

                    parent.appendChild(b);
                }
            }else{
                QDomElement b = domdoc->createElement("bind");
                b.setAttribute("role","stop");
                b.setAttribute("component",object->getId());
                parent.appendChild(b);
            }
        }


        foreach(QnsbObject* object, panel->getObjects()){
            QnsbObject* simi = containsSimilar(xauxpanel_last,object);

            if (simi == NULL){
                QDomElement b = domdoc->createElement("bind");
                b.setAttribute("role","start");
                b.setAttribute("component",object->getId());
                parent.appendChild(b);
            }
        }

        xauxpanel_last = panel;
    }else{
        foreach(QnsbObject* object, panel->getObjects()){
            QDomElement b = domdoc->createElement("bind");
            b.setAttribute("role","start");
            b.setAttribute("component",object->getId());
            parent.appendChild(b);
        }

        xauxpanel_last = panel;
    }
}

void QnsbDocument::writeNCLRefActionsBind(QnsbPanel* panel, QDomElement parent)
{
    foreach(QnsbObject* object, xauxpanel_last->getObjects()){
        QnsbObject* simi = containsSimilar(panel,object);

        if (simi != NULL){
            if (!compare(simi, object)){
                QDomElement b = domdoc->createElement("bind");
                b.setAttribute("role","set");
                b.setAttribute("component",object->getId());
                b.setAttribute("interface","bounds");

                QString btop = object->getProperty("top"); btop.remove(btop.length()-1,1);
                QString bleft = object->getProperty("left"); bleft.remove(bleft.length()-1,1);
                QString bwidth = object->getProperty("width"); bwidth.remove(bwidth.length()-1,1);
                QString bheight = object->getProperty("height"); bheight.remove(bheight.length()-1,1);

                QString ntop = simi->getProperty("top"); ntop.remove(ntop.length()-1,1);
                QString nleft = simi->getProperty("left"); nleft.remove(nleft.length()-1,1);
                QString nwidth = simi->getProperty("width"); nwidth.remove(nwidth.length()-1,1);
                QString nheight = simi->getProperty("height"); nheight.remove(nheight.length()-1,1);


                qreal rtop = 100*ntop.toDouble()/bheight.toDouble();
                qreal rleft = 100*nleft.toDouble()/bwidth.toDouble();
                qreal rwidth = 100*nwidth.toDouble()/bwidth.toDouble();
                qreal rheight = 100*nheight.toDouble()/bheight.toDouble();

                QDomElement bp = domdoc->createElement("bindParam");
                bp.setAttribute("name","var");
                bp.setAttribute("value",
                                QString::number(rleft)+"%,"+
                                QString::number(rtop)+"%,"+
                                QString::number(rwidth)+"%,"+
                                QString::number(rheight)+"%");

                b.appendChild(bp);

                parent.appendChild(b);
            }
        }else{
            QDomElement b = domdoc->createElement("bind");
            b.setAttribute("role","stop");
            b.setAttribute("component",object->getId());
            parent.appendChild(b);
        }
    }

    foreach(QnsbObject* object, panel->getObjects()){
        QnsbObject* simi = containsSimilar(xauxpanel_last,object);

        if (simi == NULL){
            QDomElement b = domdoc->createElement("bind");
            b.setAttribute("role","start");
            b.setAttribute("component",object->getId());
            parent.appendChild(b);

            QDomElement b02 = domdoc->createElement("bind");
            b02.setAttribute("role","set");
            b02.setAttribute("component",object->getId());
            b02.setAttribute("interface","bounds");

            QnsbObject* inst = objectsInstance[object->getInstanceId()];

            QString btop = inst->getProperty("top"); btop.remove(btop.length()-1,1);
            QString bleft = inst->getProperty("left"); bleft.remove(bleft.length()-1,1);
            QString bwidth = inst->getProperty("width"); bwidth.remove(bwidth.length()-1,1);
            QString bheight = inst->getProperty("height"); bheight.remove(bheight.length()-1,1);

            QString ntop = object->getProperty("top"); ntop.remove(ntop.length()-1,1);
            QString nleft = object->getProperty("left"); nleft.remove(nleft.length()-1,1);
            QString nwidth = object->getProperty("width"); nwidth.remove(nwidth.length()-1,1);
            QString nheight = object->getProperty("height"); nheight.remove(nheight.length()-1,1);


            qreal rtop = 100*ntop.toDouble()/bheight.toDouble();
            qreal rleft = 100*nleft.toDouble()/bwidth.toDouble();
            qreal rwidth = 100*nwidth.toDouble()/bwidth.toDouble();
            qreal rheight = 100*nheight.toDouble()/bheight.toDouble();

            QDomElement bp = domdoc->createElement("bindParam");
            bp.setAttribute("name","var");
            bp.setAttribute("value",
                            QString::number(rleft)+"%,"+
                            QString::number(rtop)+"%,"+
                            QString::number(rwidth)+"%,"+
                            QString::number(rheight)+"%");

            b02.appendChild(bp);

            parent.appendChild(b02);
        }
    }
}

bool QnsbDocument::compare(QnsbObject* a, QnsbObject* b)
{
    if (a->getProperty("top") != b->getProperty("top")){
        return false;
    }

    if (a->getProperty("left") != b->getProperty("left")){
        return false;
    }

    if (a->getProperty("width") != b->getProperty("width")){
        return false;
    }

    if (a->getProperty("height") != b->getProperty("height")){
        return false;
    }

    if (a->getType() != b->getType()){
        return false;
    }

    if (a->getSrc() != b->getSrc()){
        return false;
    }

    if (a->getId() != b->getId()){
        return false;
    }

    return true;
}

QnsbObject* QnsbDocument::containsSimilar(QnsbPanel* p, QnsbObject* o)
{
    QnsbObject* oref = NULL;

    foreach(QnsbObject* obj, p->getObjects()){
        if (obj->getInstanceId() == o->getInstanceId()){
            return obj;
        }
    }

    return oref;
}
