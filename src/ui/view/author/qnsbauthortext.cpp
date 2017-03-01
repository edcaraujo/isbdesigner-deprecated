#include "qnsbauthortext.h"

QnsbAuthorText::QnsbAuthorText(QGraphicsItem* parent)
    : QGraphicsTextItem(parent)
{
    setTextInteractionFlags(Qt::TextEditorInteraction);
    setDefaultTextColor(QColor("#FFFFFF"));
}

QnsbAuthorText::~QnsbAuthorText()
{

}

void QnsbAuthorText::focusInEvent(QFocusEvent * event)
{
    emit textSelected();

    QGraphicsTextItem::focusInEvent(event);
}

void QnsbAuthorText::focusOutEvent(QFocusEvent * event)
{
    emit textChanged();

    QGraphicsTextItem::focusOutEvent(event);
}


