#ifndef QNSBAUTHORTEXT_H
#define QNSBAUTHORTEXT_H

#include <QGraphicsTextItem>

class QnsbAuthorText : public QGraphicsTextItem
{
    Q_OBJECT

public:
    QnsbAuthorText(QGraphicsItem* parent = 0);

    ~QnsbAuthorText();

signals:
    void textSelected();

    void textChanged();

protected:
    virtual void focusInEvent(QFocusEvent * event);

    virtual void focusOutEvent(QFocusEvent * event);
};

#endif // QNSBAUTHORTEXT_H
