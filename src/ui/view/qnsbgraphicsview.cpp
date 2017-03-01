#include "qnsbgraphicsview.h"

QnsbGraphicsView::QnsbGraphicsView(QWidget* parent)
    : QGraphicsView(parent)
{

}

QnsbGraphicsView::~QnsbGraphicsView()
{

}

QString QnsbGraphicsView::getImage()
{
    return image;
}

void QnsbGraphicsView::setImage(QString image)
{
    this->image = image;

    setBackgroundBrush(QBrush(QImage(image)));
}
