#include "qnsbsketchdimension.h"

QnsbSketchDimension::QnsbSketchDimension(QnsbGraphicsItem* parent)
    : QnsbGraphicsDimension(parent)
{
    setTop(0);
    setLeft(0);
    setWidth(0);
    setHeight(400);

    iselected = false;

    lock = false;

    name = "";

    d = new QDialog();

    targerForm.setupUi(d);
}

QnsbSketchDimension::~QnsbSketchDimension()
{

}

QString QnsbSketchDimension::getName()
{
    return name;
}

void QnsbSketchDimension::setName(QString name)
{
    this->name = name;
}

QnsbSketchChain* QnsbSketchDimension::getChain() const
{
    return chain;
}

void QnsbSketchDimension::setChain(QnsbSketchChain* chain)
{
    this->chain = chain;
}

QList<QnsbSketchPanel*> QnsbSketchDimension::getPanels() const
{
    return panels;
}

void QnsbSketchDimension::addPanel(QnsbSketchPanel* panel)
{
    if (panel != NULL){
        panel->setIndex(panels.size());
        panel->setParentItem(this);

        if (!panels.isEmpty()){
            panel->setPrevious(panels.last());
        }

        if (!panels.isEmpty()){
            panels.last()->setNext(panel);
        }

        panel->adjust();

        connect(panel,SIGNAL(panelSelected(QnsbSketchPanel*)),SIGNAL(panelSelected(QnsbSketchPanel*)));
        connect(panel,SIGNAL(panelChanged(QnsbSketchPanel*)),SIGNAL(panelChanged(QnsbSketchPanel*)));

        connect(panel, SIGNAL(objectAdded(QnsbSketchObject*)), SIGNAL(objectAdded(QnsbSketchObject*)));
        connect(panel, SIGNAL(objectRemoved(QnsbSketchObject*)), SIGNAL(objectRemoved(QnsbSketchObject*)));
        connect(panel, SIGNAL(objectChanged(QnsbSketchObject*)), SIGNAL(objectChanged(QnsbSketchObject*)));
        connect(panel, SIGNAL(objectSelected(QnsbSketchObject*)), SIGNAL(objectSelected(QnsbSketchObject*)));

        panels.append(panel);



        chain->adjust();
    }
}

void QnsbSketchDimension::removePanel(QnsbSketchPanel* panel)
{
    if (panel != NULL){
        panels.removeOne(panel);
    }
}

void QnsbSketchDimension::setLock(bool lock)
{
    this->lock = lock;
}

void QnsbSketchDimension::adjust()
{
    setWidth(chain->getWidth());

    int n = getChain()->getLinks().size();

    qreal left = 56 + (panels.size())*(56+56+400) + 56 + 56;
    qreal top;

    if (n > 1){
       top = getTop() + getHeight()/2 - n*(90 + 32)/2 + (n-1)*16;
    }else{
       top = getTop() + getHeight()/2 - 90/2;
    }

    if (chain->getInterface() == this){
        foreach(QnsbSketchLink* link, getChain()->getLinks()){
            link->setTop(top);
            link->setLeft(left);

            top += 90 + 32/2;
        }
    }
}

void QnsbSketchDimension::draw(QPainter* painter)
{
    painter->setBrush(QBrush(Qt::white));
    painter->drawRect(0,getHeight()/2 - 6/2,56 + (panels.size())*(56+56+400),6);

    if (panels.size() > 0) {
        painter->setPen(QColor("#FFFFFF"));

        if (chain->getType() == "home"){
            painter->setBrush(QBrush(Qt::white));
            painter->drawText(QRect(40,getHeight()/2 - 48/2 -24,80,32),getChain()->getTitle());
            painter->drawPixmap(32,getHeight()/2 - 48/2, 48, 48,QPixmap(":/icon/home2"));
        }else{
            painter->setBrush(QBrush(Qt::white));
            painter->drawText(QRect(40,getHeight()/2 - 48/2 -24,80,32),getChain()->getTitle());
            painter->drawPixmap(32,getHeight()/2 - 48/2, 48, 48,QPixmap(":/icon/previous2"));
        }

        for(int i=1;i < panels.size();i++){
            painter->setBrush(QBrush(Qt::white));
            painter->drawRect(i*(56 + 56) + (i-1)*400,400/2 - 256/2,400,256);
            painter->drawText(QRect(i*(56 + 56 + 400) + 40,getHeight()/2 - 48/2 - 24,80,32),getChain()->getTitle());
            painter->drawPixmap(i*(56 + 56 + 400) + 32,getHeight()/2 - 48/2, 48, 48,QPixmap(":/icon/next2"));
        }
    }

    if (!iselected){
//        painter->setPen(QPen(QBrush(Qt::white),3));
//        painter->drawLine(56 + (panels.size())*(56+56+400),getHeight()/2,
//                          56 + (panels.size())*(56+56+400) + 26,getHeight()/2 + 42);

        if (getChain()->getInterface() != this && panels.size() == getChain()->getInterface()->getPanels().size()){
            painter->drawPixmap(56 + (panels.size())*(56+56+400) - 24,getHeight()/2 - 48/2, 48, 48,QPixmap(":/icon/addlock"));
        }else{
            painter->drawPixmap(56 + (panels.size())*(56+56+400) - 24,getHeight()/2 - 48/2, 48, 48,QPixmap(":/icon/add"));
        }


//        if (!lock){
//            painter->drawPixmap(56 + (panels.size())*(56+56+400) - 12 + 26,getHeight()/2 - 24/2 + 42, 24, 24,QPixmap(":/icon/addi"));
//        }else{
//            painter->drawPixmap(56 + (panels.size())*(56+56+400) - 12 + 26,getHeight()/2 - 24/2 + 42, 24, 24,QPixmap(":/icon/iaddlock"));
//        }
    }else{
        painter->setPen(QPen(QBrush(Qt::white),3));
//        painter->drawLine(56 + (panels.size())*(56+56+400),getHeight()/2,
//                          56 + (panels.size())*(56+56+400) - 26,getHeight()/2 + 42);

        painter->drawPixmap(56 + (panels.size())*(56+56+400) - 24,getHeight()/2 - 48/2, 48, 48,QPixmap(":/icon/addselected"));
//        painter->drawPixmap(56 + (panels.size())*(56+56+400) - 12 - 26,getHeight()/2 - 24/2 + 42, 24, 24,QPixmap(":/icon/addisel"));

        painter->drawPixmap(56 + (panels.size())*(56+56+400) - 24 - 0,getHeight()/2 - 48/2 - 72, 48, 48,QPixmap(":/icon/seq"));
        painter->drawPixmap(56 + (panels.size())*(56+56+400) - 24 + 64,getHeight()/2 - 48/2 - 32, 48, 48,QPixmap(":/icon/alter"));
        painter->drawPixmap(56 + (panels.size())*(56+56+400) - 24 + 64,getHeight()/2 - 48/2 + 32, 48, 48,QPixmap(":/icon/dist"));
        painter->drawPixmap(56 + (panels.size())*(56+56+400) - 24 - 0,getHeight()/2 - 48/2 + 72, 48, 48,QPixmap(":/icon/ref"));
    }
}

void QnsbSketchDimension::delineate(QPainterPath* painter) const
{
    if ((getChain()->getInterface() == this) || (getChain()->getInterface() != this && panels.size() != getChain()->getInterface()->getPanels().size())){
        painter->addEllipse(56 + (panels.size())*(56+56+400) - 24,getHeight()/2 - 48/2, 48, 48);
    }


    if (iselected){
//        painter->addEllipse(56 + (panels.size())*(56+56+400) - 12 - 26,getHeight()/2 - 24/2 + 42, 24, 24);

        painter->addEllipse(56 + (panels.size())*(56+56+400) - 24 - 0,getHeight()/2 - 48/2 - 72, 48, 48);
        painter->addEllipse(56 + (panels.size())*(56+56+400) - 24 + 64,getHeight()/2 - 48/2 - 32, 48, 48);
        painter->addEllipse(56 + (panels.size())*(56+56+400) - 24 + 64,getHeight()/2 - 48/2 + 32, 48, 48);
        painter->addEllipse(56 + (panels.size())*(56+56+400) - 24 + 0,getHeight()/2 - 48/2 + 72, 48, 48);
    }else{

//        if (!lock){
//            painter->addEllipse(56 + (panels.size())*(56+56+400) - 12 + 26,getHeight()/2 - 24/2 + 42, 24, 24);
//        }
    }

    if (panels.size() > 0){
        if (getChain()->getType() != "home" ){
            painter->addEllipse(56 - 24,getHeight()/2 - 48/2, 48, 48);
        }
    }
}

void QnsbSketchDimension::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    QRectF add(56 + (panels.size())*(56+56+400) - 24,getHeight()/2 - 48/2, 48, 48);

    QRectF pan(56 + (panels.size())*(56+56+400) - 24 - 0,getHeight()/2 - 48/2 - 72, 48, 48);
    QRectF seq(56 + (panels.size())*(56+56+400) - 24 + 64,getHeight()/2 - 48/2 - 32, 48, 48);
    QRectF dist(56 + (panels.size())*(56+56+400) - 24 + 64,getHeight()/2 - 48/2 + 32, 48, 48);
    QRectF ref(56 + (panels.size())*(56+56+400) - 24 + 0,getHeight()/2 - 48/2 + 72, 48, 48);

    QRectF home(56 - 24,getHeight()/2 - 48/2, 48, 48);

    if (add.contains(event->pos())){
        if (iselected){
            iselected = false;
        }else{
            iselected = true;
        }

    }else if (pan.contains(event->pos())){
        QnsbSketchPanel* lastpanel = panels.last();

        QnsbSketchPanel* panel = new QnsbSketchPanel(this);
        panel->setDimension(this);

        addPanel(panel);

        emit panelAdded(panel);

        emit panelSelected(panel);

        if (lastpanel != NULL){
            foreach(QnsbSketchObject* obj, lastpanel->getObjects()){
                QnsbSketchObject* nobj = new QnsbSketchObject();
                nobj->setTop(obj->getTop());
                nobj->setLeft(obj->getLeft());
                nobj->setWidth(obj->getWidth());
                nobj->setHeight(obj->getHeight());

                nobj->setPanel(panel);
                nobj->setId(obj->getId());
                nobj->setType(obj->getType());
                nobj->setInstanceID(obj->getInstanceID());
                nobj->setStatusID(obj->getStatusID());
                nobj->setSrc(obj->getSrc());
                nobj->setSketch(obj->getSketch());
                nobj->setPreview(obj->getPreview());

                panel->addObject(nobj);

                emit objectAdded(nobj);
            }
        }

        iselected = false;

    }else if (seq.contains(event->pos())){
        if (chain->getInterface() != this){
            chain->setInterface(this);

            emit chainChange(chain);
        }

        QnsbSketchChain* chain = new QnsbSketchChain();
        chain->setPrevious(getChain());
        chain->setMinimumWidth(getChain()->getMinimumWidth());
        chain->setMinimumHeight(getChain()->getMinimumHeight());
        chain->setWidth(getChain()->getMinimumWidth());
        chain->setHeight(getChain()->getMinimumHeight());

        int nnn = 0;

        foreach (QnsbSketchDimension* dim, getChain()->getDimensions()){
            if (dim->getPanels().size() == panels.size()){
                nnn++;
            }
        }

        if (nnn == 1){
            chain->setType("linear");

        }else{
            chain->setType("distributive");
        }

        emit chainAdded(chain);

        foreach (QnsbSketchDimension* dim, getChain()->getDimensions()){
            if (dim->getPanels().size() == panels.size()){
                QnsbSketchDimension* dimension = new QnsbSketchDimension();
                dimension->setChain(chain);
                dimension->adjust();

                chain->addDimension(dimension);

                emit dimensionAdded(dimension);

                QnsbSketchPanel* panel = new QnsbSketchPanel(dimension);
                panel->setDimension(dimension);

                dimension->addPanel(panel);

                emit panelAdded(panel);

                QnsbSketchPanel* lastpanel = dim->getPanels().last();

                if (lastpanel != NULL){

                    foreach(QnsbSketchObject* obj, lastpanel->getObjects()){
                        QnsbSketchObject* nobj = new QnsbSketchObject();
                        nobj->setTop(obj->getTop());
                        nobj->setLeft(obj->getLeft());
                        nobj->setWidth(obj->getWidth());
                        nobj->setHeight(obj->getHeight());

                        nobj->setPanel(panel);
                        nobj->setId(obj->getId());
                        nobj->setType(obj->getType());
                        nobj->setInstanceID(obj->getInstanceID());
                        nobj->setStatusID(obj->getStatusID());
                        nobj->setSrc(obj->getSrc());
                        nobj->setSketch(obj->getSketch());
                        nobj->setPreview(obj->getPreview());

                        panel->addObject(nobj);

                        emit objectAdded(nobj);
                    }
                }
            }
        }

        QnsbSketchLink* link = new QnsbSketchLink();
        link->setChain(getChain());
        link->setType("sequencial");
        link->setTarget(chain);
        link->adjust();

        getChain()->addLink(link);

        emit linkAdded(link);

        iselected = false;

        adjust();

        foreach (QnsbSketchDimension* dim, getChain()->getDimensions()){
            if (dim != this){
                dim->setLock(true);
            }
        }

        iselected = false;
    }else if(dist.contains(event->pos())){
        if (chain->getInterface() != this){
            chain->setInterface(this);

            emit chainChange(chain);
        }

        QnsbSketchChain* chain = new QnsbSketchChain();
        chain->setPrevious(getChain());
        chain->setMinimumWidth(getChain()->getMinimumWidth());
        chain->setMinimumHeight(getChain()->getMinimumHeight());
        chain->setWidth(getChain()->getMinimumWidth());
        chain->setHeight(getChain()->getMinimumHeight());
        chain->setType("distributive");

        emit chainAdded(chain);

        for (int i=0;i<getChain()->getDimensions().size();i++){
            QnsbSketchDimension* dimension = new QnsbSketchDimension();
            dimension->setChain(chain);
            dimension->adjust();

            chain->addDimension(dimension);

            emit dimensionAdded(dimension);

            QnsbSketchPanel* panel = new QnsbSketchPanel(dimension);
            panel->setDimension(dimension);

            dimension->addPanel(panel);

            emit panelAdded(panel);

            QnsbSketchPanel* lastpanel = getChain()->getDimensions().at(i)->getPanels().last();

            if (lastpanel != NULL){

                foreach(QnsbSketchObject* obj, lastpanel->getObjects()){
                    QnsbSketchObject* nobj = new QnsbSketchObject();
                    nobj->setTop(obj->getTop());
                    nobj->setLeft(obj->getLeft());
                    nobj->setWidth(obj->getWidth());
                    nobj->setHeight(obj->getHeight());

                    nobj->setPanel(panel);
                    nobj->setId(obj->getId());
                    nobj->setType(obj->getType());
                    nobj->setInstanceID(obj->getInstanceID());
                    nobj->setStatusID(obj->getStatusID());
                    nobj->setSrc(obj->getSrc());
                    nobj->setSketch(obj->getSketch());
                    nobj->setPreview(obj->getPreview());

                    panel->addObject(nobj);

                    emit objectAdded(nobj);
                }
            }
        }


        QnsbSketchDimension* dimension = new QnsbSketchDimension();
        dimension->setChain(chain);
        dimension->adjust();

        chain->addDimension(dimension);

        emit dimensionAdded(dimension);

        QnsbSketchPanel* panel = new QnsbSketchPanel(dimension);
        panel->setDimension(dimension);

        dimension->addPanel(panel);

        emit panelAdded(panel);

        QnsbSketchLink* link = new QnsbSketchLink();
        link->setChain(getChain());
        link->setType("sequencial");
        link->setTarget(chain);
        link->adjust();

        getChain()->addLink(link);

        emit linkAdded(link);

        iselected = false;

        adjust();

        iselected = false;

    }else if (home.contains(event->pos())){
        if (getChain()->getType() != "home"){
            emit chainSelected(getChain()->getPrevious());

            qreal x = getChain()->getPrevious()->getWidth();
            qreal y = getChain()->getPrevious()->getHeight()/2;

            chain->getView()->centerOn(x,y);
        }

        iselected = false;

    }else if(ref.contains(event->pos())){

        QMap<QString, QnsbSketchChain*> targets;

        QnsbSketchView* view = (QnsbSketchView*) chain->getView();

        foreach(QnsbSketchChain* chain, view->getChains().values()){
            targets[chain->getTitle()] = chain;

            if (chain->getType() == "home"){
                targerForm.cbTarget->addItem(QIcon(":/icon/home2"), chain->getTitle());

            }else if (chain->getType() == "linear"){
                targerForm.cbTarget->addItem(QIcon(":/icon/nseq"), chain->getTitle());

            }else if (chain->getType() == "distributive"){
                targerForm.cbTarget->addItem(QIcon(":/icon/ndist"), chain->getTitle());

            }else if (chain->getType() == "referencial"){
                targerForm.cbTarget->addItem(QIcon(":/icon/nref"), chain->getTitle());
            }
        }

        if (d->exec()){
            if (chain->getInterface() != this){
                chain->setInterface(this);

                emit chainChange(chain);
            }

            iselected = false;

            QnsbSketchChain* chain = new QnsbSketchChain();
            chain->setPrevious(getChain());
            chain->setMinimumWidth(getChain()->getMinimumWidth());
            chain->setMinimumHeight(getChain()->getMinimumHeight());
            chain->setWidth(getChain()->getMinimumWidth());
            chain->setHeight(getChain()->getMinimumHeight());
            chain->setType("referencial");
            chain->setMatrix(targets[targerForm.cbTarget->currentText()]);

            emit chainAdded(chain);

            QnsbSketchLink* link = new QnsbSketchLink();
            link->setChain(getChain());
            link->setType("sequencial");
            link->setTarget(chain);
            link->adjust();

            getChain()->addLink(link);

            emit linkAdded(link);

            adjust();
        }

        targets.clear();

        targerForm.cbTarget->clear();

        iselected = false;
    }

    update();
}

