#include "qnsbgraphicschain.h"

QnsbGraphicsChain::QnsbGraphicsChain(QObject* parent)
    : QnsbGraphicsScene(parent)
{

}

QnsbGraphicsChain::~QnsbGraphicsChain()
{

}

QnsbGraphicsView* QnsbGraphicsChain::getView() const
{
    return view;
}

void QnsbGraphicsChain::setView(QnsbGraphicsView* view)
{
    this->view = view;
}
