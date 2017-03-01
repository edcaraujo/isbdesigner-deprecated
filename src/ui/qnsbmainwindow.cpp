#include "qnsbmainwindow.h"

QnsbMainWindow::QnsbMainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    setWindowTitle("ISB Designer");

    createActions();
    createMenus();
    createToolBar();
    createStatusBar();
    createViews();
    createConnections();

    docname = "";
}

QnsbMainWindow::~QnsbMainWindow()
{

}

void  QnsbMainWindow::createActions()
{
     // new action
     newAction = new QAction(this);
     newAction->setEnabled(true);
     newAction->setText(tr("New"));
     newAction->setIcon(QIcon(":/icon/new"));
     newAction->setShortcut(QKeySequence("Ctrl+N"));

     // open action
     openAction = new QAction(this);
     openAction->setEnabled(true);
     openAction->setText(tr("Open..."));
     openAction->setIcon(QIcon(":/icon/open"));
     openAction->setShortcut(QKeySequence("Ctrl+O"));

     // save action
     saveAction = new QAction(this);
     saveAction->setEnabled(true);
     saveAction->setText(tr("Save"));
     saveAction->setIcon(QIcon(":/icon/save"));
     saveAction->setShortcut(QKeySequence("Ctrl+S"));

     // saveas action
     saveAsAction = new QAction(this);
     saveAsAction->setEnabled(false);
     saveAsAction->setText(tr("Save As..."));
     saveAsAction->setIcon(QIcon(":/icon/saveas"));
     saveAsAction->setShortcut(QKeySequence("Shift+Ctrl+S"));

     // close action
     closeAction = new QAction(this);
     closeAction->setEnabled(false);
     closeAction->setText(tr("Close"));
     closeAction->setIcon(QIcon(":/icon/close"));
     closeAction->setShortcut(QKeySequence("Ctrl+W"));

     // quit action
     quitAction = new QAction(this);
     quitAction->setEnabled(false);
     quitAction->setText(tr("Quit"));
     quitAction->setIcon(QIcon(":/icon/quit"));
     quitAction->setShortcut(QKeySequence("Ctrl+Q"));

     // import action
     importAction = new QAction(this);
     importAction->setEnabled(false);
     importAction->setText(tr("Import..."));
     importAction->setIcon(QIcon(":/icon/import"));

     // export action
     exportAction = new QAction(this);
     exportAction->setEnabled(true);
     exportAction->setText(tr("Export..."));
     exportAction->setIcon(QIcon(":/icon/export"));

     // undo action
     undoAction = new QAction(this);
     undoAction->setEnabled(false);
     undoAction->setText(tr("Undo"));
     undoAction->setIcon(QIcon(":/icon/undo"));
     undoAction->setShortcut(QKeySequence("Ctrl+Z"));

     // redo action
     redoAction = new QAction(this);
     redoAction->setEnabled(false);
     redoAction->setText(tr("Redo"));
     redoAction->setIcon(QIcon(":/icon/redo"));
     redoAction->setShortcut(QKeySequence("Ctrl+Y"));

     // cut action
     cutAction = new QAction(this);
     cutAction->setEnabled(false);
     cutAction->setText(tr("Cut"));
     cutAction->setIcon(QIcon(":/icon/cut"));
     cutAction->setShortcut(QKeySequence("Ctrl+X"));

     // copy action
     copyAction = new QAction(this);
     copyAction->setEnabled(false);
     copyAction->setText(tr("Copy"));
     copyAction->setIcon(QIcon(":/icon/copy"));
     copyAction->setShortcut(QKeySequence("Ctrl+C"));

     // paste action
     pasteAction = new QAction(this);
     pasteAction->setEnabled(false);
     pasteAction->setText(tr("Paste"));
     pasteAction->setIcon(QIcon(":/icon/paste"));
     pasteAction->setShortcut(QKeySequence("Ctrl+V"));

     // play action
     playAction = new QAction(this);
     playAction->setEnabled(false);
     playAction->setText(tr("Play"));
     playAction->setIcon(QIcon(":/icon/play"));

     // pause action
     pauseAction = new QAction(this);
     pauseAction->setEnabled(false);
     pauseAction->setText(tr("Pause"));
     pauseAction->setIcon(QIcon(":/icon/pause"));

     // stop action
     stopAction = new QAction(this);
     stopAction->setEnabled(false);
     stopAction->setText(tr("Stop"));
     stopAction->setIcon(QIcon(":/icon/stop"));

     // home action
     homeAction = new QAction(this);
     homeAction->setEnabled(false);
     homeAction->setText(tr("Home"));
     homeAction->setToolTip(tr("Go to the first chain"));
     homeAction->setIcon(QIcon(":/icon/home"));

     // next action
     nextAction = new QAction(this);
     nextAction->setEnabled(false);
     nextAction->setText(tr("Next"));
     nextAction->setToolTip(tr("Show the next chain"));
     nextAction->setIcon(QIcon(":/icon/next"));

     // previous action
     previousAction = new QAction(this);
     previousAction->setEnabled(false);
     previousAction->setText(tr("Previous"));
     previousAction->setToolTip(tr("Show the previous chain"));
     previousAction->setIcon(QIcon(":/icon/previous"));

     // sketch action
     sketchAction = new QAction(this);
     sketchAction->setEnabled(false);
     sketchAction->setCheckable(true);
     sketchAction->setChecked(false);
     sketchAction->setText(tr("Sketch"));
     sketchAction->setToolTip(tr("Show Sketching View"));
     sketchAction->setIcon(QIcon(":/icon/sketch"));

     // author action
     authorAction = new QAction(this);
     authorAction->setEnabled(false);
     authorAction->setCheckable(true);
     authorAction->setChecked(false);
     authorAction->setText(tr("Author"));
     authorAction->setToolTip(tr("Show Authoring View"));
     authorAction->setIcon(QIcon(":/icon/author"));

     // preview action
     previewAction = new QAction(this);
     previewAction->setEnabled(false);
     previewAction->setCheckable(true);
     previewAction->setChecked(false);
     previewAction->setText(tr("Preview"));
     previewAction->setToolTip(tr("Show Preview"));
     previewAction->setIcon(QIcon(":/icon/preview"));

     // chain action
     narrativeAction = new QAction(this);
     narrativeAction->setEnabled(false);
     narrativeAction->setCheckable(true);
     narrativeAction->setChecked(false);
     narrativeAction->setText(tr("Narrative"));
     narrativeAction->setToolTip(tr("Show Narrative View"));
     narrativeAction->setIcon(QIcon(":/icon/narrative"));

     // preferences action
     preferencesAction = new QAction(this);
     preferencesAction->setEnabled(false);
     preferencesAction->setText(tr("Preferences..."));
     preferencesAction->setIcon(QIcon(":/icon/preferences"));

     // about action
     aboutAction = new QAction(this);
     aboutAction->setEnabled(false);
     aboutAction->setText(tr("About..."));
     aboutAction->setIcon(QIcon(":/icon/about"));

     // view action group
     viewActionGroup = new QActionGroup(this);
     viewActionGroup->setEnabled(true);
     viewActionGroup->setExclusive(true);

     viewActionGroup->addAction(sketchAction);
     viewActionGroup->addAction(authorAction);
     viewActionGroup->addAction(previewAction);
     viewActionGroup->addAction(narrativeAction);
}

void  QnsbMainWindow::createMenus()
{
    // file menu
    fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addSeparator();
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exportAction);
    fileMenu->addAction(importAction);
    fileMenu->addSeparator();
    fileMenu->addAction(closeAction);
    fileMenu->addSeparator();
    fileMenu->addAction(quitAction);

    // edit menu
    editMenu = menuBar()->addMenu(tr("Edit"));
    editMenu->addAction(undoAction);
    editMenu->addAction(redoAction);
    editMenu->addSeparator();
    editMenu->addAction(cutAction);
    editMenu->addAction(copyAction);
    editMenu->addAction(pasteAction);

    // insert menu
    insertMenu = menuBar()->addMenu(tr("Insert"));

    // navigation menu
    navigationMenu = menuBar()->addMenu(tr("Navigation"));
    navigationMenu->addAction(nextAction);
    navigationMenu->addAction(previousAction);
    navigationMenu->addSeparator();
    navigationMenu->addAction(homeAction);

    // playback menu
    playbackMenu = menuBar()->addMenu(tr("Playback"));
    playbackMenu->addAction(playAction);
    playbackMenu->addAction(pauseAction);
    playbackMenu->addAction(stopAction);

    // view menu
    viewMenu = menuBar()->addMenu(tr("View"));
    viewMenu->addAction(sketchAction);
    viewMenu->addAction(authorAction);
//    viewMenu->addAction(previewAction);
    viewMenu->addAction(narrativeAction);

    // window menu
    windowMenu = menuBar()->addMenu(tr("Window"));

    windowMenu->addAction(preferencesAction);

    // help menu
    helpMenu = menuBar()->addMenu(tr("Help"));
    helpMenu->addAction(aboutAction);
}

void  QnsbMainWindow::createToolBar()
{
    // file toolbar
    fileToolbar = addToolBar(tr("File"));

    fileToolbar->setMovable(false);
    fileToolbar->setFloatable(false);
    fileToolbar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    fileToolbar->addAction(newAction);
//    fileToolbar->addAction(exportAction);
    fileToolbar->addAction(openAction);
    fileToolbar->addAction(saveAction);
    fileToolbar->addSeparator();

    // edit toolbar
    editToolbar = addToolBar(tr("Edit"));

    editToolbar->setMovable(false);
    editToolbar->setFloatable(false);
    editToolbar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    editToolbar->addAction(undoAction);
    editToolbar->addAction(redoAction);
    editToolbar->addSeparator();
    editToolbar->addAction(cutAction);
    editToolbar->addAction(copyAction);
    editToolbar->addAction(pasteAction);
    editToolbar->addSeparator();

    // view toolbar
    viewToolbar = addToolBar(tr("View"));

    viewToolbar->setMovable(false);
    viewToolbar->setFloatable(false);
    viewToolbar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    viewToolbar->addAction(sketchAction);
    viewToolbar->addAction(authorAction);
//    viewToolbar->addAction(previewAction);
    viewToolbar->addAction(narrativeAction);
    viewToolbar->addSeparator();

    // window toolbar
    windowToolbar = addToolBar(tr("Window"));

    windowToolbar->setMovable(false);
    windowToolbar->setFloatable(false);
    windowToolbar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    windowToolbar->addAction(preferencesAction);

#ifdef Q_WS_MACX
    setUnifiedTitleAndToolBarOnMac(true);
#endif
}

void  QnsbMainWindow::createViews()
{
    view = new QnsbView(this);

    setCentralWidget(view);
}

void  QnsbMainWindow::createConnections()
{
    connect(newAction, SIGNAL(triggered()), SLOT(performNew()));
    connect(openAction, SIGNAL(triggered()), SLOT(performOpen()));
    connect(saveAction, SIGNAL(triggered()), SLOT(performSave()));
    connect(exportAction, SIGNAL(triggered()), SLOT(performExport()));

    connect(sketchAction, SIGNAL(triggered()), SLOT(showSketch()));
    connect(authorAction, SIGNAL(triggered()), SLOT(showAuthor()));
    connect(previewAction, SIGNAL(triggered()), SLOT(showPreview()));
    connect(narrativeAction, SIGNAL(triggered()), SLOT(showNarrative()));
}

void  QnsbMainWindow::createStatusBar()
{
    statusBar();
}

void QnsbMainWindow::performNew()
{
    view->clean();

    QMap<QString,QString> cp;

    cp["id"] = "seq0";
    cp["type"] = "home";
    cp["interface"] = "main";

    QMap<QString,QString> dp;

    dp["name"] = "main";

    view->addChain("DEFAULT-CHAIN", cp);
    view->selectChain("DEFAULT-CHAIN");

    view->addDimension("DEFAULT-DIMENSION", "DEFAULT-CHAIN", dp);
    view->selectDimension("DEFAULT-DIMENSION");

    view->addPanel("DEFAULT-PANEL", "DEFAULT-DIMENSION", QMap<QString,QString>());
    view->selectPanel("DEFAULT-DIMENSION");

    view->showSketch();

    sketchAction->setEnabled(true);

    sketchAction->setEnabled(true);
    sketchAction->setChecked(true);

    narrativeAction->setEnabled(true);
    authorAction->setEnabled(true);
}

void QnsbMainWindow::performOpen()
{
    view->clean();

    QString fs = QFileDialog::getOpenFileName(this,"Open File");

    if (fs != ""){
        view->load(fs);

        docname = fs;

        view->showNarrative();

        sketchAction->setEnabled(true);
        sketchAction->setChecked(true);

        narrativeAction->setEnabled(true);

        sketchAction->setEnabled(true);
        authorAction->setEnabled(true);

        narrativeAction->setEnabled(true);
        narrativeAction->setChecked(true);
    }
}

void QnsbMainWindow::performSave()
{
    QString fs = QFileDialog::getSaveFileName(this,"Save File");

    if (fs != ""){
        view->save(fs);

        docname = fs;
    }
}

void QnsbMainWindow::performExport()
{
    QString data = view->getExportData();

    emit dataExported(data);
}

void QnsbMainWindow::showSketch()
{
    view->showSketch();
}

void QnsbMainWindow::showAuthor()
{
    view->showAuthor();
}

void QnsbMainWindow::showPreview()
{

}

void QnsbMainWindow::showNarrative()
{
    view->showNarrative();
}
