#include "qnsbauthorpanel.h"

QnsbAuthorPanel::QnsbAuthorPanel(QnsbGraphicsItem* parent)
    : QnsbGraphicsPanel(parent)
{
    setNext(NULL);
    setPrevious(NULL);
    setDimension(NULL);

    notes = "";

    selected = false;

    setTop(0);
    setLeft(0);
    setWidth(400);
    setHeight(320);

    setIndex(0);

    createActions();
    createMenus();
    createConnections();

    beginItem = new QnsbAuthorText(this);
    beginItem->setY(0);
    beginItem->setX(0);
    beginItem->setTextWidth(64);
    beginItem->setPlainText("0.00s");

    connect(beginItem, SIGNAL(textSelected()),SLOT(notifiesPanelSelection()));
    connect(beginItem, SIGNAL(textChanged()), SLOT(notifiesPanelTimeChange()));

    endItem = new QnsbAuthorText(this);
    endItem->setY(0);
    endItem->setX(400-64);
    endItem->setTextWidth(64);
    endItem->setPlainText("0.00s");

    connect(endItem, SIGNAL(textSelected()),SLOT(notifiesPanelSelection()));
    connect(endItem, SIGNAL(textChanged()), SLOT(notifiesPanelTimeChange()));
}

QnsbAuthorPanel::~QnsbAuthorPanel()
{

}

int QnsbAuthorPanel::getIndex()
{
    return index;
}

void QnsbAuthorPanel::setIndex(int index)
{
    this->index = index;
}

bool QnsbAuthorPanel::isSelected()
{
    return selected;
}

void QnsbAuthorPanel::setSelected(bool selected)
{
    this->selected = selected;
}

qreal QnsbAuthorPanel::getBegin() const
{
    return begin;
}

void QnsbAuthorPanel::setBegin(qreal begin)
{
    this->begin = begin;

    beginItem->setPlainText(QString::number(begin,'f', 2)+"s");
}

qreal QnsbAuthorPanel::getEnd() const
{
    return end;
}

void QnsbAuthorPanel::setEnd(qreal end)
{
    this->end = end;

    endItem->setPlainText(QString::number(end,'f', 2)+"s");
}

QString QnsbAuthorPanel::getNotes() const
{
    return notes;
}

void QnsbAuthorPanel::setNotes(QString notes)
{
    this->notes = notes;
}

QnsbAuthorPanel* QnsbAuthorPanel::getNext() const
{
    return next;
}

void QnsbAuthorPanel::setNext(QnsbAuthorPanel* next)
{
    this->next = next;
}

QnsbAuthorPanel* QnsbAuthorPanel::getPrevious() const
{
    return previous;
}

void QnsbAuthorPanel::setPrevious(QnsbAuthorPanel* previous)
{
    this->previous = previous;
}

QnsbAuthorDimension* QnsbAuthorPanel::getDimension() const
{
    return dimension;
}

void QnsbAuthorPanel::setDimension(QnsbAuthorDimension* dimension)
{
    this->dimension = dimension;
}

QVector<QnsbAuthorObject*> QnsbAuthorPanel::getObjects() const
{
    return objects;
}

void QnsbAuthorPanel::addObject(QnsbAuthorObject* object)
{
    if (object != NULL){
        object->setParent(this);
        object->setParentItem(this);

        objects.append(object);

        connect(object, SIGNAL(objectChanged(QnsbAuthorObject*)), SIGNAL(objectChanged(QnsbAuthorObject*)));
        connect(object, SIGNAL(objectSelected(QnsbAuthorObject*)), SIGNAL(objectSelected(QnsbAuthorObject*)));

        connect(object, SIGNAL(variablePerformed()), SLOT(performVariable()));

        update();
    }
}

void QnsbAuthorPanel::removeObject(QnsbAuthorObject* object)
{
    if (object != NULL){
        int index = objects.indexOf(object);

        if (index >= 0){
            objects.remove(index);

            getDimension()->getChain()->removeItem(object);
        }
    }
}

void QnsbAuthorPanel::notifiesPanelSelection()
{
    emit panelSelected(this);
}

void QnsbAuthorPanel::notifiesPanelTimeChange()
{
    QString attribute;

    attribute = beginItem->toPlainText(); attribute.remove(attribute.length()-1,1);
    begin = attribute.toDouble();

    attribute = endItem->toPlainText(); attribute.remove(attribute.length()-1,1);
    end = attribute.toDouble();

    emit panelChanged(this);
}

void QnsbAuthorPanel::adjust()
{
    setTop(dimension->getHeight()/2 - (getHeight() - 64)/2 - 32);

    setLeft(56 + 56 + index*(56 + 56 + 400));
}

void QnsbAuthorPanel::createActions()
{
    // variable action
    variableAction = new QAction(this);
    variableAction->setText(tr("Variable"));
    variableAction->setIcon(QIcon(":/icon/variable"));

    variableAction->setEnabled(true);
}

void QnsbAuthorPanel::createMenus()
{
    // insert menu
    insertMenu = new QMenu();
    insertMenu->setTitle("Insert");
    insertMenu->addAction(variableAction);

    // context menu
    contextMenu = new QMenu();
    contextMenu->addMenu(insertMenu);
}

void QnsbAuthorPanel::createConnections()
{
    connect(variableAction, SIGNAL(triggered()), SLOT(performVariable()));
}

void QnsbAuthorPanel::addObjectToNextPanel(QnsbAuthorObject* reference, QnsbAuthorPanel* panel)
{
    if (panel != NULL){
        if (panel->getNext() != NULL){
            QnsbAuthorPanel* next = panel->getNext();

            QnsbAuthorObject* nobj = new QnsbAuthorObject();
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
            foreach(QnsbAuthorLink* link, panel->getDimension()->getChain()->getLinks()){

                // this works because referencial chains doesnt have any dimension.
                foreach(QnsbAuthorDimension* dim, link->getTarget()->getDimensions()){
                    if (reference->getPanel()->getDimension()->getName() == dim->getName()){
                        QnsbAuthorPanel* next = dim->getPanels().first();

                        QnsbAuthorObject* nobj = new QnsbAuthorObject();
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

void QnsbAuthorPanel::performVariable()
{
    QnsbAuthorObject* object = new QnsbAuthorObject();
    object->setType("variable");
    object->setPanel(this);
    object->setSelected(true);
    object->setWidth(32+124);
    //    object->setHeight(getHeight()*0.6);
    object->setHeight(32+8);
    //    object->setTop(getHeight()*0.2);
    object->setTop(32 + 256/2 - (32+8)/2);
    object->setLeft(getWidth()/2 - (32+124)/2);

    addObject(object);

    emit objectAdded(object);

    emit objectSelected(object);

    addObjectToNextPanel(object, this);
}

void QnsbAuthorPanel::draw(QPainter* painter)
{
    painter->setBrush(QBrush(Qt::white));

    if (selected){
        painter->setPen(QPen(QBrush("#FF9900"),12,Qt::SolidLine,Qt::SquareCap,Qt::RoundJoin));

        painter->drawRect(0, 32, getWidth(), 256);
    }

    painter->setPen(Qt::NoPen);

    painter->drawRect(0, 32, getWidth(), 256);

//    painter->setPen(QColor("#FFFFFF"));

//    painter->drawText(0,16,"0s");

//    painter->drawText(400-32,16,"5s");
}

void QnsbAuthorPanel::delineate(QPainterPath* painter) const
{
    painter->addRect(0,32,400,256);
}

void QnsbAuthorPanel::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (event->button() == Qt::RightButton){
        event->ignore();

    }else if (event->button() == Qt::LeftButton){
        selected = true;

        dimension->update();

        emit panelSelected(this);
    }
}

void QnsbAuthorPanel::contextMenuEvent(QGraphicsSceneContextMenuEvent* event)
{
    QnsbGraphicsItem::contextMenuEvent(event);

    if (!event->isAccepted()){
        contextMenu->exec(event->screenPos());

        event->accept();
    }
}
