#ifndef QNSBVIEW_H
#define QNSBVIEW_H

#include <QMap>
#include <QVector>
#include <QUuid>
#include <QStackedWidget>

#include "core/qnsbdocument.h"

#include "ui/view/sketch/qnsbsketchview.h"
#include "ui/view/narrative/qnsbnarrativeview.h"
#include "ui/view/author/qnsbauthorview.h"

class QnsbView : public QStackedWidget
{
    Q_OBJECT

public:
    QnsbView(QWidget* parent = 0);

    virtual ~QnsbView();

    void load(QString location);

    void save(QString location);

    void performExport(QString location);

    QString getExportData();

    void clean();

    void showSketch();

    void showAuthor();

    void showNarrative();

public slots:

    void addChain(QString uid, QMap<QString,QString> properties);

    void removeChain(QString uid);

    void changeChain(QString uid, QMap<QString,QString> properties);

    void selectChain(QString uid);

    void addDimension(QString uid, QString parent, QMap<QString,QString> properties);

    void removeDimension(QString uid);

    void changeDimension(QString uid, QMap<QString,QString> properties);

    void selectDimension(QString uid);

    void addLink(QString uid, QString parent, QMap<QString,QString> properties);

    void removeLink(QString uid);

    void changeLink(QString uid, QMap<QString,QString> properties);

    void selectLink(QString uid);

    void addPanel(QString uid, QString parent, QMap<QString,QString> properties);

    void removePanel(QString uid);

    void changePanel(QString uid, QMap<QString,QString> properties);

    void selectPanel(QString uid);

    void addObject(QString uid, QString parent, QMap<QString,QString> properties);

    void removeObject(QString uid);

    void changeObject(QString uid, QMap<QString,QString> properties);

    void selectObject(QString uid);

private:
    void createViews();

    void createDocuments();

    void createConnections();

    QnsbSketchView* sketch; /**< TODO */

    QnsbAuthorView* author; /**< TODO */

    QnsbNarrativeView* narrative; /**< TODO */

    QnsbDocument* document; /**< TODO */
};

#endif // QNSBVIEW_H
