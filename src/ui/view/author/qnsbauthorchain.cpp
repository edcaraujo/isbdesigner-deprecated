#include "qnsbauthorchain.h"

QnsbAuthorChain::QnsbAuthorChain(QObject* parent)
    : QnsbGraphicsChain(parent)
{
    setPrevious(NULL);
    setInterface(NULL);

    matrix = NULL;
}

QnsbAuthorChain::~QnsbAuthorChain()
{

}

QString QnsbAuthorChain::getId() const
{
    return id;
}

void QnsbAuthorChain::setId(QString id)
{
    this->id = id;
}

QString QnsbAuthorChain::getType() const
{
    return type;
}

void QnsbAuthorChain::setType(QString type)
{
    this->type = type;
}

QnsbAuthorChain* QnsbAuthorChain::getPrevious()
{
    return previous;
}

void QnsbAuthorChain::setPrevious(QnsbAuthorChain* previous)
{
    this->previous = previous;
}

QnsbAuthorChain* QnsbAuthorChain::getMatrix()
{
    return matrix;
}

void QnsbAuthorChain::setMatrix(QnsbAuthorChain* matrix)
{
    this->matrix = matrix;
}

QnsbAuthorDimension* QnsbAuthorChain::getInterface()
{
    return interface;
}

void QnsbAuthorChain::setInterface(QnsbAuthorDimension* interface)
{
    this->interface = interface;
}

QVector<QnsbAuthorDimension*> QnsbAuthorChain::getDimensions() const
{
    return dimensions;
}

void QnsbAuthorChain::addDimension(QnsbAuthorDimension* dimension)
{
    if (dimension != NULL){
        if (dimensions.size() == 0){
            setInterface(dimension);
        }

        addItem(dimension);

        adjust();

        connect(dimension, SIGNAL(chainSelected(QnsbAuthorChain*)), SIGNAL(chainSelected(QnsbAuthorChain*)));

        connect(dimension, SIGNAL(panelChanged(QnsbAuthorPanel*)), SIGNAL(panelChanged(QnsbAuthorPanel*)));
        connect(dimension, SIGNAL(panelSelected(QnsbAuthorPanel*)), SIGNAL(panelSelected(QnsbAuthorPanel*)));

        connect(dimension, SIGNAL(objectAdded(QnsbAuthorObject*)), SIGNAL(objectAdded(QnsbAuthorObject*)));
        connect(dimension, SIGNAL(objectChanged(QnsbAuthorObject*)), SIGNAL(objectChanged(QnsbAuthorObject*)));
        connect(dimension, SIGNAL(objectSelected(QnsbAuthorObject*)), SIGNAL(objectSelected(QnsbAuthorObject*)));

        dimensions.append(dimension);
    }
}

void QnsbAuthorChain::removeDimension(QnsbAuthorDimension* dimension)
{
    if (dimension != NULL){
        int index = dimensions.indexOf(dimension);

        if (index >= 0){
            dimensions.remove(index);
        }
    }
}

QVector<QnsbAuthorLink*> QnsbAuthorChain::getLinks() const
{
    return links;
}

void QnsbAuthorChain::addLink(QnsbAuthorLink* link)
{
    if (link != NULL){
        links.append(link);

        connect(link, SIGNAL(chainSelected(QnsbAuthorChain*)), SIGNAL(chainSelected(QnsbAuthorChain*)));

        connect(link, SIGNAL(linkSelected(QnsbAuthorLink*)), SIGNAL(linkSelected(QnsbAuthorLink*)));
        connect(link, SIGNAL(linkChanged(QnsbAuthorLink*)), SIGNAL(linkChanged(QnsbAuthorLink*)));

        addItem(link);

        adjust();
    }
}

void QnsbAuthorChain::removeLink(QnsbAuthorLink* link)
{
    if (link != NULL){
        int index = links.indexOf(link);

        if (index >= 0){
            links.remove(index);
        }
    }
}

void QnsbAuthorChain::adjust()
{    
    int MAXNPANEL = 0;

    foreach (QnsbAuthorDimension* dimension, dimensions) {
        int NPANEL = dimension->getPanels().size();

        if (MAXNPANEL < NPANEL){
            MAXNPANEL = NPANEL;
        }
    }

    qreal width = (56 + 56) + (MAXNPANEL + 1)*(56 + 56 + 400);

    setWidth(width);

    qreal height;

    if (links.size() > 2){
        height = links.size()*(90) + (links.size()-1)*32 + 50 + (dimensions.size()-1)*(400+32);
    }else{
        height =  dimensions.size()*400 + (dimensions.size()-1)*(32) + 50;
    }

    if (getHeight() < height){
        setHeight(height);
    }

    int nd = 0;

    int mosttop = getHeight()/2 - (dimensions.size()*400 + (dimensions.size()-1)*(32))/2;

    foreach (QnsbAuthorDimension* dimension, dimensions) {
        dimension->setTop(mosttop + nd*(400+16));
        dimension->adjust();

        nd++;
    }
}
