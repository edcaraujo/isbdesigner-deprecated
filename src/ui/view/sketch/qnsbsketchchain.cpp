#include "qnsbsketchchain.h"

QnsbSketchChain::QnsbSketchChain(QObject* parent)
    : QnsbGraphicsChain(parent)
{
    setPrevious(NULL);

    nreflink = 0;

    ndistlink = 0;

    nseqlink = 0;

    matrix = NULL;

    setInterface(NULL);
}

QnsbSketchChain::~QnsbSketchChain()
{

}

int QnsbSketchChain::getnReferencialLink()
{
    return nreflink;
}

int QnsbSketchChain::getnSequencialLink()
{
    return nseqlink;
}

int QnsbSketchChain::getnDistributiveLink()
{
    return ndistlink;
}

QString QnsbSketchChain::getTitle() const
{
    return title;
}

QString QnsbSketchChain::getSInterface() const
{
    return sinterface;
}

void QnsbSketchChain::setSInterface(QString  sinterface)
{
    this->sinterface = sinterface;
}

void QnsbSketchChain::setTitle(QString title)
{
    this->title = title;
}

QString QnsbSketchChain::getType() const
{
    return type;
}

void QnsbSketchChain::setType(QString type)
{
    this->type = type;
}

QnsbSketchChain* QnsbSketchChain::getPrevious()
{
    return previous;
}

void QnsbSketchChain::setPrevious(QnsbSketchChain* previous)
{
    this->previous = previous;
}

QnsbSketchChain* QnsbSketchChain::getMatrix()
{
    return matrix;
}

void QnsbSketchChain::setMatrix(QnsbSketchChain* matrix)
{
    this->matrix = matrix;
}

QnsbSketchDimension* QnsbSketchChain::getInterface()
{
    return interface;
}

void QnsbSketchChain::setInterface(QnsbSketchDimension* interface)
{
    this->interface = interface;
}

QVector<QnsbSketchDimension*> QnsbSketchChain::getDimensions() const
{
    return dimensions;
}

void QnsbSketchChain::addDimension(QnsbSketchDimension* dimension)
{
    // qDebug() << "QnsbSketchChain::addDimension()";

    if (dimension != NULL){

        if (dimension->getName() == ""){
            if (dimensions.size() == 0){
                setInterface(dimension);
                dimension->setName("main");
            }else{
                dimension->setName("sec"+QString::number(dimension->getChain()->getDimensions().size()));
            }
        }else{
            if (dimension->getName() == getSInterface()){
                setInterface(dimension);
            }
        }

        dimensions.append(dimension);

        connect(dimension, SIGNAL(panelAdded(QnsbSketchPanel*)), SIGNAL(panelAdded(QnsbSketchPanel*)));
        connect(dimension,SIGNAL(panelChanged(QnsbSketchPanel*)),SIGNAL(panelChanged(QnsbSketchPanel*)));

        connect(dimension, SIGNAL(chainAdded(QnsbSketchChain*)), SIGNAL(chainAdded(QnsbSketchChain*)));
        connect(dimension, SIGNAL(chainChange(QnsbSketchChain*)), SIGNAL(chainChange(QnsbSketchChain*)));
        connect(dimension, SIGNAL(chainSelected(QnsbSketchChain*)), SIGNAL(chainSelected(QnsbSketchChain*)));

        connect(dimension, SIGNAL(dimensionAdded(QnsbSketchDimension*)), SIGNAL(dimensionAdded(QnsbSketchDimension*)));

        connect(dimension, SIGNAL(linkAdded(QnsbSketchLink*)), SIGNAL(linkAdded(QnsbSketchLink*)));

        connect(dimension, SIGNAL(panelSelected(QnsbSketchPanel*)), SIGNAL(panelSelected(QnsbSketchPanel*)));

        connect(dimension, SIGNAL(objectAdded(QnsbSketchObject*)), SIGNAL(objectAdded(QnsbSketchObject*)));
        connect(dimension, SIGNAL(objectRemoved(QnsbSketchObject*)), SIGNAL(objectRemoved(QnsbSketchObject*)));
        connect(dimension, SIGNAL(objectChanged(QnsbSketchObject*)), SIGNAL(objectChanged(QnsbSketchObject*)));
        connect(dimension, SIGNAL(objectSelected(QnsbSketchObject*)), SIGNAL(objectSelected(QnsbSketchObject*)));

        addItem(dimension);

        adjust();

        emit chainChange(this);
    }
}

void QnsbSketchChain::removeDimension(QnsbSketchDimension* dimension)
{
    if (dimension != NULL){
        int index = dimensions.indexOf(dimension);

        if (index >= 0){
            dimensions.remove(index);

            removeItem(dimension);
        }
    }
}

void QnsbSketchChain::adjust()
{
    int n = 0;

    if (dimensions.size() > 0){
        n = interface->getPanels().size();
    }

    qreal width = (56 + 56) + (n + 1)*(56 + 56 + 400);

    qreal height;

    if (links.size() > 2){
        height = links.size()*(90) + (links.size()-1)*32 + 50 + (dimensions.size()-1)*(400+32);
    }else{
        height =  dimensions.size()*400 + (dimensions.size()-1)*(32) + 50;
    }

    setWidth(width);

    if (getHeight() < height){
        setHeight(height);
    }

    int nd = 0;

    int mosttop = getHeight()/2 - (dimensions.size()*400 + (dimensions.size()-1)*(32))/2;

    foreach (QnsbSketchDimension* dimension, dimensions) {
        dimension->setTop(mosttop + nd*(400+16));
        dimension->adjust();

        nd++;
    }
}

QVector<QnsbSketchLink*> QnsbSketchChain::getLinks() const
{
    return links;
}

void QnsbSketchChain::addLink(QnsbSketchLink* link)
{
    // qDebug() << "QnsbSketchChain::addLink()";

    if (link != NULL){
        connect(link, SIGNAL(chainSelected(QnsbSketchChain*)), SIGNAL(chainSelected(QnsbSketchChain*)));

        connect(link, SIGNAL(linkSelected(QnsbSketchLink*)), SIGNAL(linkSelected(QnsbSketchLink*)));

        links.append(link);

        addItem(link);

        adjust();
    }
}

void QnsbSketchChain::removeLink(QnsbSketchLink* link)
{
    if (link != NULL){
        int index = links.indexOf(link);

        if (index >= 0){
            links.remove(index);

            removeItem(link);
        }
    }
}
