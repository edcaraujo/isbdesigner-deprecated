#ifndef QNSBGRAPHICSVIEW_H
#define QNSBGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QString>
#include <QMap>
#include <QResizeEvent>

#include "qnsbgraphicschain.h"
#include "qnsbgraphicsdimension.h"
#include "qnsbgraphicspanel.h"

class QnsbGraphicsChain;
class QnsbGraphicsDimension;

class QnsbGraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    QnsbGraphicsView(QWidget* parent = 0);

    ~QnsbGraphicsView();

    QString getImage();

    void setImage(QString image);

    virtual void clean() = 0;

public slots:
    virtual void addChain(QString uid, QMap<QString,QString> properties) = 0;

    virtual void removeChain(QString uid) = 0;

    virtual void changeChain(QString uid, QMap<QString,QString> properties) = 0;

    virtual void selectChain(QString uid) = 0;

    virtual void addDimension(QString uid, QString parent, QMap<QString,QString> properties) = 0;

    virtual void removeDimension(QString uid) = 0;

    virtual void changeDimension(QString uid, QMap<QString,QString> properties) = 0;

    virtual void selectDimension(QString uid) = 0;

    virtual void addLink(QString uid, QString parent, QMap<QString,QString> properties) = 0;

    virtual void removeLink(QString uid) = 0;

    virtual void changeLink(QString uid, QMap<QString,QString> properties) = 0;

    virtual void selectLink(QString uid) = 0;

    virtual void addPanel(QString uid, QString parent, QMap<QString,QString> properties) = 0;

    virtual void removePanel(QString uid) = 0;

    virtual void changePanel(QString uid, QMap<QString,QString> properties) = 0;

    virtual void selectPanel(QString uid) = 0;

    virtual void addObject(QString uid, QString parent, QMap<QString,QString> properties) = 0;

    virtual void removeObject(QString uid) = 0;

    virtual void changeObject(QString uid, QMap<QString,QString> properties) = 0;

    virtual void selectObject(QString uid) = 0;

signals:
    void chainAdded(QString uid, QMap<QString,QString> properties);

    void chainRemoved(QString uid);

    void chainChanged(QString uid, QMap<QString,QString> properties);

    void chainSelected(QString uid);

    void dimensionAdded(QString uid, QString parent, QMap<QString,QString> properties);

    void dimensionRemoved(QString uid);

    void dimensionChanged(QString uid, QMap<QString,QString> properties);

    void dimensionSelected(QString uid);

    void linkAdded(QString uid, QString parent, QMap<QString,QString> properties);

    void linkRemoved(QString uid);

    void linkChanged(QString uid, QMap<QString,QString> properties);

    void linkSelected(QString uid);

    void panelAdded(QString uid, QString parent, QMap<QString,QString> properties);

    void panelRemoved(QString uid);

    void panelChanged(QString uid, QMap<QString,QString> properties);

    void panelSelected(QString uid);

    void objectAdded(QString uid, QString parent, QMap<QString,QString> properties);

    void objectRemoved(QString uid);

    void objectChanged(QString uid, QMap<QString,QString> properties);

    void objectSelected(QString uid);

private:
    QString image;
};

#endif // QNSBGRAPHICSVIEW_H
