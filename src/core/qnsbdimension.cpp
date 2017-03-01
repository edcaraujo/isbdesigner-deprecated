#include "qnsbdimension.h"

QnsbDimension::QnsbDimension()
{

}

QnsbDimension::~QnsbDimension()
{

}

QString QnsbDimension::getName() const
{
    return name;
}

void QnsbDimension::setName(QString name)
{
    this->name = name;
}

QnsbChain* QnsbDimension::getChain() const
{
    return chain;
}

void QnsbDimension::setChain(QnsbChain* chain)
{
    this->chain = chain;
}

QList<QnsbPanel*> QnsbDimension::gePanels() const
{
    return panels;
}

void QnsbDimension::addPanel(QnsbPanel* panel)
{
    if (panel != NULL){
        panel->setDimension(this);

        panels.append(panel);
    }
}

void QnsbDimension::removePanel(QnsbPanel* panel)
{
    if (panel != NULL){
       panels.removeOne(panel);
    }
}
