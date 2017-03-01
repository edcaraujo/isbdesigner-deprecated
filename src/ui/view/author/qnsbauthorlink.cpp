#include "qnsbauthorlink.h"

QnsbAuthorLink::QnsbAuthorLink(QnsbGraphicsItem* parent)
    : QnsbGraphicsLink(parent)
{
    setTop(0);
    setLeft(0);
    setWidth(160);
    setHeight(90);

    createActions();
    createMenus();
    createConnections();

    setTrigger(NULL);

    selected = false;

    dialog = new QDialog();

    properties.setupUi(dialog);

    connect(properties.cbType,SIGNAL(currentIndexChanged(QString)),SLOT(adjustType(QString)));
    connect(properties.cbATrigger,SIGNAL(currentIndexChanged(QString)),SLOT(adjustVariable(QString)));
}

QnsbAuthorLink::~QnsbAuthorLink()
{

}

QString QnsbAuthorLink::getType() const
{
    return type;
}

void QnsbAuthorLink::setType(QString type)
{
    this->type = type;
}

bool QnsbAuthorLink::isSelected()
{
    return selected;
}

void QnsbAuthorLink::setSelected(bool selected)
{
    this->selected = selected;
}

QString QnsbAuthorLink::getVarValue() const
{
    return varvalue;
}

void QnsbAuthorLink::setVarValue(QString varvalue)
{
    this->varvalue = varvalue;
}

QString QnsbAuthorLink::getVarName() const
{
    return varname;
}

void QnsbAuthorLink::setVarName(QString varname)
{
    this->varname = varname;
}

QString QnsbAuthorLink::getOp() const
{
    return op;
}

void QnsbAuthorLink::setOp(QString op)
{
    this->op = op;
}

QString QnsbAuthorLink::getKey() const
{
    return key;
}

void QnsbAuthorLink::setKey(QString key)
{
    this->key = key;
}

QnsbAuthorChain* QnsbAuthorLink::getChain() const
{
    return chain;
}

void QnsbAuthorLink::setChain(QnsbAuthorChain* chain)
{
    this->chain = chain;
}

QnsbAuthorObject* QnsbAuthorLink::getTrigger() const
{
    return trigger;
}

void QnsbAuthorLink::setTrigger(QnsbAuthorObject* trigger)
{
    this->trigger = trigger;
}

QnsbAuthorChain* QnsbAuthorLink::getTarget() const
{
    return target;
}

void QnsbAuthorLink::setTarget(QnsbAuthorChain* target)
{
    this->target = target;
}

void QnsbAuthorLink::createActions()
{
    // video action
    propertyAction = new QAction(this);
    propertyAction->setText(tr("Properties"));

    propertyAction->setEnabled(true);
}

void QnsbAuthorLink::createMenus()
{
    // context menu
    contextMenu = new QMenu();
    contextMenu->addAction(propertyAction);
}

void QnsbAuthorLink::createConnections()
{
    connect(propertyAction, SIGNAL(triggered()), SLOT(performProperty()));
}

void QnsbAuthorLink::performProperty()
{
    if (type == "sequencial"){
        properties.cbType->setCurrentIndex(0);

    }else if (type == "interactive"){
        properties.cbType->setCurrentIndex(1);

        if (trigger != NULL){
            triggers[trigger->getId()] = trigger;

            if (trigger->getType() == "image"){
                if (trigger->getSrc() != ""){
                    properties.cbITrigger->addItem(QIcon(trigger->getSrc()),trigger->getId());
                }else{
                    properties.cbITrigger->addItem(QIcon(":/icon/image"),trigger->getId());
                }

            }else if (trigger->getType() == "video"){
                properties.cbITrigger->addItem(QIcon(":/icon/video"),trigger->getId());

            }else if (trigger->getType() == "audio"){
                properties.cbITrigger->addItem(QIcon(":/icon/audio"),trigger->getId());

            }else if (trigger->getType() == "text"){
                properties.cbITrigger->addItem(QIcon(":/icon/text"),trigger->getId());

            }else if (trigger->getType() == "script"){
                properties.cbITrigger->addItem(QIcon(":/icon/preferences"),trigger->getId());

            }

            QnsbAuthorPanel* panel = (QnsbAuthorPanel*) getChain()->getDimensions().at(0)->getPanels().last();

            foreach(QnsbAuthorObject* object, panel->getObjects()){
                if (object->getUid() != trigger->getUid()){
                    triggers[object->getId()] = object;

                    if (object->getType() == "image"){
                        if (object->getSrc() != ""){
                            properties.cbITrigger->addItem(QIcon(object->getSrc()),object->getId());
                        }else{
                            properties.cbITrigger->addItem(QIcon(":/icon/image"),object->getId());
                        }

                    }else if (object->getType() == "video"){
                        properties.cbITrigger->addItem(QIcon(":/icon/video"),object->getId());

                    }else if (object->getType() == "audio"){
                        properties.cbITrigger->addItem(QIcon(":/icon/audio"),object->getId());

                    }else if (object->getType() == "text"){
                        properties.cbITrigger->addItem(QIcon(":/icon/text"),object->getId());

                    }else if (object->getType() == "script"){
                        properties.cbITrigger->addItem(QIcon(":/icon/preferences"),object->getId());

                    }

                    properties.cbITrigger->addItem(object->getId());
                }
            }

        }else{
            QnsbAuthorPanel* panel = (QnsbAuthorPanel*) getChain()->getDimensions().at(0)->getPanels().last();

            foreach(QnsbAuthorObject* object, panel->getObjects()){
                triggers[object->getId()] = object;

                if (object->getType() == "image"){
                    if (object->getSrc() != ""){
                        properties.cbITrigger->addItem(QIcon(object->getSrc()),object->getId());
                    }else{
                        properties.cbITrigger->addItem(QIcon(":/icon/image"),object->getId());
                    }

                }else if (object->getType() == "video"){
                    properties.cbITrigger->addItem(QIcon(":/icon/video"),object->getId());

                }else if (object->getType() == "audio"){
                    properties.cbITrigger->addItem(QIcon(":/icon/audio"),object->getId());

                }else if (object->getType() == "text"){
                    properties.cbITrigger->addItem(QIcon(":/icon/text"),object->getId());

                }else if (object->getType() == "script"){
                    properties.cbITrigger->addItem(QIcon(":/icon/preferences"),object->getId());

                }
            }
        }

        if (key != ""){
            properties.cbIKey->setCurrentIndex(properties.cbIKey->findText(key));
        }

    }else if (type == "adaptative"){
        properties.cbType->setCurrentIndex(2);

        if (trigger != NULL){
            triggers[trigger->getId()] = trigger;

            if (trigger->getType() == "variable"){
                properties.cbATrigger->addItem(QIcon(":/icon/variable"),trigger->getId());
            }

            QnsbAuthorPanel* panel = (QnsbAuthorPanel*) getChain()->getDimensions().at(0)->getPanels().last();

            foreach(QnsbAuthorObject* object, panel->getObjects()){
                if (object->getUid() != trigger->getUid()){
                    triggers[object->getId()] = object;

                    if (object->getType() == "variable"){
                        properties.cbATrigger->addItem(QIcon(":/icon/variable"),object->getId());
                    }
                }
            }

        }else{
            QnsbAuthorPanel* panel = (QnsbAuthorPanel*) getChain()->getDimensions().at(0)->getPanels().last();

            foreach(QnsbAuthorObject* object, panel->getObjects()){
                triggers[object->getId()] = object;

                if (object->getType() == "variable"){
                    properties.cbATrigger->addItem(QIcon(":/icon/variable"),object->getId());
                }
            }
        }

        if (trigger != NULL){
            properties.cbAVariable->addItem(trigger->getVarName());
        }

        if (op == "eq"){
            properties.cbAOperator->setCurrentIndex(1);

        }else if (op == "ne"){
            properties.cbAOperator->setCurrentIndex(2);

        }else if (op == "gt"){
            properties.cbAOperator->setCurrentIndex(3);

        }else if (op == "lt"){
            properties.cbAOperator->setCurrentIndex(4);

        }else if (op == "gte"){
            properties.cbAOperator->setCurrentIndex(5);

        }else if (op == "lte"){
            properties.cbAOperator->setCurrentIndex(6);

        }else{
            properties.cbAOperator->setCurrentIndex(0);
        }

        if (varvalue != ""){
            properties.leAValue->setText(varvalue);
        }
    }

    if (target->getType() != "referencial"){
        targets[target->getId()] = target;

        properties.cbTarget->addItem(target->getId());

        properties.lbTarget->setEnabled(false);
        properties.cbTarget->setEnabled(false);
    }else{
        targets[target->getMatrix()->getId()] = target->getMatrix();

        properties.cbTarget->addItem(target->getMatrix()->getId());

        QnsbAuthorView* view = (QnsbAuthorView*) getChain()->getView();

        foreach(QnsbAuthorChain* chain, view->getChains().values()){
            if (chain->getType() != "referencial" && chain->getId() != target->getMatrix()->getId()){
                targets[chain->getId()] = chain;

                properties.cbTarget->addItem(chain->getId());
            }
        }

        properties.lbTarget->setEnabled(true);
        properties.cbTarget->setEnabled(true);
    }

    if (chain->getType() == "referencial"){
        properties.cbTarget->setEnabled(true);
    }

    if (dialog->exec()){
        // setting type
        QString type = properties.cbType->currentText();

        if (type == "Interactive"){
            setType("interactive");

        }else if (type == "Adaptative"){
            setType("adaptative");

        }else if (type == "Sequencial"){
            setType("sequencial");
        }

        // setting target
        QString target = properties.cbTarget->currentText();

        if (target != ""){
            setTarget(targets[target]);
        }

        // setting trigger


        if (properties.cbITrigger->currentText() != ""){
            QString trigger = properties.cbITrigger->currentText();

            setTrigger(triggers[trigger]);

        }else if (properties.cbATrigger->currentText() != ""){
            QString trigger = properties.cbATrigger->currentText();

            setTrigger(triggers[trigger]);
        }

        // setting key
        QString key = properties.cbIKey->currentText();

        if (key != "" && key != "----------"){
            setKey(key);
        }

        // setting variable
        QString variable = properties.cbAVariable->currentText();

        if (variable != ""){
            setVarName(variable);
        }

        // setting operator
        QString op = properties.cbAOperator->currentText();

        if (op != ""){
            setOp(op);
        }

        // setting value
        QString value = properties.leAValue->text();

        if (value != ""){
            setVarValue(value);
        }

        update();

        emit linkChanged(this);
    }

    targets.clear();
    triggers.clear();

    properties.cbTarget->clear();

    properties.cbITrigger->clear();
    properties.cbIKey->setCurrentIndex(0);

    properties.cbATrigger->clear();
    properties.cbAOperator->setCurrentIndex(0);
    properties.cbAVariable->clear();

    properties.leAValue->clear();
}

void QnsbAuthorLink::adjustType(QString type)
{
    if (type == "Interactive"){
        properties.gbInteractive->setEnabled(true);

        properties.gbAdaptative->setEnabled(false);

        triggers.clear();

        properties.cbITrigger->clear();
        properties.cbIKey->setCurrentIndex(0);

        properties.cbATrigger->clear();
        properties.cbAOperator->setCurrentIndex(0);
        properties.cbAVariable->clear();

        properties.leAValue->clear();

        if (trigger != NULL){
            triggers[trigger->getId()] = trigger;

            if (trigger->getType() == "image"){
                if (trigger->getSrc() != ""){
                    properties.cbITrigger->addItem(QIcon(trigger->getSrc()),trigger->getId());
                }else{
                    properties.cbITrigger->addItem(QIcon(":/icon/image"),trigger->getId());
                }

            }else if (trigger->getType() == "video"){
                properties.cbITrigger->addItem(QIcon(":/icon/video"),trigger->getId());

            }else if (trigger->getType() == "audio"){
                properties.cbITrigger->addItem(QIcon(":/icon/audio"),trigger->getId());

            }else if (trigger->getType() == "text"){
                properties.cbITrigger->addItem(QIcon(":/icon/text"),trigger->getId());

            }else if (trigger->getType() == "script"){
                properties.cbITrigger->addItem(QIcon(":/icon/preferences"),trigger->getId());

            }

            QnsbAuthorPanel* panel = (QnsbAuthorPanel*) getChain()->getDimensions().at(0)->getPanels().last();

            foreach(QnsbAuthorObject* object, panel->getObjects()){
                if (object->getUid() != trigger->getUid()){
                    triggers[object->getId()] = object;

                    if (object->getType() == "image"){
                        if (object->getSrc() != ""){
                            properties.cbITrigger->addItem(QIcon(object->getSrc()),object->getId());
                        }else{
                            properties.cbITrigger->addItem(QIcon(":/icon/image"),object->getId());
                        }

                    }else if (object->getType() == "video"){
                        properties.cbITrigger->addItem(QIcon(":/icon/video"),object->getId());

                    }else if (object->getType() == "audio"){
                        properties.cbITrigger->addItem(QIcon(":/icon/audio"),object->getId());

                    }else if (object->getType() == "text"){
                        properties.cbITrigger->addItem(QIcon(":/icon/text"),object->getId());

                    }else if (object->getType() == "script"){
                        properties.cbITrigger->addItem(QIcon(":/icon/preferences"),object->getId());

                    }
                }
            }

        }else{
            QnsbAuthorPanel* panel = (QnsbAuthorPanel*) getChain()->getDimensions().at(0)->getPanels().last();

            foreach(QnsbAuthorObject* object, panel->getObjects()){
                triggers[object->getId()] = object;

                if (object->getType() == "image"){
                    if (object->getSrc() != ""){
                        properties.cbITrigger->addItem(QIcon(object->getSrc()),object->getId());
                    }else{
                        properties.cbITrigger->addItem(QIcon(":/icon/image"),object->getId());
                    }

                }else if (object->getType() == "video"){
                    properties.cbITrigger->addItem(QIcon(":/icon/video"),object->getId());

                }else if (object->getType() == "audio"){
                    properties.cbITrigger->addItem(QIcon(":/icon/audio"),object->getId());

                }else if (object->getType() == "text"){
                    properties.cbITrigger->addItem(QIcon(":/icon/text"),object->getId());

                }else if (object->getType() == "script"){
                    properties.cbITrigger->addItem(QIcon(":/icon/preferences"),object->getId());

                }
            }
        }

        if (key != ""){
            properties.cbIKey->setCurrentIndex(properties.cbIKey->findText(key));
        }

    }else if (type == "Adaptative"){
        properties.gbAdaptative->setEnabled(true);

        properties.gbInteractive->setEnabled(false);

        triggers.clear();

        properties.cbITrigger->clear();
        properties.cbIKey->setCurrentIndex(0);

        properties.cbATrigger->clear();
        properties.cbAOperator->setCurrentIndex(0);
        properties.cbAVariable->clear();

        properties.leAValue->clear();

        if (trigger != NULL){
            if (trigger->getType() == "variable"){
                triggers[trigger->getId()] = trigger;

                properties.cbATrigger->addItem(QIcon(":/icon/variable"),trigger->getId());
            }

            QnsbAuthorPanel* panel = (QnsbAuthorPanel*) getChain()->getDimensions().at(0)->getPanels().last();

            foreach(QnsbAuthorObject* object, panel->getObjects()){
                if (object->getUid() != trigger->getUid()){
                    if (object->getType() == "variable"){
                        triggers[object->getId()] = object;

                        properties.cbATrigger->addItem(QIcon(":/icon/variable"),object->getId());
                    }
                }
            }

        }else{
            QnsbAuthorPanel* panel = (QnsbAuthorPanel*) getChain()->getDimensions().at(0)->getPanels().last();

            foreach(QnsbAuthorObject* object, panel->getObjects()){
                if (object->getType() == "variable"){
                    triggers[object->getId()] = object;

                    properties.cbATrigger->addItem(QIcon(":/icon/variable"),object->getId());
                }
            }
        }

        if (trigger != NULL){
            properties.cbAVariable->addItem(trigger->getVarName());

        }else{
            if (triggers.size() > 0){
                properties.cbAVariable->addItem(triggers.begin().value()->getVarName());
            }
        }

        if (op == "eq"){
            properties.cbAOperator->setCurrentIndex(1);

        }else if (op == "ne"){
            properties.cbAOperator->setCurrentIndex(2);

        }else if (op == "gt"){
            properties.cbAOperator->setCurrentIndex(3);

        }else if (op == "lt"){
            properties.cbAOperator->setCurrentIndex(4);

        }else if (op == "gte"){
            properties.cbAOperator->setCurrentIndex(5);

        }else if (op == "lte"){
            properties.cbAOperator->setCurrentIndex(6);
        }

        if (varvalue != ""){
            properties.leAValue->setText(varvalue);
        }

    }else if (type == "Sequencial"){
        properties.gbAdaptative->setEnabled(false);

        properties.gbInteractive->setEnabled(false);

        triggers.clear();

        properties.cbITrigger->clear();
        properties.cbIKey->setCurrentIndex(0);

        properties.cbATrigger->clear();
        properties.cbAOperator->setCurrentIndex(0);
        properties.cbAVariable->clear();

        properties.leAValue->clear();
    }
}

void QnsbAuthorLink::adjustVariable(QString variable)
{
    if (variable != ""){
        if (triggers[variable]->getVarName() != ""){
            properties.cbAVariable->addItem(triggers[variable]->getVarName());
        }

        if (triggers[variable]->getVarValue() != ""){
            properties.leAValue->setText(triggers[variable]->getVarValue());
        }
    }
}

void QnsbAuthorLink::adjust()
{

}

void QnsbAuthorLink::draw(QPainter* painter)
{
    painter->setBrush(QBrush(Qt::white));
    painter->drawRect(24/2,getHeight()/2 - 6/2,56, 6);

    if (selected){
        painter->setPen(QPen(QBrush(QColor("#FF9900")),2));
        painter->drawRect(24/2,getHeight()/2 - 6/2,56, 6);

        painter->setPen(QPen(QBrush(QColor("#FF9900")),5));
        painter->drawEllipse(0,getHeight()/2 - 24/2,24,24);
        painter->drawEllipse(24/2 + 56 - 48/2,getHeight()/2 - 48/2,48,48);
    }

    if (target->getType() == "linear"){
        painter->drawPixmap(24/2 + 56 - 48/2,getHeight()/2 - 48/2,48,48,QPixmap(":/icon/nalter"));

    }else if (target->getType() == "distributive"){
        painter->drawPixmap(24/2 + 56 - 48/2,getHeight()/2 - 48/2,48,48,QPixmap(":/icon/ndist"));

    }else if (target->getType() == "referencial"){
        painter->drawPixmap(24/2 + 56 - 48/2,getHeight()/2 - 48/2,48,48,QPixmap(":/icon/nref"));
    }

    if (type == "interactive"){
        painter->drawPixmap(0,getHeight()/2 - 24/2,24,24,QPixmap(":/icon/miniint"));

    }else if (type == "adaptative"){
        painter->drawPixmap(0,getHeight()/2 - 24/2,24,24,QPixmap(":/icon/miniadp"));

    }else if (type == "sequencial"){
        painter->drawPixmap(0,getHeight()/2 - 24/2,24,24,QPixmap(":/icon/mininext"));
    }

    painter->setPen(QColor("#FFFFFF"));

    if (target->getType() != "referencial"){
        painter->drawText(QRect(24/2 + 56 - 48/2 + 8,getHeight()/2 - 48/2 - 24,64,24),target->getId());
    }else{
        painter->drawText(QRect(24/2 + 56 - 48/2 + 8,getHeight()/2 - 48/2 - 24,64,24),target->getMatrix()->getId());
    }
}

void QnsbAuthorLink::delineate(QPainterPath* painter) const
{
    painter->addRect(0,0,getWidth(), getHeight());
}

void QnsbAuthorLink::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    QnsbGraphicsLink::mousePressEvent(event);

    if (!event->isAccepted()){
        if (event->button() == Qt::LeftButton){
            setSelected(true);

            emit linkSelected(this);
        }
    }
}

void QnsbAuthorLink::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
{
    if (event->button() == Qt::LeftButton){
        if (target->getType() != "referencial"){
            emit chainSelected(target);

            target->getView()->centerOn(0,target->getHeight()/2);
        }else{
            emit chainSelected(target->getMatrix());

            target->getMatrix()->getView()->centerOn(0,target->getMatrix()->getHeight()/2);
        }
    }

    QnsbGraphicsLink::mouseDoubleClickEvent(event);
}

void QnsbAuthorLink::contextMenuEvent(QGraphicsSceneContextMenuEvent* event)
{
    QnsbGraphicsItem::contextMenuEvent(event);

    if (!event->isAccepted()){
        contextMenu->exec(event->screenPos());

        event->accept();
    }
}
