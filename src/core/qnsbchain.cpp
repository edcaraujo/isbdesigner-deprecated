#include "qnsbchain.h"

QnsbChain::QnsbChain()
{

}

QnsbChain::~QnsbChain()
{

}

QString QnsbChain::getId() const
{
    return id;
}

void QnsbChain::setId(QString id)
{
    this->id = id;
}

QString QnsbChain::getInterface() const
{
    return interface;
}

void QnsbChain::setInterface(QString interface)
{
    this->interface = interface;
}

QString QnsbChain::getType() const
{
    return type;
}

void QnsbChain::setType(QString type)
{
    this->type = type;
}

QnsbChain* QnsbChain::getMatrix()
{
    return matrix;
}

void QnsbChain::setMatrix(QnsbChain* matrix)
{
    this->matrix = matrix;
}

QString QnsbChain::getsMatrix()
{
    return smatrix;
}

void QnsbChain::setsMatrix(QString smatrix)
{
    this->smatrix = smatrix;
}

QVector<QnsbDimension*> QnsbChain::getDimensions() const
{
    return dimensions;
}

void QnsbChain::addDimension(QnsbDimension* dimension)
{
    if (dimension != NULL){
        dimension->setChain(this);

        dimensions.append(dimension);
    }
}

void QnsbChain::removeDimension(QnsbDimension* dimension)
{
    if (dimension != NULL){
        int index = dimensions.indexOf(dimension);

        if (index > 0){
            dimensions.remove(index);
        }
    }
}

QVector<QnsbLink*> QnsbChain::getLinks() const
{
    return links;
}

void QnsbChain::addLink(QnsbLink* link)
{
    if (link != NULL){
        link->setChain(this);

        links.append(link);
    }
}

void QnsbChain::removeLink(QnsbLink* link)
{
    if (link != NULL){
        int index = links.indexOf(link);

        if (index > 0){
            links.remove(index);
        }
    }
}
