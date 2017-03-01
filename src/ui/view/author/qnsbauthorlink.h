#ifndef QNSBAUTHORLINK_H
#define QNSBAUTHORLINK_H

#include <QDialog>
#include <QMenu>
#include <QAction>

#include "ui/view/qnsbgraphicslink.h"
#include "qnsbauthorview.h"
#include <QStandardItemModel>

#include "qnsbauthorchain.h"

#include "ui_QnsbAuthorLinkProperties.h"

using namespace Ui;

class QnsbAuthorChain;
class QnsbAuthorView;

class QnsbAuthorLink : public QnsbGraphicsLink
{
    Q_OBJECT

public:
    QnsbAuthorLink(QnsbGraphicsItem* parent = 0);

    ~QnsbAuthorLink();

    QString getType() const;

    void setType(QString type);

    bool isSelected();

    void setSelected(bool selected);

    QString getKey() const;

    void setKey(QString key);

    QString getVarValue() const;

    void setVarValue(QString varvalue);

    QString getVarName() const;

    void setVarName(QString varname);

    QString getOp() const;

    void setOp(QString op);

    QnsbAuthorChain* getChain() const;

    void setChain(QnsbAuthorChain* chain);

    QnsbAuthorObject* getTrigger() const;

    void setTrigger(QnsbAuthorObject* trigger);

    QnsbAuthorChain* getTarget() const;

    void setTarget(QnsbAuthorChain* target);

    void adjust();

public slots:
    void performProperty();

    void adjustType(QString type);

    void adjustVariable(QString variable);

signals:
    void chainSelected(QnsbAuthorChain* chain);

    void linkSelected(QnsbAuthorLink* link);

    void linkChanged(QnsbAuthorLink* link);

protected:
    virtual void draw(QPainter* painter);

    virtual void delineate(QPainterPath* painter) const;

    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);

    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event);

    virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent* event);

private:
    void createActions();

    void createMenus();

    void createConnections();

    bool selected;

    QString type;

    QString key;

    QString varname;

    QString op;

    QString varvalue;

    QnsbAuthorChain* chain;

    QnsbAuthorObject* trigger;

    QnsbAuthorChain* target;

    QDialog* dialog;

    QnsbAuthorLinkProperties properties;

    QMenu* contextMenu;

    QAction* propertyAction;

    QMap<QString, QnsbAuthorChain*> targets;

    QMap<QString, QnsbAuthorObject*> triggers;
};

#endif // QNSBAUTHORLINK_H
