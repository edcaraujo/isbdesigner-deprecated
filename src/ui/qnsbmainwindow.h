#ifndef QNSBMAINWINDOW_H
#define QNSBMAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QActionGroup>
#include <QFileDialog>
#include <QToolBar>

#include "view/qnsbview.h"

class QnsbMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QnsbMainWindow(QWidget* parent = 0);

    virtual ~QnsbMainWindow();

protected slots:
    void performNew();

    void performOpen();

    void performSave();

    void performExport();

    void showSketch();

    void showAuthor();

    void showPreview();

    void showNarrative();

signals:
    void dataExported(QString data);

private:
    void createMenus();

    void createActions();

    void createViews();

    void createConnections();

    void createToolBar();

    void createStatusBar();

    QMenu* fileMenu;

    QMenu* editMenu;

    QMenu* insertMenu;

    QMenu* navigationMenu;

    QMenu* playbackMenu;

    QMenu* viewMenu;

    QMenu* windowMenu;

    QMenu* helpMenu;

    QToolBar* fileToolbar;

    QToolBar* editToolbar;

    QToolBar* viewToolbar;

    QToolBar* windowToolbar;

    QAction* newAction;

    QAction* openAction;

    QAction* saveAction;

    QAction* saveAsAction;

    QAction* importAction;

    QAction* exportAction;

    QAction* closeAction;

    QAction* quitAction;

    QAction* undoAction;

    QAction* redoAction;

    QAction* cutAction;

    QAction* copyAction;

    QAction* pasteAction;

    QAction* playAction;

    QAction* pauseAction;

    QAction* stopAction;

    QAction* homeAction;

    QAction* nextAction;

    QAction* previousAction;

    QAction* sketchAction;

    QAction* authorAction;

    QAction* previewAction;

    QAction* narrativeAction;

    QAction* preferencesAction;

    QAction* aboutAction;

    QActionGroup* viewActionGroup;

    QnsbView* view;

    QString docname;
};

#endif // QNSBMAINWINDOW_H
