#include "qnsbnarrativeview.h"

QnsbNarrativeView::QnsbNarrativeView(QWidget* parent)
    : QnsbGraphicsView(parent)
{
    setImage(":bg/narrative/view");

    scene = new QnsbNarrativeScene(this);

    setScene(scene);

    selectedChain = NULL;
}

QnsbNarrativeView::~QnsbNarrativeView()
{

}

void QnsbNarrativeView::clean()
{

}

void QnsbNarrativeView::addChain(QString uid, QMap<QString,QString> properties)
{
//    // qDebug() << "QnsbNarrativeView::addChain()";

    if (!chains.contains(uid)){
        QnsbNarrativeChain* chain = new QnsbNarrativeChain();
        chain->setUid(uid);
        chain->setTitle(properties["id"]);
        chain->setVisible(false);

        chain->setType(properties["type"]);

        if (chains.contains(properties["matrix"])){
            chain->setMatrix(chains[properties["matrix"]]);
        }

        if (chains.size() == 0){
            scene->setHome(chain);
        }

        connect(chain, SIGNAL(chainSelected(QnsbNarrativeChain*)),SLOT(notifiesChainSelection(QnsbNarrativeChain*)));

        // TODO: Set properties.

        chains[uid] = chain;

        scene->addItem(chain);
        scene->adjust();
    }
}

void QnsbNarrativeView::removeChain(QString uid)
{

}

void QnsbNarrativeView::changeChain(QString uid, QMap<QString,QString> properties)
{
    if (chains.contains(uid)){
        QnsbNarrativeChain* chain = chains[uid];

        if (chains.contains(properties["matrix"])){
            chain->setMatrix(chains[properties["matrix"]]);
        }
    }
}

void QnsbNarrativeView::selectChain(QString uid)
{
    if (chains.contains(uid)){
        if (!chains[uid]->isSelected()){
            if (selectedChain != NULL){
                selectedChain->setSelected(false);
            }

            chains[uid]->setSelected(true);

            selectedChain = chains[uid];
        }
    }
}

void QnsbNarrativeView::addDimension(QString uid, QString parent, QMap<QString,QString> properties)
{

}

void QnsbNarrativeView::removeDimension(QString uid)
{

}

void QnsbNarrativeView::changeDimension(QString uid, QMap<QString,QString> properties)
{

}

void QnsbNarrativeView::selectDimension(QString uid)
{

}

void QnsbNarrativeView::addLink(QString uid, QString parent, QMap<QString,QString> properties)
{
    // qDebug() << "QnsbNarrativeView::addLink()";

    if (chains.contains(parent) && chains.contains(properties["targetUID"])){
        if (!links.contains(uid)){
            QnsbNarrativeChain* chain = chains.value(parent);
            QnsbNarrativeChain* target = chains.value(properties["targetUID"]);

            QnsbNarrativeLink* link = new QnsbNarrativeLink();
            link->setChain(chain);
            link->setUid(uid);
            link->setTarget(target);
            link->setZValue(-1);
            link->setType(properties["type"]);

            chain->addLink(link);

            links[uid] = link;

            scene->addItem(link);
            scene->adjust();
        }
    }
}

void QnsbNarrativeView::removeLink(QString uid)
{

}

void QnsbNarrativeView::changeLink(QString uid, QMap<QString,QString> properties)
{
    if (links.contains(uid) && chains.contains(properties["targetUID"])){
        QnsbNarrativeLink* link = links[uid];

        link->setType(properties["type"]);
        link->setKey(properties["key"]);

        link->setVarName(properties["varname"]);
        link->setOp(properties["op"]);
        link->setVarValue(properties["varvalue"]);

        link->setTarget(chains[properties["targetUID"]]);
    }
}

void QnsbNarrativeView::selectLink(QString uid)
{

}

void QnsbNarrativeView::addPanel(QString uid, QString parent, QMap<QString,QString> properties)
{

}

void QnsbNarrativeView::removePanel(QString uid)
{

}

void QnsbNarrativeView::changePanel(QString uid, QMap<QString,QString> properties)
{

}

void QnsbNarrativeView::selectPanel(QString uid)
{

}

void QnsbNarrativeView::addObject(QString uid, QString parent, QMap<QString,QString> properties)
{

}

void QnsbNarrativeView::removeObject(QString uid)
{

}

void QnsbNarrativeView::changeObject(QString uid, QMap<QString,QString> properties)
{

}

void QnsbNarrativeView::selectObject(QString uid)
{

}

void QnsbNarrativeView::notifiesChainSelection(QnsbNarrativeChain* chain)
{
    if (selectedChain != NULL){
        selectedChain->setSelected(false);
    }

    chain->setSelected(true);

    selectedChain = chain;

    scene->update();

    emit chainSelected(chain->getUid());
}

void QnsbNarrativeView::focusOnSelectedChain()
{
    if (selectedChain != NULL){
        centerOn(selectedChain);
    }
}

void QnsbNarrativeView::resizeEvent(QResizeEvent* event)
{
    QnsbGraphicsView::resizeEvent(event);

    qreal width = event->size().width();
    qreal height = event->size().height();

    scene->setMinimumWidth(width);
    scene->setMinimumHeight(height);

    scene->setWidth(width+18);
    scene->setHeight(height+18);

    scene->adjust();
}
