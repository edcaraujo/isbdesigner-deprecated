#ifndef QNSBGRAPHICSCHAIN_H
#define QNSBGRAPHICSCHAIN_H

#include <QVector>

#include "qnsbgraphicsview.h"
#include "qnsbgraphicsscene.h"
#include "qnsbgraphicsdimension.h"

class QnsbGraphicsView;
class QnsbGraphicsDimension;

class QnsbGraphicsChain : public QnsbGraphicsScene
{
public:
    QnsbGraphicsChain(QObject* parent = 0);

    virtual ~QnsbGraphicsChain();

    QnsbGraphicsView* getView() const;

    void setView(QnsbGraphicsView* view);

    virtual void adjust() = 0;

private:
    QnsbGraphicsView* view;
};

#endif // QNSBGRAPHICSCHAIN_H
