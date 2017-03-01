#ifndef QNSBSKETCHPANEL_H
#define QNSBSKETCHPANEL_H

#include <QMenu>
#include <QAction>
#include <QVector>

#include "ui/view/qnsbgraphicspanel.h"

#include "qnsbsketchdimension.h"
#include "qnsbsketchobject.h"
#include "qnsbsketchnote.h"

class QnsbSketchDimension;
class QnsbSketchObject;

class QnsbSketchPanel : public QnsbGraphicsPanel
{
    Q_OBJECT
public:
    QnsbSketchPanel(QnsbGraphicsItem* parent = 0);

    virtual ~QnsbSketchPanel();

    int getIndex();

    void setIndex(int index);

    bool isSelected();

    void setSelected(bool selected);

    QnsbSketchPanel* getPrevious();

    void setPrevious(QnsbSketchPanel* previous);

    QnsbSketchPanel* getNext();

    void setNext(QnsbSketchPanel* next);

    QnsbSketchDimension* getDimension();

    void setDimension(QnsbSketchDimension* dimension);

    QVector<QnsbSketchObject*> getObjects() const;

    void addObject(QnsbSketchObject* object);

    void removeObject(QnsbSketchObject* object);

    QString getNotes() const;

    void setNotes(QString notes);

    void adjust();

    QString getTBegin() const;

    void setTBegin(QString tbegin);

    QString getTEnd() const;

    void setTEnd(QString tend);

public slots:
    void performImage();

    void performVideo();

    void performAudio();

    void performText();

    void performScript();

    void notifiesPanelNoteChange();

    void notifiesPanelSelection();

signals:
    void panelSelected(QnsbSketchPanel* panel);

    void panelChanged(QnsbSketchPanel* panel);

    void objectAdded(QnsbSketchObject* object);

    void objectRemoved(QnsbSketchObject* object);

    void objectChanged(QnsbSketchObject* object);

    void objectSelected(QnsbSketchObject* object);

protected:
    virtual void draw(QPainter* painter);

    virtual void delineate(QPainterPath* painter) const;

    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);

    virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent* event);

private:
    void createActions();

    void createMenus();

    void createConnections();

    void addObjectToNextPanel(QnsbSketchObject* reference, QnsbSketchPanel* panel);

private:
    int index;

    bool selected;

    QString notes;

    QString tbegin;

    QString tend;

    QMenu* insertMenu;

    QMenu* contextMenu;

    QAction* videoAction;

    QAction* audioAction;

    QAction* imageAction;

    QAction* scriptAction;

    QAction* textAction;

    QnsbSketchPanel* previous;

    QnsbSketchPanel* next;

    QnsbSketchNote* note;

    QnsbSketchDimension* dimension;

    QVector<QnsbSketchObject*> objects;
};

#endif // QNSBSKETCHPANEL_H
