#include "qnsbpanel.h"

QnsbPanel::QnsbPanel()
{

}

QnsbPanel::~QnsbPanel()
{

}

QString QnsbPanel::getBegin() const
{
    return begin;
}

void QnsbPanel::setBegin(QString begin)
{
    this->begin = begin;
}

QString QnsbPanel::getEnd() const
{
    return end;
}

void QnsbPanel::setEnd(QString end)
{
    this->end = end;
}

QString QnsbPanel::getNotes() const
{
    return notes;
}

void QnsbPanel::setNotes(QString notes)
{
    this->notes = notes;
}

QnsbDimension* QnsbPanel::getDimension() const
{
    return dimension;
}

void QnsbPanel::setDimension(QnsbDimension* dimension)
{
    this->dimension = dimension;
}

QVector<QnsbObject*> QnsbPanel::getObjects() const
{
    return objects;
}

void QnsbPanel::addObject(QnsbObject* object)
{
    if (object != NULL){
        objects.append(object);
    }
}

void QnsbPanel::removeObject(QnsbObject* object)
{
    if (object != NULL){
        int index = objects.indexOf(object);

        if (index >= 0){
            objects.remove(index);
        }
    }
}
