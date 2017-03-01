#include "qnsbsketchnote.h"

QnsbSketchNote::QnsbSketchNote(QGraphicsItem* parent)
    : QGraphicsTextItem(parent)
{
    setTextInteractionFlags(Qt::TextEditorInteraction);
    setDefaultTextColor(QColor("#FFFFFF"));
}

QnsbSketchNote::~QnsbSketchNote()
{

}

void QnsbSketchNote::focusInEvent(QFocusEvent * event)
{
    emit noteSelected();

    QGraphicsTextItem::focusInEvent(event);
}

void QnsbSketchNote::focusOutEvent(QFocusEvent * event)
{
    emit noteChanged();

    QGraphicsTextItem::focusOutEvent(event);
}
