#include "qnsbsketchobject.h"

#include <QMimeData>

QnsbSketchObject::QnsbSketchObject(QnsbGraphicsItem* parent)
    : QnsbGraphicsItem(parent)
{
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsFocusable, true);

    setMoving(false);
    setResizing(false);
    setSelected(false);

    setInstanceID(getUid());
    setStatusID(getUid());
    setLastStatusID("");
    setSrc("");

    createActions();
    createMenus();
    createConnections();

    setAcceptDrops(true);
}

QnsbSketchObject::~QnsbSketchObject()
{

}

void QnsbSketchObject::setMoving(bool moving)
{
    this->moving = moving;
}

bool QnsbSketchObject::isMoving()
{
    return moving;
}

void QnsbSketchObject::setResizing(bool resizing)
{
    this->resizing = resizing;
}

bool QnsbSketchObject::isResizing()
{
    return resizing;
}

void QnsbSketchObject::setSelected(bool selected)
{
    this->selected = selected;
}

bool QnsbSketchObject::isSelected()
{
    return selected;
}

qreal QnsbSketchObject::getTop() const
{
    return top;
}

void QnsbSketchObject::setTop(qreal top)
{
    this->top = top;

    QnsbGraphicsItem::setTop(top-4);
}

qreal QnsbSketchObject::getMoveTop()
{
    return moveTop;
}

void QnsbSketchObject::setMoveTop(qreal moveTop)
{
    this->moveTop = moveTop;
}

qreal QnsbSketchObject::getPressTop()
{
    return pressTop;
}

void QnsbSketchObject::setPressTop(qreal pressTop)
{
    this->pressTop = pressTop;
}

qreal QnsbSketchObject::getResizeTop()
{
    return resizeTop;
}

void QnsbSketchObject::setResizeTop(qreal resizeTop)
{
    this->resizeTop = resizeTop;
}

qreal QnsbSketchObject::getLeft() const
{
    return left;
}

void QnsbSketchObject::setLeft(qreal left)
{
    this->left = left;

    QnsbGraphicsItem::setLeft(left-4);
}

qreal QnsbSketchObject::getMoveLeft()
{
    return moveLeft;
}

void QnsbSketchObject::setMoveLeft(qreal moveLeft)
{
    this->moveLeft = moveLeft;
}

qreal QnsbSketchObject::getPressLeft()
{
    return pressLeft;
}

void QnsbSketchObject::setPressLeft(qreal pressLeft)
{
    this->pressLeft = pressLeft;
}

qreal QnsbSketchObject::getResizeLeft()
{
    return resizeLeft;
}

void QnsbSketchObject::setResizeLeft(qreal resizeLeft)
{
    this->resizeLeft = resizeLeft;
}

qreal QnsbSketchObject::getWidth() const
{
    return width;
}

void QnsbSketchObject::setWidth(qreal width)
{
    this->width = width;

    QnsbGraphicsItem::setWidth(width+8);
}

void QnsbSketchObject::setPressWidth(qreal pressWidth)
{
    this->pressWidth = pressWidth;
}

qreal QnsbSketchObject::getResizeWidth()
{
    return resizeWidth;
}

void QnsbSketchObject::setResizeWidth(qreal resizeWidth)
{
    this->resizeWidth = resizeWidth;
}

qreal QnsbSketchObject::getHeight() const
{
    return height;
}

void QnsbSketchObject::setHeight(qreal height)
{
    this->height = height;

    QnsbGraphicsItem::setHeight(height+8);
}

qreal QnsbSketchObject::getPressHeight()
{
    return pressHeight;
}

void QnsbSketchObject::setPressHeight(qreal pressHeight)
{
    this->pressHeight = pressHeight;
}

qreal QnsbSketchObject::getResizeHeight()
{
    return resizeHeight;
}

void QnsbSketchObject::setResizeHeight(qreal resizeHeight)
{
    this->resizeHeight = resizeHeight;
}

int QnsbSketchObject::getResizeType()
{
    return resizeType;
}

void QnsbSketchObject::setResizeType(int resizeType)
{
    this->resizeType = resizeType;
}

QString QnsbSketchObject::getType()
{
    return type;
}

void QnsbSketchObject::setType(QString type)
{
    this->type = type;
}

QString QnsbSketchObject::getVarValue() const
{
    return varvalue;
}

void QnsbSketchObject::setVarValue(QString varvalue)
{
    this->varvalue = varvalue;
}

QString QnsbSketchObject::getVarName() const
{
    return varname;
}

void QnsbSketchObject::setVarName(QString varname)
{
    this->varname = varname;
}

void QnsbSketchObject::setPanel(QnsbSketchPanel* panel)
{
    this->panel = panel;
}

QnsbSketchPanel* QnsbSketchObject::getPanel() const
{
    return panel;
}

QString QnsbSketchObject::getId() const
{
    return id;
}

void QnsbSketchObject::setId(QString id)
{
    this->id = id;
}

QString QnsbSketchObject::getInstanceID() const
{
    return instanceID;
}

void QnsbSketchObject::setInstanceID(QString instanceID)
{
    this->instanceID = instanceID;
}

QString QnsbSketchObject::getStatusID() const
{
    return statusID;
}

void QnsbSketchObject::setStatusID(QString statusID)
{
    setLastStatusID(this->statusID);

    this->statusID = statusID;
}

QString QnsbSketchObject::getSrc() const
{
    return src;
}

void QnsbSketchObject::setSrc(QString src)
{
    this->src = src;
}

QString QnsbSketchObject::getSketch() const
{
    return sketch;
}

void QnsbSketchObject::setSketch(QString sketch)
{
    this->sketch = sketch;
}

QString QnsbSketchObject::getPreview() const
{
    return preview;
}

void QnsbSketchObject::setPreview(QString preview)
{
    this->preview = preview;
}

QString QnsbSketchObject::getLastStatusID() const
{
    return lastStatusID;
}

void QnsbSketchObject::setLastStatusID(QString lastStatusID)
{
    this->lastStatusID = lastStatusID;
}

void QnsbSketchObject::adjust()
{

}

void QnsbSketchObject::draw(QPainter* painter)
{
    painter->setRenderHint(QPainter::Antialiasing,false);

    if (type == "image"){
        painter->setBrush(QBrush("#FFFFCC"));

        if (selected){
            painter->setPen(QPen(QBrush(Qt::black), 0, Qt::DashLine));
        }

        if (sketch != ""){
            painter->drawPixmap(4,4,width-1,height-1,QPixmap(sketch));

        }else{

            painter->drawRect(4, 4, width-1, height-1);

            if (width > 32 && height > 32){
                painter->drawPixmap(8+4, 8+4, 24, 24,QPixmap(":/icon/image"));
            }

            painter->drawText(QRectF(36+4,12+4,getWidth()-40, getHeight()-16),"Image ("+id+")");
        }

    }else if (type == "video"){
        painter->setBrush(QBrush("#E1FFE1"));

        if (selected){
            painter->setPen(QPen(QBrush(Qt::black), 0, Qt::DashLine));
        }

        if (sketch != ""){
            painter->drawPixmap(4,4,width-1,height-1,QPixmap(sketch));

        }else{
            painter->drawRect(4, 4, width-1, height-1);

            if (width > 32 && height > 32){
                painter->drawPixmap(8+4, 8+4, 24, 24,QPixmap(":/icon/video"));
            }

            painter->drawText(QRectF(36+4,12+4,getWidth()-40, getHeight()-16),"Video ("+id+")");
        }

    }else if (type == "text"){
        painter->setBrush(QBrush("#E4F1FC"));

        if (selected){
            painter->setPen(QPen(QBrush(Qt::black), 0, Qt::DashLine));
        }

        painter->drawRect(4, 4, width-1, height-1);

        painter->drawPixmap(8+4, 8+4, 24, 24,QPixmap(":/icon/text"));

        painter->drawText(QRectF(36+4,12+4,getWidth()-40, getHeight()-16),"Text ("+id+")");

    }else if (type == "audio"){
        if (selected){
            painter->setPen(QPen(QBrush(Qt::black), 0, Qt::DashLine));
        }

        painter->drawPixmap(8+4, 8+4, 24, 24,QPixmap(":/icon/audio"));

        painter->drawText(QRectF(36+4,12+4,getWidth()-40, getHeight()-16),"Audio ("+id+")");

    }else if (type == "script"){
        painter->setBrush(QBrush("#EEEEEE"));

        if (selected){
            painter->setPen(QPen(QBrush(Qt::black), 0, Qt::DashLine));
        }

        painter->drawRect(4, 4, width-1, height-1);

        painter->drawPixmap(8+4, 8+4, 24, 24,QPixmap(":/icon/preferences"));

        painter->drawText(QRectF(36+4,12+4,getWidth()-40, getHeight()-16),"Script ("+id+")");

    }else if (type == "variable"){
        if (selected){
            painter->setPen(QPen(QBrush(Qt::black), 0, Qt::DashLine));
        }

        painter->drawPixmap(8+4, 8+4, 24, 24,QPixmap(":/icon/variable"));

        painter->drawText(QRectF(36+4,12+4,getWidth()-40, getHeight()-16),"Variable ("+id+")");
    }

    if (moving){
        painter->setBrush(Qt::NoBrush);
        painter->setPen(QPen(QBrush(Qt::black), 0));            // 0px = cosmetic border
        painter->drawRect(getMoveLeft()+4-left,getMoveTop()+4-top,width-1,height-1);

    }else if (resizing){
        painter->setBrush(Qt::NoBrush);
        painter->setPen(QPen(QBrush(Qt::black), 0));                // 0px = cosmetic border
        painter->drawRect(getResizeLeft()+4-left,getResizeTop()+4-top,getResizeWidth()-1,getResizeHeight()-1);
    }


    if (selected){
        painter->setRenderHint(QPainter::Antialiasing,false);

        painter->setBrush(Qt::NoBrush);
        painter->setPen(QPen(QBrush(Qt::black), 0, Qt::DashLine));
        painter->drawRect(4, 4, width-1, height-1);

        painter->setBrush(QBrush(Qt::white));
        painter->setPen(QPen(QBrush(Qt::black), 0));

        if (type != "audio" && type != "variable"){
            painter->drawRect(0,0,8,8);                                         // topleft
            painter->drawRect((width+8)/2-4-1,0,8,8);                      // top
            painter->drawRect((width+8)-8-1,0,8,8);                        // topright
            painter->drawRect((width+8)-8-1,(height+8)/2-4-1,8,8);    // right
            painter->drawRect((width+8)-8-1,(height+8)-8-1,8,8);      // bottomright
            painter->drawRect((width+8)/2-4-1,(height+8)-8-1,8,8);    // bottom
            painter->drawRect(0,(height+8)-8-1,8,8);                       // bottomleft
            painter->drawRect(0,(height+8)/2-4-1,8,8);                     // left
        }
    }
}

void QnsbSketchObject::delineate(QPainterPath* painter) const
{
    painter->setFillRule(Qt::WindingFill);

    painter->addRect(4,4,width,height);

    if (selected && type != "audio" && type != "variable"){
        painter->addRect(0,0,8,8);                               // topleft
        painter->addRect((width+8)/2 - 4,0,8,8);                 // top
        painter->addRect((width+8) - 8,0,8,8);                   // topright
        painter->addRect((width+8) - 8,(height+8)/2 - 4,8,8);    // right
        painter->addRect((width+8) - 8,(height+8) - 8,8,8);      // bottomright
        painter->addRect((width+8)/2 - 4,(height+8) - 8,8,8);    // bottom
        painter->addRect(0,(height+8) - 8,8,8);                  // bottomleft
        painter->addRect(0,(height+8)/2 - 4,8,8);                // left
    }
}

void QnsbSketchObject::move(QGraphicsSceneMouseEvent* event)
{
    /* setting */
     qreal x = left;
     qreal y = top;

     /* setting minimal position */
     qreal minx;
     qreal miny;

     minx = 0;
     miny = 0;

     /* setting maximal position */
     qreal maxx;
     qreal maxy;

     maxx = panel->getWidth() - width;
//     maxy = panel->getHeight() - height;
     maxy = 256 - height;


     /* setting delta */
     qreal dx = event->pos().x() - getPressLeft(); // (x1 - x0)
     qreal dy = event->pos().y() - getPressTop();  // (y1 - y0)

     /* setting next position */
     qreal nextx = x + dx;
     qreal nexty = y + dy;

     /* adjusting */
     if (nextx < minx){
         nextx = minx;
     }

     if (nexty < miny){
         nexty = miny;
     }

     if (nextx > maxx){
         nextx = maxx;
     }

     if (nexty > maxy){
         nexty = maxy;
     }

     /* moving */
     setMoveTop(nexty);
     setMoveLeft(nextx);

     panel->update();
}

void QnsbSketchObject::resize(QGraphicsSceneMouseEvent* event)
{
    /* setting bounds */
    qreal x = left;
    qreal y = top;
    qreal w = width;
    qreal h = height;

    /* setting minimal bounds */
    qreal minx;
    qreal miny;
    qreal minw;
    qreal minh;

    minx = 0;
    miny = 0;
    minw = -1; // not used
    minh = -1; // not used

    /* setting maximal bounds */
    qreal maxx;
    qreal maxy;
    qreal maxw;
    qreal maxh;

    maxx = panel->getWidth() - width;
//    maxy = panel->getHeight() - height;
    maxy = 256 - height;
    maxw = panel->getWidth();
//    maxh = panel->getHeight();
    maxh = 256;


    /* setting delta */
    qreal dx = event->pos().x() - pressLeft;    // (x1 - x0)
    qreal dy = event->pos().y() - pressTop;     // (y1 - y0)
    qreal dw = -dx;
    qreal dh = -dy;

    /* setting next bounds */
    qreal nextx = x + dx;
    qreal nexty = y + dy;
    qreal nextw = w + dw;
    qreal nexth = h + dh;

    /* adjusting */
    switch(resizeType){

    /* adjusting TOPLEFT */
    case TopLeft:{
        if (nextx < minx){
            nextx = minx;
            nextw = x + w - minx;
        }

        if (nexty < miny){
            nexty = miny;
            nexth = y + h - miny;
        }

        break;
    }

    /* adjusting TOP */
    case Top:{
        nextx = x; // fixed x
        nextw = w; // fixed width

        if (nexty < miny){
            nexty = miny;
            nexth = y + h - miny;
        }

        break;
    }

    /* adjusting TOPRIGHT */
    case TopRight:{
        nextx = x; // fixed x

        nextw = w - dw;
        if (x + nextw > maxw){
            nextw = maxw - x;
        }

        if (nexty < miny){
            nexty = miny;
            nexth = y + h - miny;
        }

        break;
    }

    /* adjusting RIGHT */
    case Right:{
        nextx = x; // fixed x

        nextw = w - dw;
        if (x + nextw > maxw){
            nextw = maxw - x;
        }

        nexty = y; // fixed y
        nexth = h; // fixed height

        break;
    }

    /* adjusting BOTTOMRIGHT */
    case BottomRight:{
        nextx = x; // fixed x

        nextw = w - dw;
        if (x + nextw > maxw){
            nextw = maxw - x;
        }

        nexty = y; // fixed y

        nexth = h - dh;
        if (y + nexth > maxh){
            nexth = maxh - y;
        }

        break;
    }

    /* adjusting BOTTOM */
    case Bottom:{
        nextx = x; // fixed x
        nextw = w; // fixed width

        nexty = y; // fixed y

        nexth = h - dh;
        if (y + nexth > maxh){
            nexth = maxh - y;
        }

        break;
    }

    /* adjusting BOTTOMLEFT */
    case BottomLeft:{
        if (nextx < minx){
            nextx = minx;
            nextw = x + w - minx;
        }

        nexty = y; // fixed y

        nexth = h - dh;
        if (y + nexth > maxh){
            nexth = maxh - y;
        }

        break;
    }

    /* adjusting LEFT */
    case Left:{
        if (nextx < minx){
            nextx = minx;
            nextw = x + w - minx;
        }

        nexty = y; // fixed y
        nexth = h; // fixed height

        break;
    }
    }

    /* resizing */
    setResizeTop(nexty);
    setResizeLeft(nextx);
    setResizeWidth(nextw);
    setResizeHeight(nexth);

    panel->update();
}

void QnsbSketchObject::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if (moving){
        move(event);

    }else if (resizing){
        resize(event);
    }
}

void QnsbSketchObject::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (event->button() == Qt::RightButton){
        event->ignore();

    }else if (event->button() == Qt::LeftButton){
        selected = true;

        emit objectSelected(this);

        setPressTop(event->pos().y());
        setPressLeft(event->pos().x());
        setPressWidth(width);
        setPressHeight(height);

        // avoid flickering on first move
        setMoveTop(top);
        setMoveLeft(left);

        // avoid flickering on first resize
        setResizeTop(top);
        setResizeLeft(left);
        setResizeWidth(width);
        setResizeHeight(height);

        if (type != "audio" && type != "variable"){
            // if over TOPLEFT resize region
            if (QRectF(0,0,8,8).contains(event->pos())){
                setResizeType(TopLeft);
                setResizing(true);

            // if over TOP resize region
            }else if (QRectF((width+8)/2 - 4,0,8,8).contains(event->pos())){
                setResizeType(Top);
                setResizing(true);

            // if over TOPRIGHT resize region
            }else if (QRectF((width+8) - 8,0,8,8).contains(event->pos())){
                setResizeType(TopRight);
                setResizing(true);

            // if over RIGHT resize region
            }else if (QRectF((width+8) - 8,(height+8)/2 - 4,8,8).contains(event->pos())){
                setResizeType(Right);
                setResizing(true);

            // if over BOTTOMRIGHT resize region
            }else if (QRectF((width+8) - 8,(height+8) - 8,8,8).contains(event->pos())){
                setResizeType(BottomRight);
                setResizing(true);

            // if over BOTTOM resize region
            }else if (QRectF((width+8)/2 - 4,(height+8) - 8,8,8).contains(event->pos())){
                setResizeType(Bottom);
                setResizing(true);

            // if over BOTTOMLEFT resize region
            }else if (QRectF(0,(height+8) - 8,8,8).contains(event->pos())){
                setResizeType(BottomLeft);
                setResizing(true);

            // if over LEFT resize region
            }else if (QRectF(0,(height+8)/2 - 4,8,8).contains(event->pos())){
                setResizeType(Left);
                setResizing(true);

            // if not over any resize region
            }else{
                setMoving(true);
            }

        }else{
            setMoving(true);
        }
    }

    QnsbGraphicsItem::mousePressEvent(event);
}

void QnsbSketchObject::mouseReleaseEvent(QGraphicsSceneMouseEvent*event)
{
    if (moving){
        setMoving(false);

        if ((top != moveTop || left != moveLeft)){
            setTop(moveTop);
            setLeft(moveLeft);

            setStatusID(QUuid::createUuid().toString());

            emit objectChanged(this);
        }
    }

    if (resizing){
        setResizing(false);

        if ((top != resizeTop || left != resizeLeft || width != resizeWidth || height != resizeHeight)){
            if (resizeTop > top + height){
             setResizeHeight(resizeTop - (top + height));
             setResizeTop(top + height);
            }

            if (resizeLeft > left + width){
             setResizeWidth(resizeLeft - (left + width));
             setResizeLeft(left + width);
            }

            if (resizeWidth < 0){
                setResizeLeft(resizeLeft + resizeWidth);
                setResizeWidth(-resizeWidth);
            }

            if (resizeHeight < 0){
                setResizeTop(resizeTop + resizeHeight);
                setResizeHeight(-resizeHeight);
            }

            setTop(resizeTop);
            setLeft(resizeLeft);
            setWidth(resizeWidth);
            setHeight(resizeHeight);

            setStatusID(QUuid::createUuid().toString());

            emit objectChanged(this);
        }
    }

    panel->update();

    QnsbGraphicsItem::mouseReleaseEvent(event);
}


void QnsbSketchObject::createActions()
{
    // video action
    videoAction = new QAction(this);
    videoAction->setText(tr("Video"));
    videoAction->setIcon(QIcon(":/icon/video"));

    videoAction->setEnabled(true);

    // image action
    imageAction = new QAction(this);
    imageAction->setText(tr("Image"));
    imageAction->setIcon(QIcon(":/icon/image"));

    imageAction->setEnabled(true);

    // text action
    textAction = new QAction(this);
    textAction->setText(tr("Text"));
    textAction->setIcon(QIcon(":/icon/text"));

    textAction->setEnabled(true);

    // audio action
    audioAction = new QAction(this);
    audioAction->setText(tr("Audio"));
    audioAction->setIcon(QIcon(":/icon/audio"));

    audioAction->setEnabled(true);

    // script action
    scriptAction = new QAction(this);
    scriptAction->setText(tr("Script"));
    scriptAction->setIcon(QIcon(":/icon/preferences"));

    scriptAction->setEnabled(true);

    // script action
    sketchAction = new QAction(this);
    sketchAction->setText(tr("Sketch..."));

    sketchAction->setEnabled(true);

    // remove action
    removeAction = new QAction(this);
    removeAction->setText(tr("Remove"));

    removeAction->setEnabled(true);
}

void QnsbSketchObject::createMenus()
{
    // insert menu
    insertMenu = new QMenu();
    insertMenu->setTitle(tr("Insert"));

    insertMenu->setEnabled(true);

    insertMenu->addAction(videoAction);
    insertMenu->addAction(imageAction);
    insertMenu->addAction(textAction);
    insertMenu->addAction(audioAction);
    insertMenu->addSeparator();
    insertMenu->addAction(scriptAction);

    // context menu
    contextMenu = new QMenu();
    contextMenu->addMenu(insertMenu);
    contextMenu->addSeparator();
    contextMenu->addAction(sketchAction);
    contextMenu->addSeparator();
    contextMenu->addAction(removeAction);
}

void QnsbSketchObject::createConnections()
{
    connect(imageAction, SIGNAL(triggered()), SIGNAL(imagePeformed()));
    connect(videoAction, SIGNAL(triggered()), SIGNAL(videoPeformed()));
    connect(textAction, SIGNAL(triggered()), SIGNAL(textPeformed()));
    connect(audioAction, SIGNAL(triggered()), SIGNAL(audioPeformed()));
    connect(scriptAction, SIGNAL(triggered()), SIGNAL(scriptPeformed()));

    connect(sketchAction, SIGNAL(triggered()), SLOT(performSketch()));

    connect(removeAction, SIGNAL(triggered()), SLOT(performRemove()));

}

void QnsbSketchObject::performRemove()
{
    emit objectRemoved(this);
}

void QnsbSketchObject::performSketch()
{
    QString file = QFileDialog::getOpenFileName();

    if (file != ""){
        setStatusID(QUuid::createUuid().toString());

        setSketch(file); update(); emit objectChanged(this);
    }
}

void QnsbSketchObject::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    foreach(QUrl url, event->mimeData()->urls()){
        event->acceptProposedAction();

        return;
    }
}

void QnsbSketchObject::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    foreach(QUrl url, event->mimeData()->urls()){
        QString name = url.toLocalFile();
        QString suffix = QFileInfo(name).suffix().toUpper();

//        if (type == "image"){
            if(suffix=="PNG" || suffix=="JPEG" || suffix=="JPG"){
                event->acceptProposedAction(); sketch = name; update();

                setStatusID(QUuid::createUuid().toString());
                emit objectChanged(this);
            }
//        }else if (type == "video"){
//            if(suffix=="MP4" || suffix=="AVI"){
//                event->acceptProposedAction(); sketch = name; update();

//                setStatusID(QUuid::createUuid().toString());
//                emit objectChanged(this);
//            }
//        }
    }
}

void QnsbSketchObject::contextMenuEvent(QGraphicsSceneContextMenuEvent* event)
{
    QnsbGraphicsItem::contextMenuEvent(event);

    if (!event->isAccepted()){
        contextMenu->exec(event->screenPos());

        event->accept();
    }
}

