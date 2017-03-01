#ifndef QNSBAUTHOROBJECT_H
#define QNSBAUTHOROBJECT_H

#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QGraphicsSceneDragDropEvent>
#include <QUrl>

#include "ui/view/qnsbgraphicsitem.h"

#include "ui_QnsbAuthorVariableProperty.h"

using namespace Ui;

#include "qnsbauthorpanel.h"

class QnsbAuthorPanel;

class QnsbAuthorObject : public QnsbGraphicsItem
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

    QnsbAuthorObject(QnsbGraphicsItem* parent = 0);

    ~QnsbAuthorObject();

    QString getType();

    void setMoving(bool moving);

    bool isMoving();

    void setResizing(bool resizing);

    bool isInstanceChange();

    void setInstanceChange(bool instanceChange);

    bool isResizing();

    void setPanel(QnsbAuthorPanel* panel);

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

    QnsbAuthorPanel* getPanel() const;

    void setType(QString type);

    bool isSelected();

    void setSelected(bool selected);

    void adjust();

    QString getInstanceID() const;

    void setInstanceID(QString instanceID);

    QString getId() const;

    void setId(QString id);

    QString getSrc() const;

    void setSrc(QString src);

    QString getStatusID() const;

    void setStatusID(QString statusID);

    QString getLastStatusID() const;

    void setLastStatusID(QString statusID);

    QString getVarValue() const;

    void setVarValue(QString varvalue);

    QString getVarName() const;

    void setVarName(QString varname);

    QString getSketch() const;

    void setSketch(QString sketch);

    QString getPreview() const;

    void setPreview(QString preview);

signals:
    void variablePerformed();

    void objectChanged(QnsbAuthorObject* object);

    void objectSelected(QnsbAuthorObject* object);

public slots:
    void performSource();

    void performPreview();

    void performProperty();

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

    bool instanceChange;

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

    QString id;

    QString type;

    QString src;

    QString instanceID;

    QString statusID;

    QString lastStatusID;

    QString varname;

    QString varvalue;

    QString sketch;

    QString preview;

    QnsbAuthorPanel* panel;

    QMenu* contextMenu;

    QMenu* insertMenu;

    QPixmap img;

    Ui::QnsbAuthorVariableProperties d;

    QAction* variableAction;

    QAction* sourceAction;

    QAction* previewAction;

    QAction* propertyAction;

    QDialog* properties;
};

#endif // QNSBAUTHOROBJECT_H
