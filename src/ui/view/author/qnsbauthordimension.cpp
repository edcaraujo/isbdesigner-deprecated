#include "qnsbauthordimension.h"

QnsbAuthorDimension::QnsbAuthorDimension(QnsbGraphicsItem* parent)
    : QnsbGraphicsDimension(parent)
{
    setTop(0);
    setLeft(0);
    setWidth(0);
    setHeight(400);

    setChain(NULL);
}

QString QnsbAuthorDimension::getName()
{
    return name;
}

void QnsbAuthorDimension::setName(QString name)
{
    this->name = name;
}

QnsbAuthorChain* QnsbAuthorDimension::getChain() const
{
    return chain;
}

void QnsbAuthorDimension::setChain(QnsbAuthorChain* chain)
{
    this->chain = chain;
}

QList<QnsbAuthorPanel*> QnsbAuthorDimension::getPanels() const
{
    return panels;
}

void QnsbAuthorDimension::addPanel(QnsbAuthorPanel* panel)
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

        panels.append(panel);

        connect(panel, SIGNAL(panelChanged(QnsbAuthorPanel*)), SIGNAL(panelChanged(QnsbAuthorPanel*)));
        connect(panel, SIGNAL(panelSelected(QnsbAuthorPanel*)), SIGNAL(panelSelected(QnsbAuthorPanel*)));

        connect(panel, SIGNAL(objectAdded(QnsbAuthorObject*)), SIGNAL(objectAdded(QnsbAuthorObject*)));
        connect(panel, SIGNAL(objectChanged(QnsbAuthorObject*)), SIGNAL(objectChanged(QnsbAuthorObject*)));
        connect(panel, SIGNAL(objectSelected(QnsbAuthorObject*)), SIGNAL(objectSelected(QnsbAuthorObject*)));

        if (panel->getBegin() == 0 && panel->getEnd() == 0){
            if (panel->getPrevious() != NULL){
                panel->setBegin(panel->getPrevious()->getEnd());
            }

            panel->setEnd(panel->getBegin()+5);

            emit panelChanged(panel);
        }

        chain->adjust();
    }
}

void QnsbAuthorDimension::removePanel(QnsbAuthorPanel* panel)
{
    if (panel != NULL){
        panels.removeOne(panel);
    }
}

QnsbAuthorDimension::~QnsbAuthorDimension()
{

}

void QnsbAuthorDimension::adjust()
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
        foreach(QnsbAuthorLink* link, getChain()->getLinks()){
            link->setTop(top);
            link->setLeft(left);

            top += 90 + 32/2;
        }
    }
}

void QnsbAuthorDimension::draw(QPainter* painter)
{
    painter->setBrush(QBrush(Qt::white));
    painter->drawRect(0,getHeight()/2 - 6/2,56 + (panels.size())*(56+56+400),6);

    if (panels.size() > 0) {
        painter->setPen(QColor("#FFFFFF"));

        if (chain->getType() == "home"){
            painter->setBrush(QBrush(Qt::white));
            painter->drawText(QRect(40,getHeight()/2 - 48/2 -24,80,32),getChain()->getId());
            painter->drawPixmap(32,getHeight()/2 - 48/2, 48, 48,QPixmap(":/icon/home2"));
        }else{
            painter->setBrush(QBrush(Qt::white));
            painter->drawText(QRect(40,getHeight()/2 - 48/2 -24,80,32),getChain()->getId());
            painter->drawPixmap(32,getHeight()/2 - 48/2, 48, 48,QPixmap(":/icon/previous2"));
        }

        for(int i=1;i < panels.size();i++){
            painter->setBrush(QBrush(Qt::white));
            painter->drawText(QRect(i*(56 + 56 + 400) + 40,getHeight()/2 - 48/2 - 24,80,32),getChain()->getId());
            painter->drawPixmap(i*(56 + 56 + 400) + 32,getHeight()/2 - 48/2, 48, 48,QPixmap(":/icon/next2"));
        }
    }

    painter->drawPixmap(56 + (panels.size())*(56+56+400) - 24,getHeight()/2 - 48/2, 48, 48,QPixmap(":/icon/addlock"));
}

void QnsbAuthorDimension::delineate(QPainterPath* painter) const
{
    if (panels.size() > 0){
        if (getChain()->getType() != "home"){
            painter->addEllipse(56 - 24,getHeight()/2 - 48/2, 48, 48);
        }
    }
}

void QnsbAuthorDimension::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    QRectF home(56 - 24,getHeight()/2 - 48/2, 48, 48);

    if (home.contains(event->pos())){
        emit chainSelected(getChain()->getPrevious());

        qreal x = getChain()->getPrevious()->getWidth();
        qreal y = getChain()->getPrevious()->getHeight()/2;

        chain->getView()->centerOn(x,y);
    }
}
