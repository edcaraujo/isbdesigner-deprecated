#ifndef QNSBAUTHORPANEL_H
#define QNSBAUTHORPANEL_H

#include "ui/view/qnsbgraphicspanel.h"

#include "qnsbauthordimension.h"
#include "qnsbauthorobject.h"
#include "qnsbauthortext.h"

class QnsbAuthorDimension;
class QnsbAuthorObject;

class QnsbAuthorPanel : public QnsbGraphicsPanel
{
    Q_OBJECT

public:
    QnsbAuthorPanel(QnsbGraphicsItem* parent = 0);

    ~QnsbAuthorPanel();

    int getIndex();

    void setIndex(int index);

    bool isSelected();

    void setSelected(bool selected);

    qreal getBegin() const;

    void setBegin(qreal begin);

    qreal getEnd() const;

    void setEnd(qreal end);

    QString getNotes() const;

    void setNotes(QString notes);

    QnsbAuthorPanel* getNext() const;

    void setNext(QnsbAuthorPanel* next);

    QnsbAuthorPanel* getPrevious() const;

    void setPrevious(QnsbAuthorPanel* previous);

    QnsbAuthorDimension* getDimension() const;

    void setDimension(QnsbAuthorDimension* dimension);

    QVector<QnsbAuthorObject*> getObjects() const;

    void addObject(QnsbAuthorObject* object);

    void removeObject(QnsbAuthorObject* object);

    void adjust();

public slots:
    void notifiesPanelSelection();

    void notifiesPanelTimeChange();

    void performVariable();

signals:
    void panelChanged(QnsbAuthorPanel* panel);

    void panelSelected(QnsbAuthorPanel* panel);

    void objectAdded(QnsbAuthorObject* object);

    void objectChanged(QnsbAuthorObject* object);

    void objectSelected(QnsbAuthorObject* object);

protected:
    void draw(QPainter* painter);

    void delineate(QPainterPath* painter) const;

    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);

    virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent* event);

private:
    void createActions();

    void createMenus();

    void createConnections();

    void addObjectToNextPanel(QnsbAuthorObject* reference, QnsbAuthorPanel* panel);

    int index;

    bool selected;

    qreal begin;

    qreal end;

    QMenu* contextMenu;

    QMenu* insertMenu;

    QAction* variableAction;

    QnsbAuthorText* beginItem;

    QnsbAuthorText* endItem;

    QString notes;

    QnsbAuthorPanel* next;

    QnsbAuthorPanel* previous;

    QnsbAuthorDimension* dimension;

    QVector<QnsbAuthorObject*> objects;
};

#endif // QNSBAUTHORPANEL_H
