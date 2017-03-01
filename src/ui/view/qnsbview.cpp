#include "qnsbview.h"

QnsbView::QnsbView(QWidget* parent)
    : QStackedWidget(parent)
{
    createViews();
    createDocuments();
    createConnections();
}

QnsbView::~QnsbView()
{

}

void QnsbView::createViews()
{
    narrative = new QnsbNarrativeView(this);

    addWidget(narrative);

    sketch = new QnsbSketchView(this);

    addWidget(sketch);

    author = new QnsbAuthorView(this);

    addWidget(author);
}

void QnsbView::createDocuments()
{
    document = new QnsbDocument(this);
}

void QnsbView::createConnections()
{
    // sketching view connections
    connect(sketch, SIGNAL(chainAdded(QString,QMap<QString,QString>)), SLOT(addChain(QString,QMap<QString,QString>)));
    connect(sketch, SIGNAL(chainRemoved(QString)), SLOT(removeChain(QString)));
    connect(sketch, SIGNAL(chainChanged(QString,QMap<QString,QString>)), SLOT(changeChain(QString,QMap<QString,QString>)));
    connect(sketch, SIGNAL(chainSelected(QString)), SLOT(selectChain(QString)));

    connect(sketch, SIGNAL(dimensionAdded(QString,QString,QMap<QString,QString>)), SLOT(addDimension(QString,QString,QMap<QString,QString>)));
    connect(sketch, SIGNAL(dimensionRemoved(QString)), SLOT(removeDimension(QString)));
    connect(sketch, SIGNAL(dimensionChanged(QString,QMap<QString,QString>)), SLOT(changeDimension(QString,QMap<QString,QString>)));
    connect(sketch, SIGNAL(dimensionSelected(QString)), SLOT(selectDimension(QString)));

    connect(sketch, SIGNAL(linkAdded(QString,QString,QMap<QString,QString>)), SLOT(addLink(QString,QString,QMap<QString,QString>)));
    connect(sketch, SIGNAL(linkRemoved(QString)), SLOT(removeLink(QString)));
    connect(sketch, SIGNAL(linkChanged(QString,QMap<QString,QString>)), SLOT(changeLink(QString,QMap<QString,QString>)));
    connect(sketch, SIGNAL(linkSelected(QString)), SLOT(selectLink(QString)));

    connect(sketch, SIGNAL(panelAdded(QString,QString,QMap<QString,QString>)), SLOT(addPanel(QString,QString,QMap<QString,QString>)));
    connect(sketch, SIGNAL(panelRemoved(QString)), SLOT(removePanel(QString)));
    connect(sketch, SIGNAL(panelChanged(QString,QMap<QString,QString>)), SLOT(changePanel(QString,QMap<QString,QString>)));
    connect(sketch, SIGNAL(panelSelected(QString)), SLOT(selectPanel(QString)));

    connect(sketch, SIGNAL(objectAdded(QString,QString,QMap<QString,QString>)), SLOT(addObject(QString,QString,QMap<QString,QString>)));
    connect(sketch, SIGNAL(objectRemoved(QString)), SLOT(removeObject(QString)));
    connect(sketch, SIGNAL(objectChanged(QString,QMap<QString,QString>)), SLOT(changeObject(QString,QMap<QString,QString>)));
    connect(sketch, SIGNAL(objectSelected(QString)), SLOT(selectObject(QString)));

    // narrative view connections
    connect(narrative, SIGNAL(chainAdded(QString,QMap<QString,QString>)), SLOT(addChain(QString,QMap<QString,QString>)));
    connect(narrative, SIGNAL(chainRemoved(QString)), SLOT(removeChain(QString)));
    connect(narrative, SIGNAL(chainChanged(QString,QMap<QString,QString>)), SLOT(changeChain(QString,QMap<QString,QString>)));
    connect(narrative, SIGNAL(chainSelected(QString)), SLOT(selectChain(QString)));

    connect(narrative, SIGNAL(dimensionAdded(QString,QString,QMap<QString,QString>)), SLOT(addDimension(QString,QString,QMap<QString,QString>)));
    connect(narrative, SIGNAL(dimensionRemoved(QString)), SLOT(removeDimension(QString)));
    connect(narrative, SIGNAL(dimensionChanged(QString,QMap<QString,QString>)), SLOT(changeDimension(QString,QMap<QString,QString>)));
    connect(narrative, SIGNAL(dimensionSelected(QString)), SLOT(selectDimension(QString)));

    connect(narrative, SIGNAL(linkAdded(QString,QString,QMap<QString,QString>)), SLOT(addLink(QString,QString,QMap<QString,QString>)));
    connect(narrative, SIGNAL(linkRemoved(QString)), SLOT(removeLink(QString)));
    connect(narrative, SIGNAL(linkChanged(QString,QMap<QString,QString>)), SLOT(changeLink(QString,QMap<QString,QString>)));
    connect(narrative, SIGNAL(linkSelected(QString)), SLOT(selectLink(QString)));

    connect(narrative, SIGNAL(panelAdded(QString,QString,QMap<QString,QString>)), SLOT(addPanel(QString,QString,QMap<QString,QString>)));
    connect(narrative, SIGNAL(panelRemoved(QString)), SLOT(removePanel(QString)));
    connect(narrative, SIGNAL(panelChanged(QString,QMap<QString,QString>)), SLOT(changePanel(QString,QMap<QString,QString>)));
    connect(narrative, SIGNAL(panelSelected(QString)), SLOT(selectPanel(QString)));

    connect(narrative, SIGNAL(objectAdded(QString,QString,QMap<QString,QString>)), SLOT(addObject(QString,QString,QMap<QString,QString>)));
    connect(narrative, SIGNAL(objectRemoved(QString)), SLOT(removeObject(QString)));
    connect(narrative, SIGNAL(objectChanged(QString,QMap<QString,QString>)), SLOT(changeObject(QString,QMap<QString,QString>)));
    connect(narrative, SIGNAL(objectSelected(QString)), SLOT(selectObject(QString)));

    // author view connections
    connect(author, SIGNAL(chainAdded(QString,QMap<QString,QString>)), SLOT(addChain(QString,QMap<QString,QString>)));
    connect(author, SIGNAL(chainRemoved(QString)), SLOT(removeChain(QString)));
    connect(author, SIGNAL(chainChanged(QString,QMap<QString,QString>)), SLOT(changeChain(QString,QMap<QString,QString>)));
    connect(author, SIGNAL(chainSelected(QString)), SLOT(selectChain(QString)));

    connect(author, SIGNAL(dimensionAdded(QString,QString,QMap<QString,QString>)), SLOT(addDimension(QString,QString,QMap<QString,QString>)));
    connect(author, SIGNAL(dimensionRemoved(QString)), SLOT(removeDimension(QString)));
    connect(author, SIGNAL(dimensionChanged(QString,QMap<QString,QString>)), SLOT(changeDimension(QString,QMap<QString,QString>)));
    connect(author, SIGNAL(dimensionSelected(QString)), SLOT(selectDimension(QString)));

    connect(author, SIGNAL(linkAdded(QString,QString,QMap<QString,QString>)), SLOT(addLink(QString,QString,QMap<QString,QString>)));
    connect(author, SIGNAL(linkRemoved(QString)), SLOT(removeLink(QString)));
    connect(author, SIGNAL(linkChanged(QString,QMap<QString,QString>)), SLOT(changeLink(QString,QMap<QString,QString>)));
    connect(author, SIGNAL(linkSelected(QString)), SLOT(selectLink(QString)));

    connect(author, SIGNAL(panelAdded(QString,QString,QMap<QString,QString>)), SLOT(addPanel(QString,QString,QMap<QString,QString>)));
    connect(author, SIGNAL(panelRemoved(QString)), SLOT(removePanel(QString)));
    connect(author, SIGNAL(panelChanged(QString,QMap<QString,QString>)), SLOT(changePanel(QString,QMap<QString,QString>)));
    connect(author, SIGNAL(panelSelected(QString)), SLOT(selectPanel(QString)));

    connect(author, SIGNAL(objectAdded(QString,QString,QMap<QString,QString>)), SLOT(addObject(QString,QString,QMap<QString,QString>)));
    connect(author, SIGNAL(objectRemoved(QString)), SLOT(removeObject(QString)));
    connect(author, SIGNAL(objectChanged(QString,QMap<QString,QString>)), SLOT(changeObject(QString,QMap<QString,QString>)));
    connect(author, SIGNAL(objectSelected(QString)), SLOT(selectObject(QString)));
}

void QnsbView::addChain(QString uid, QMap<QString,QString> properties)
{
    sketch->addChain(uid, properties);
    narrative->addChain(uid, properties);
    author->addChain(uid, properties);

    document->addChain(uid, properties);
}

void QnsbView::removeChain(QString uid)
{
    sketch->removeChain(uid);
    narrative->removeChain(uid);
    author->removeChain(uid);

    document->removeChain(uid);
}

void QnsbView::changeChain(QString uid, QMap<QString,QString> properties)
{
    sketch->changeChain(uid, properties);
    narrative->changeChain(uid, properties);
    author->changeChain(uid, properties);

    document->changeChain(uid, properties);
}

void QnsbView::selectChain(QString uid)
{
    sketch->selectChain(uid);
    narrative->selectChain(uid);
    author->selectChain(uid);

    document->selectChain(uid);
}

void QnsbView::addDimension(QString uid, QString parent, QMap<QString,QString> properties)
{
    sketch->addDimension(uid, parent, properties);
    narrative->addDimension(uid, parent, properties);
    author->addDimension(uid, parent, properties);

    document->addDimension(uid, parent, properties);
}

void QnsbView::removeDimension(QString uid)
{
    sketch->removeDimension(uid);
    narrative->removeDimension(uid);
    author->removeDimension(uid);

    document->removeDimension(uid);
}

void QnsbView::changeDimension(QString uid, QMap<QString,QString> properties)
{
    sketch->changeDimension(uid, properties);
    narrative->changeDimension(uid, properties);
    author->changeDimension(uid, properties);

    document->changeDimension(uid, properties);
}

void QnsbView::selectDimension(QString uid)
{
    sketch->selectDimension(uid);
    narrative->selectDimension(uid);
    author->selectDimension(uid);

    document->selectDimension(uid);
}

void QnsbView::addLink(QString uid, QString parent, QMap<QString,QString> properties)
{
    sketch->addLink(uid, parent, properties);
    narrative->addLink(uid, parent, properties);
    author->addLink(uid, parent, properties);

    document->addLink(uid, parent, properties);
}

void QnsbView::removeLink(QString uid)
{
    sketch->removeLink(uid);
    narrative->removeLink(uid);
    author->removeLink(uid);

    document->removeLink(uid);
}

void QnsbView::changeLink(QString uid, QMap<QString,QString> properties)
{
    sketch->changeLink(uid, properties);
    narrative->changeLink(uid, properties);
    author->changeLink(uid, properties);

    document->changeLink(uid, properties);
}

void QnsbView::selectLink(QString uid)
{
    sketch->selectLink(uid);
    narrative->selectLink(uid);
    author->selectLink(uid);

    document->selectLink(uid);
}

void QnsbView::addPanel(QString uid, QString parent, QMap<QString,QString> properties)
{
    document->addPanel(uid, parent, properties);

    sketch->addPanel(uid, parent, properties);
    narrative->addPanel(uid, parent, properties);
    author->addPanel(uid, parent, properties);
}

void QnsbView::removePanel(QString uid)
{
    sketch->removePanel(uid);
    narrative->removePanel(uid);
    author->removePanel(uid);

    document->removePanel(uid);
}

void QnsbView::changePanel(QString uid, QMap<QString,QString> properties)
{
    sketch->changePanel(uid, properties);
    narrative->changePanel(uid, properties);
    author->changePanel(uid, properties);

    document->changePanel(uid, properties);
}

void QnsbView::selectPanel(QString uid)
{
    sketch->selectPanel(uid);
    narrative->selectPanel(uid);
    author->selectPanel(uid);

    document->selectPanel(uid);
}

void QnsbView::addObject(QString uid, QString parent, QMap<QString,QString> properties)
{
    sketch->addObject(uid, parent, properties);
    narrative->addObject(uid, parent, properties);
    author->addObject(uid, parent, properties);

    document->addObject(uid, parent, properties);
}

void QnsbView::removeObject(QString uid)
{
    sketch->removeObject(uid);
    narrative->removeObject(uid);
    author->removeObject(uid);

    document->removeObject(uid);
}

void QnsbView::changeObject(QString uid, QMap<QString,QString> properties)
{
    sketch->changeObject(uid, properties);
    narrative->changeObject(uid, properties);
    author->changeObject(uid, properties);

    document->changeObject(uid, properties);
}

void QnsbView::selectObject(QString uid)
{
    sketch->selectObject(uid);
    narrative->selectObject(uid);
    author->selectObject(uid);

    document->selectObject(uid);
}

void QnsbView::load(QString location)
{
    clean();

    connect(document, SIGNAL(chainAdded(QString,QMap<QString,QString>)), SLOT(addChain(QString,QMap<QString,QString>)));
    connect(document, SIGNAL(chainRemoved(QString)), SLOT(removeChain(QString)));
    connect(document, SIGNAL(chainChanged(QString,QMap<QString,QString>)), SLOT(changeChain(QString,QMap<QString,QString>)));
    connect(document, SIGNAL(chainSelected(QString)), SLOT(selectChain(QString)));

    connect(document, SIGNAL(dimensionAdded(QString,QString,QMap<QString,QString>)), SLOT(addDimension(QString,QString,QMap<QString,QString>)));
    connect(document, SIGNAL(dimensionRemoved(QString)), SLOT(removeDimension(QString)));
    connect(document, SIGNAL(dimensionChanged(QString,QMap<QString,QString>)), SLOT(changeDimension(QString,QMap<QString,QString>)));
    connect(document, SIGNAL(dimensionSelected(QString)), SLOT(selectDimension(QString)));

    connect(document, SIGNAL(linkAdded(QString,QString,QMap<QString,QString>)), SLOT(addLink(QString,QString,QMap<QString,QString>)));
    connect(document, SIGNAL(linkRemoved(QString)), SLOT(removeLink(QString)));
    connect(document, SIGNAL(linkChanged(QString,QMap<QString,QString>)), SLOT(changeLink(QString,QMap<QString,QString>)));
    connect(document, SIGNAL(linkSelected(QString)), SLOT(selectLink(QString)));

    connect(document, SIGNAL(panelAdded(QString,QString,QMap<QString,QString>)), SLOT(addPanel(QString,QString,QMap<QString,QString>)));
    connect(document, SIGNAL(panelRemoved(QString)), SLOT(removePanel(QString)));
    connect(document, SIGNAL(panelChanged(QString,QMap<QString,QString>)), SLOT(changePanel(QString,QMap<QString,QString>)));
    connect(document, SIGNAL(panelSelected(QString)), SLOT(selectPanel(QString)));

    connect(document, SIGNAL(objectAdded(QString,QString,QMap<QString,QString>)), SLOT(addObject(QString,QString,QMap<QString,QString>)));
    connect(document, SIGNAL(objectRemoved(QString)), SLOT(removeObject(QString)));
    connect(document, SIGNAL(objectChanged(QString,QMap<QString,QString>)), SLOT(changeObject(QString,QMap<QString,QString>)));
    connect(document, SIGNAL(objectSelected(QString)), SLOT(selectObject(QString)));

    document->load(location);

    disconnect(document, SIGNAL(chainAdded(QString,QMap<QString,QString>)));
    disconnect(document, SIGNAL(chainRemoved(QString)));
    disconnect(document, SIGNAL(chainChanged(QString,QMap<QString,QString>)));
    disconnect(document, SIGNAL(chainSelected(QString)));

    disconnect(document, SIGNAL(dimensionAdded(QString,QString,QMap<QString,QString>)));
    disconnect(document, SIGNAL(dimensionRemoved(QString)));
    disconnect(document, SIGNAL(dimensionChanged(QString,QMap<QString,QString>)));
    disconnect(document, SIGNAL(dimensionSelected(QString)));

    disconnect(document, SIGNAL(linkAdded(QString,QString,QMap<QString,QString>)));
    disconnect(document, SIGNAL(linkRemoved(QString)));
    disconnect(document, SIGNAL(linkChanged(QString,QMap<QString,QString>)));
    disconnect(document, SIGNAL(linkSelected(QString)));

    disconnect(document, SIGNAL(panelAdded(QString,QString,QMap<QString,QString>)));
    disconnect(document, SIGNAL(panelRemoved(QString)));
    disconnect(document, SIGNAL(panelChanged(QString,QMap<QString,QString>)));
    disconnect(document, SIGNAL(panelSelected(QString)));

    disconnect(document, SIGNAL(objectAdded(QString,QString,QMap<QString,QString>)));
    disconnect(document, SIGNAL(objectRemoved(QString)));
    disconnect(document, SIGNAL(objectChanged(QString,QMap<QString,QString>)));
    disconnect(document, SIGNAL(objectSelected(QString)));
}

void QnsbView::save(QString location)
{
    document->save(location);
}

void QnsbView::performExport(QString location)
{
    document->exportToNCL(location);
}

QString QnsbView::getExportData()
{
    return document->getExportData();
}

void QnsbView::clean()
{
    sketch->clean();
    narrative->clean();
    author->clean();

    document->clean();
}

void QnsbView::showSketch()
{
    setCurrentWidget(sketch);
}

void QnsbView::showAuthor()
{
    setCurrentWidget(author);
}

void QnsbView::showNarrative()
{
    setCurrentWidget(narrative);
    narrative->focusOnSelectedChain();

    narrative->update();
}
