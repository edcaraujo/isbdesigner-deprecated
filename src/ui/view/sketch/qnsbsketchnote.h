#ifndef QNSBSKETCHNOTE_H
#define QNSBSKETCHNOTE_H

#include <QGraphicsTextItem>
#include <QDebug>

class QnsbSketchNote : public QGraphicsTextItem
{
    Q_OBJECT

public:
    QnsbSketchNote(QGraphicsItem* parent = 0);

    ~QnsbSketchNote();

signals:
    void noteSelected();

    void noteChanged();

protected:
    virtual void focusInEvent(QFocusEvent * event);

    virtual void focusOutEvent(QFocusEvent * event);
};

#endif // QNSBSKETCHNOTE_H
