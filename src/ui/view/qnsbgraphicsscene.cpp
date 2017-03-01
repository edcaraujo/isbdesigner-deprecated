#include "qnsbgraphicsscene.h"

QnsbGraphicsScene::QnsbGraphicsScene(QObject* parent)
    : QGraphicsScene(parent)
{
    setTop(0);
    setLeft(0);
    setWidth(0);
    setHeight(0);

    setMinimumWidth(0);
    setMinimumHeight(0);

    setUid(QUuid::createUuid().toString());
}

QnsbGraphicsScene::~QnsbGraphicsScene()
{

}

QString QnsbGraphicsScene::getUid() const
{
    return uid;
}

void QnsbGraphicsScene::setUid(QString uid)
{
    this->uid = uid;
}

qreal QnsbGraphicsScene::getTop() const
{
    return top;
}

void QnsbGraphicsScene::setTop(qreal top)
{
    this->top = top;

    setSceneRect(left, top, width, height);
}

qreal QnsbGraphicsScene::getLeft() const
{
    return left;
}

void QnsbGraphicsScene::setLeft(qreal left)
{
    this->left = left;

    setSceneRect(left, top, width, height);
}

qreal QnsbGraphicsScene::getWidth() const
{
    return width;
}

void QnsbGraphicsScene::setWidth(qreal width)
{
    if (width >= minimumWidth){
        this->width = width;

        setSceneRect(left, top, width, height);
    }
}

qreal QnsbGraphicsScene::getMinimumWidth() const
{
    return minimumWidth;
}

void QnsbGraphicsScene::setMinimumWidth(qreal minimumWidth)
{
    this->minimumWidth = minimumWidth;

    if (minimumWidth > width){
        setWidth(minimumWidth);
    }
}

qreal QnsbGraphicsScene::getHeight() const
{
    return height;
}

void QnsbGraphicsScene::setHeight(qreal height)
{
    if (height >= minimumHeight){
        this->height = height;

        setSceneRect(left, top, width, height);
    }
}

qreal QnsbGraphicsScene::getMinimumHeight() const
{
    return minimumHeight;
}

void QnsbGraphicsScene::setMinimumHeight(qreal minimumHeight)
{
    this->minimumHeight = minimumHeight;

    if (minimumHeight > height){
        setHeight(minimumHeight);
    }
}
