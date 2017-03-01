#include "qnsbnarrativechain.h"

QnsbNarrativeChain::QnsbNarrativeChain(QnsbGraphicsItem* parent)
    : QnsbGraphicsItem(parent)
{
    setTop(0);
    setLeft(0);
    setHeight(80);
    setWidth(60);

    matrix = NULL;

    selected = false;
}

QnsbNarrativeChain::~QnsbNarrativeChain()
{

}

bool QnsbNarrativeChain::isSelected()
{
    return selected;
}

void QnsbNarrativeChain::setSelected(bool selected)
{
    this->selected = selected;
}

QnsbNarrativeChain* QnsbNarrativeChain::getMatrix()
{
    return matrix;
}

void QnsbNarrativeChain::setMatrix(QnsbNarrativeChain* matrix)
{
    this->matrix = matrix;
}

QString QnsbNarrativeChain::getType()
{
    return type;
}

void QnsbNarrativeChain::setType(QString type)
{
    this->type = type;
}

QString QnsbNarrativeChain::getTitle() const
{
    return title;
}

void QnsbNarrativeChain::setTitle(QString title)
{
    this->title = title;
}

QVector<QnsbNarrativeLink*> QnsbNarrativeChain::getLinks() const
{
    return links;
}

void QnsbNarrativeChain::addLink(QnsbNarrativeLink* link)
{
//    // qDebug() << "QnsbNarrativeChain::addLink()";

    if (link != NULL){
        links.append(link);
    }
}

void QnsbNarrativeChain::removeLink(QnsbNarrativeLink* link)
{
    if (link != NULL){
        int index = links.indexOf(link);

        if (index >= 0){
            links.remove(index);
        }
    }
}


void QnsbNarrativeChain::adjust()
{

}

void QnsbNarrativeChain::draw(QPainter* painter)
{
    painter->setPen(QColor("#FFFFFF"));

    if (type != "referencial"){
        painter->drawText(QRect(8,8,60,32),title);
    }else{
        painter->drawText(QRect(8,8,60,32),matrix->getTitle());
    }

    if (selected){
        painter->setPen(QPen(QBrush(QColor("#FF9900")),5));
        painter->drawEllipse(0,32,48,48);
    }

    if (type == "home"){
        painter->drawPixmap(0,32,48,48,QPixmap(":/icon/home2"));

    }else if (type == "linear"){
        painter->drawPixmap(0,32,48,48,QPixmap(":/icon/nalter"));

    }else if (type == "distributive"){
        painter->drawPixmap(0,32,48,48,QPixmap(":/icon/ndist"));

    }else if (type == "referencial"){
        painter->drawPixmap(0,32,48,48,QPixmap(":/icon/nref"));
    }
}

void QnsbNarrativeChain::delineate(QPainterPath* painter) const
{
    painter->addEllipse(0,32,48,48);
}

void QnsbNarrativeChain::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    setSelected(true);

    emit chainSelected(this);
}

