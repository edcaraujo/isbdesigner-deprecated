#ifndef QNSBGRAPHICSSCENE_H
#define QNSBGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QString>
#include <QUuid>

class QnsbGraphicsScene : public QGraphicsScene
{
public:
    QnsbGraphicsScene(QObject* parent = 0);

    virtual ~QnsbGraphicsScene();

    QString getUid() const;

    void setUid(QString uid);

    qreal getTop() const;

    void setTop(qreal top);

    qreal getLeft() const;

    void setLeft(qreal left);

    qreal getRight() const;

    void setRight(qreal right);

    qreal getBottom() const;

    void setBottom(qreal bottom);

    qreal getWidth() const;

    void setWidth(qreal width);

    qreal getMinimumWidth() const;

    void setMinimumWidth(qreal minimumWidth);

    qreal getHeight() const;

    void setHeight(qreal height);

    qreal getMinimumHeight() const;

    void setMinimumHeight(qreal minimumHeight);

private:
    QString uid;

    qreal top;

    qreal left;

    qreal right;

    qreal bottom;

    qreal width;

    qreal minimumWidth;

    qreal height;

    qreal minimumHeight;
};

#endif // QNSBGRAPHICSSCENE_H
