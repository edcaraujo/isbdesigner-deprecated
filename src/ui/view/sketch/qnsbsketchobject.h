#ifndef QNSBSKETCHOBJECT_H
#define QNSBSKETCHOBJECT_H

#include <QFileDialog>
#include <QGraphicsSceneDragDropEvent>
#include <QUrl>

#include "ui/view/qnsbgraphicsitem.h"

#include "qnsbsketchpanel.h"

class QnsbSketchPanel;

class QnsbSketchObject : public QnsbGraphicsItem
{
    Q_OBJECT

public:
    enum ResizeType {
        Top,
        TopRight,
        Right,
        BottomRight,
        Bottom,
        BottomLeft,
        Left,
        TopLeft
    };

    QnsbSketchObject(QnsbGraphicsItem* parent = 0);

    ~QnsbSketchObject();

    QString getType();

    void setMoving(bool moving);

    bool isMoving();

    void setResizing(bool resizing);

    bool isResizing();

    void setPanel(QnsbSketchPanel* panel);

    qreal getTop() const;

    void setTop(qreal top);

    qreal getMoveTop();

    void setMoveTop(qreal moveTop);

    qreal getPressTop();

    void setPressTop(qreal pressTop);

    qreal getResizeTop();

    void setResizeTop(qreal resizeTop);

    qreal getLeft() const;

    void setLeft(qreal top);

    qreal getMoveLeft();

    void setMoveLeft(qreal moveLeft);

    qreal getPressLeft();

    void setPressLeft(qreal pressLeft);

    qreal getResizeLeft();

    void setResizeLeft(qreal resizeLeft);

    qreal getWidth() const;

    void setWidth(qreal width);

    qreal getPressWidth();

    void setPressWidth(qreal pressWidth);

    qreal getResizeWidth();

    void setResizeWidth(qreal resizeWidth);

    qreal getHeight() const;

    void setHeight(qreal height);

    qreal getPressHeight();

    void setPressHeight(qreal pressHeight);

    qreal getResizeHeight();

    void setResizeHeight(qreal resizeHeight);

    int getResizeType();

    void setResizeType(int resizeType);

    QnsbSketchPanel* getPanel() const;

    QString getDraft() const;

    void setDraft(QString draft);

    void setType(QString type);

    bool isSelected();

    void setSelected(bool selected);

    void adjust();

    QString getInstanceID() const;

    void setInstanceID(QString instanceID);

    QString getId() const;

    void setId(QString id);

    QString getStatusID() const;

    QString getSrc() const;

    void setSrc(QString src);

    QString getSketch() const;

    void setSketch(QString sketch);

    QString getPreview() const;

    void setPreview(QString preview);

    void setStatusID(QString statusID);

    QString getLastStatusID() const;

    void setLastStatusID(QString statusID);

    QString getVarValue() const;

    void setVarValue(QString varvalue);

    QString getVarName() const;

    void setVarName(QString varname);

public slots:
    void performRemove();

    void performSketch();

signals:
    void objectChanged(QnsbSketchObject* object);

    void objectSelected(QnsbSketchObject* object);

    void objectRemoved(QnsbSketchObject* object);

    void imagePeformed();

    void videoPeformed();

    void audioPeformed();

    void textPeformed();

    void scriptPeformed();

protected:
    virtual void draw(QPainter* painter);

    virtual void delineate(QPainterPath* painter) const;

    virtual void move(QGraphicsSceneMouseEvent* event);

    virtual void resize(QGraphicsSceneMouseEvent* event);

    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event);

    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);

    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent*event);

    virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent* event);

    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);

    void dropEvent(QGraphicsSceneDragDropEvent *event);

private:
    void createActions();

    void createMenus();

    void createConnections();

    bool selected;

    bool moving;

    bool linking;

    bool resizing;

    qreal top;

    qreal moveTop;

    qreal pressTop;

    qreal resizeTop;

    qreal left;

    qreal moveLeft;

    qreal pressLeft;

    qreal resizeLeft;

    qreal width;

    qreal pressWidth;

    qreal resizeWidth;

    qreal height;

    qreal pressHeight;

    qreal resizeHeight;

    int resizeType;

    QString type;

    QString id;

    QString src;

    QString sketch;

    QString preview;

    QString instanceID;

    QString statusID;

    QString lastStatusID;

    QnsbSketchPanel* panel;

    QMenu* insertMenu;

    QMenu* contextMenu;

    QString varname;

    QString varvalue;

    QAction* videoAction;

    QAction* audioAction;

    QAction* imageAction;

    QAction* textAction;

    QAction* scriptAction;

    QAction* sketchAction;

    QAction* removeAction;
};

#endif // QNSBSKETCHOBJECT_H
