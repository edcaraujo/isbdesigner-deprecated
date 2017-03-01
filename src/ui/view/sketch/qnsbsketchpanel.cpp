#include "qnsbsketchpanel.h"

QnsbSketchPanel::QnsbSketchPanel(QnsbGraphicsItem* parent)
    : QnsbGraphicsPanel(parent)
{
    setIndex(0);

    setTop(0);
    setLeft(0);
    setWidth(400);
    setHeight(416);

    createActions();
    createMenus();
    createConnections();

    selected = false;

    previous = NULL;
    next = NULL;

    note = new QnsbSketchNote(this);
    note->setPlainText("type your notes here...");
    note->setY(256+32);
    note->setTextWidth(400);

    connect(note,SIGNAL(noteSelected()),SLOT(notifiesPanelSelection()));
    connect(note, SIGNAL(noteChanged()),SLOT(notifiesPanelNoteChange()));
}

QnsbSketchPanel::~QnsbSketchPanel()
{

}

QString QnsbSketchPanel::getNotes() const
{
    return notes;
}

void QnsbSketchPanel::setNotes(QString notes)
{
    this->notes = notes;

    if (notes == ""){
        note->setPlainText("type your notes here...");
    }else{
        note->setPlainText(notes);
    }
}

void QnsbSketchPanel::notifiesPanelNoteChange()
{
    setNotes(note->toPlainText());

    emit panelChanged(this);
}

void QnsbSketchPanel::notifiesPanelSelection()
{
    panelSelected(this);
}

QString QnsbSketchPanel::getTBegin() const
{
    return tbegin;
}

void QnsbSketchPanel::setTBegin(QString tbegin)
{
    this->tbegin = tbegin;
}

QString QnsbSketchPanel::getTEnd() const
{
    return tend;
}

void QnsbSketchPanel::setTEnd(QString tend)
{
    this->tend = tend;
}

QnsbSketchPanel* QnsbSketchPanel::getPrevious()
{
    return previous;
}

void QnsbSketchPanel::setPrevious(QnsbSketchPanel* previous)
{
    this->previous = previous;
}

QnsbSketchPanel* QnsbSketchPanel::getNext()
{
    return next;
}

void QnsbSketchPanel::setNext(QnsbSketchPanel* next)
{
    this->next = next;
}

QVector<QnsbSketchObject*> QnsbSketchPanel::getObjects() const
{
    return objects;
}

void QnsbSketchPanel::addObject(QnsbSketchObject* object)
{
    if (object != NULL){
        object->setParent(this);
        object->setParentItem(this);

        objects.append(object);

        connect(object, SIGNAL(objectChanged(QnsbSketchObject*)), SIGNAL(objectChanged(QnsbSketchObject*)));
        connect(object, SIGNAL(objectRemoved(QnsbSketchObject*)), SIGNAL(objectRemoved(QnsbSketchObject*)));
        connect(object, SIGNAL(objectSelected(QnsbSketchObject*)), SIGNAL(objectSelected(QnsbSketchObject*)));

        connect(object, SIGNAL(imagePeformed()), SLOT(performImage()));
        connect(object, SIGNAL(videoPeformed()), SLOT(performVideo()));
        connect(object, SIGNAL(textPeformed()), SLOT(performText()));
        connect(object, SIGNAL(audioPeformed()), SLOT(performAudio()));
        connect(object, SIGNAL(scriptPeformed()), SLOT(performScript()));

        update();
    }
}

void QnsbSketchPanel::removeObject(QnsbSketchObject* object)
{
    if (object != NULL){
        int index = objects.indexOf(object);

        if (index >= 0){
            objects.remove(index);

            getDimension()->getChain()->removeItem(object);
        }
    }
}

void QnsbSketchPanel::createActions()
{
    // video action
    videoAction = new QAction(this);
    videoAction->setText(tr("Video"));
    videoAction->setIcon(QIcon(":/icon/video"));

    videoAction->setEnabled(true);

    // image action
    imageAction = new QAction(this);
    imageAction->setText(tr("Image"));
    imageAction->setIcon(QIcon(":/icon/image"));

    imageAction->setEnabled(true);

    // text action
    textAction = new QAction(this);
    textAction->setText(tr("Text"));
    textAction->setIcon(QIcon(":/icon/text"));

    textAction->setEnabled(true);

    // audio action
    audioAction = new QAction(this);
    audioAction->setText(tr("Audio"));
    audioAction->setIcon(QIcon(":/icon/audio"));

    audioAction->setEnabled(true);

    // script action
    scriptAction = new QAction(this);
    scriptAction->setText(tr("Script"));
    scriptAction->setIcon(QIcon(":/icon/preferences"));

    scriptAction->setEnabled(true);
}

void QnsbSketchPanel::createMenus()
{
    // insert menu
    insertMenu = new QMenu();
    insertMenu->setTitle(tr("Insert"));

    insertMenu->setEnabled(true);

    insertMenu->addAction(videoAction);
    insertMenu->addAction(imageAction);
    insertMenu->addAction(textAction);
    insertMenu->addAction(audioAction);
    insertMenu->addSeparator();
    insertMenu->addAction(scriptAction);

    // context menu
    contextMenu = new QMenu();
    contextMenu->addMenu(insertMenu);
}

void QnsbSketchPanel::createConnections()
{
    connect(imageAction, SIGNAL(triggered()), SLOT(performImage()));
    connect(videoAction, SIGNAL(triggered()), SLOT(performVideo()));
    connect(textAction, SIGNAL(triggered()), SLOT(performText()));
    connect(audioAction, SIGNAL(triggered()), SLOT(performAudio()));
    connect(scriptAction, SIGNAL(triggered()), SLOT(performScript()));
}

bool QnsbSketchPanel::isSelected()
{
    return selected;
}

void QnsbSketchPanel::setSelected(bool selected)
{
    this->selected = selected;
}

int QnsbSketchPanel::getIndex()
{
    return index;
}

void QnsbSketchPanel::setIndex(int index)
{
    this->index = index;
}

QnsbSketchDimension* QnsbSketchPanel::getDimension()
{
    return dimension;
}

void QnsbSketchPanel::setDimension(QnsbSketchDimension* dimension)
{
    this->dimension = dimension;
}

void QnsbSketchPanel::adjust()
{
    setTop(dimension->getHeight()/2 - (getHeight() - 32 - 128)/2);

    setLeft(56 + 56 + index*(56 + 56 + 400));
}

void QnsbSketchPanel::draw(QPainter* painter)
{
    painter->setBrush(QBrush(Qt::white));

    if (selected){        
        painter->setPen(QPen(QBrush("#FF9900"),12,Qt::SolidLine,Qt::SquareCap,Qt::RoundJoin));

        painter->drawRect(0, 0, getWidth(), 256);
    }
    painter->setPen(QPen(QColor("#FFFFFF")));

    painter->drawText(0, 256+24, "Notes:");

    painter->setPen(Qt::NoPen);

    painter->drawRect(0, 0, getWidth(), 256);
}

void QnsbSketchPanel::delineate(QPainterPath* painter) const
{
    painter->addRect(0, 0, getWidth(), 256);
}

void QnsbSketchPanel::performImage()
{
    QnsbSketchObject* object = new QnsbSketchObject();
    object->setType("image");
    object->setPanel(this);
    object->setSelected(true);
    object->setWidth(getWidth()*0.6);
//    object->setHeight(getHeight()*0.6);
    object->setHeight(256*0.6);
//    object->setTop(getHeight()*0.2);
    object->setTop(256*0.2);
    object->setLeft(getWidth()*0.2);

    addObject(object);

    emit objectAdded(object);

    emit objectSelected(object);

    addObjectToNextPanel(object, this);
}

void QnsbSketchPanel::performVideo()
{
    QnsbSketchObject* object = new QnsbSketchObject();
    object->setType("video");
    object->setPanel(this);
    object->setSelected(true);
    object->setWidth(getWidth()*0.6);
    //    object->setHeight(getHeight()*0.6);
        object->setHeight(256*0.6);
    //    object->setTop(getHeight()*0.2);
        object->setTop(256*0.2);
    object->setLeft(getWidth()*0.2);

    addObject(object);

    emit objectAdded(object);

    emit objectSelected(object);

    addObjectToNextPanel(object, this);
}

void QnsbSketchPanel::performAudio()
{
    QnsbSketchObject* object = new QnsbSketchObject();
    object->setType("audio");
    object->setPanel(this);
    object->setSelected(true);
    object->setWidth(32+112);
    //    object->setHeight(getHeight()*0.6);
        object->setHeight(32+8);
    //    object->setTop(getHeight()*0.2);
        object->setTop(256/2 - (32+8)/2);
    object->setLeft(getWidth()/2 - (32+112)/2);

    addObject(object);

    emit objectAdded(object);

    emit objectSelected(object);

    addObjectToNextPanel(object, this);
}

void QnsbSketchPanel::performText()
{
    QnsbSketchObject* object = new QnsbSketchObject();
    object->setType("text");
    object->setPanel(this);
    object->setSelected(true);
    object->setWidth(getWidth()*0.6);
    //    object->setHeight(getHeight()*0.6);
        object->setHeight(256*0.6);
    //    object->setTop(getHeight()*0.2);
        object->setTop(256*0.2);
    object->setLeft(getWidth()*0.2);

    addObject(object);

    emit objectAdded(object);

    emit objectSelected(object);

    addObjectToNextPanel(object, this);
}

void QnsbSketchPanel::performScript()
{
    QnsbSketchObject* object = new QnsbSketchObject();
    object->setType("script");
    object->setPanel(this);
    object->setSelected(true);
    object->setWidth(getWidth()*0.6);
    //    object->setHeight(getHeight()*0.6);
        object->setHeight(256*0.6);
    //    object->setTop(getHeight()*0.2);
        object->setTop(256*0.2);
    object->setLeft(getWidth()*0.2);

    addObject(object);

    emit objectAdded(object);

    emit objectSelected(object);

    addObjectToNextPanel(object, this);
}

void QnsbSketchPanel::addObjectToNextPanel(QnsbSketchObject* reference, QnsbSketchPanel* panel)
{
    if (panel != NULL){
        if (panel->getNext() != NULL){
            QnsbSketchPanel* next = panel->getNext();

            QnsbSketchObject* nobj = new QnsbSketchObject();
            nobj->setTop(reference->getTop());
            nobj->setLeft(reference->getLeft());
            nobj->setWidth(reference->getWidth());
            nobj->setHeight(reference->getHeight());

            nobj->setPanel(next);
            nobj->setId(reference->getId());
            nobj->setType(reference->getType());
            nobj->setInstanceID(reference->getInstanceID());
            nobj->setStatusID(reference->getStatusID());

            next->addObject(nobj);

            emit objectAdded(nobj);

            addObjectToNextPanel(reference, next);
        }else{
            foreach(QnsbSketchLink* link, panel->getDimension()->getChain()->getLinks()){
                foreach(QnsbSketchDimension* dim, link->getTarget()->getDimensions()){
                    if (reference->getPanel()->getDimension()->getName() == dim->getName()){
                        QnsbSketchPanel* next = dim->getPanels().first();

                        QnsbSketchObject* nobj = new QnsbSketchObject();
                        nobj->setTop(reference->getTop());
                        nobj->setLeft(reference->getLeft());
                        nobj->setWidth(reference->getWidth());
                        nobj->setHeight(reference->getHeight());

                        nobj->setPanel(next);
                        nobj->setId(reference->getId());
                        nobj->setType(reference->getType());
                        nobj->setInstanceID(reference->getInstanceID());
                        nobj->setStatusID(reference->getStatusID());

                        next->addObject(nobj);

                        emit objectAdded(nobj);

                        addObjectToNextPanel(reference, next);
                    }
                }
            }
        }
    }
}

void QnsbSketchPanel::mousePressEvent(QGraphicsSceneMouseEvent* event){    
    if (event->button() == Qt::RightButton){
        event->ignore();

    }else if (event->button() == Qt::LeftButton){
        selected = true;

        dimension->update();

        emit panelSelected(this);
    }
}

void QnsbSketchPanel::contextMenuEvent(QGraphicsSceneContextMenuEvent* event)
{
    QnsbGraphicsItem::contextMenuEvent(event);

    if (!event->isAccepted()){
        contextMenu->exec(event->screenPos());

        event->accept();
    }
}
