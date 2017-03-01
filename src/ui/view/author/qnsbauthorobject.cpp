#include "qnsbauthorobject.h"

#include <QMimeData>

QnsbAuthorObject::QnsbAuthorObject(QnsbGraphicsItem* parent)
    : QnsbGraphicsItem(parent)
{
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsFocusable, true);

    setMoving(false);
    setResizing(false);
    setSelected(false);
    setInstanceChange(false);

    setInstanceID(getUid());
    setStatusID(getUid());
    setLastStatusID("");
    setSrc("");

    createActions();
    createMenus();
    createConnections();

    setAcceptDrops(true);

    properties = new QDialog();

    d.setupUi(properties);
}

QnsbAuthorObject::~QnsbAuthorObject()
{

}

void QnsbAuthorObject::setMoving(bool moving)
{
    this->moving = moving;
}

bool QnsbAuthorObject::isMoving()
{
    return moving;
}

bool QnsbAuthorObject::isInstanceChange()
{
    return instanceChange;
}

void QnsbAuthorObject::setInstanceChange(bool instanceChange)
{
    this->instanceChange = instanceChange;
}

void QnsbAuthorObject::setResizing(bool resizing)
{
    this->resizing = resizing;
}

bool QnsbAuthorObject::isResizing()
{
    return resizing;
}

void QnsbAuthorObject::setSelected(bool selected)
{
    this->selected = selected;
}

bool QnsbAuthorObject::isSelected()
{
    return selected;
}

qreal QnsbAuthorObject::getTop() const
{
    return top;
}

void QnsbAuthorObject::setTop(qreal top)
{
    this->top = top;

    QnsbGraphicsItem::setTop(top-4);
}

qreal QnsbAuthorObject::getMoveTop()
{
    return moveTop;
}

void QnsbAuthorObject::setMoveTop(qreal moveTop)
{
    this->moveTop = moveTop;
}

qreal QnsbAuthorObject::getPressTop()
{
    return pressTop;
}

void QnsbAuthorObject::setPressTop(qreal pressTop)
{
    this->pressTop = pressTop;
}

qreal QnsbAuthorObject::getResizeTop()
{
    return resizeTop;
}

void QnsbAuthorObject::setResizeTop(qreal resizeTop)
{
    this->resizeTop = resizeTop;
}

qreal QnsbAuthorObject::getLeft() const
{
    return left;
}

void QnsbAuthorObject::setLeft(qreal left)
{
    this->left = left;

    QnsbGraphicsItem::setLeft(left-4);
}

qreal QnsbAuthorObject::getMoveLeft()
{
    return moveLeft;
}

void QnsbAuthorObject::setMoveLeft(qreal moveLeft)
{
    this->moveLeft = moveLeft;
}

qreal QnsbAuthorObject::getPressLeft()
{
    return pressLeft;
}

void QnsbAuthorObject::setPressLeft(qreal pressLeft)
{
    this->pressLeft = pressLeft;
}

qreal QnsbAuthorObject::getResizeLeft()
{
    return resizeLeft;
}

void QnsbAuthorObject::setResizeLeft(qreal resizeLeft)
{
    this->resizeLeft = resizeLeft;
}

qreal QnsbAuthorObject::getWidth() const
{
    return width;
}

void QnsbAuthorObject::setWidth(qreal width)
{
    this->width = width;

    QnsbGraphicsItem::setWidth(width+8);
}

void QnsbAuthorObject::setPressWidth(qreal pressWidth)
{
    this->pressWidth = pressWidth;
}

qreal QnsbAuthorObject::getResizeWidth()
{
    return resizeWidth;
}

void QnsbAuthorObject::setResizeWidth(qreal resizeWidth)
{
    this->resizeWidth = resizeWidth;
}

qreal QnsbAuthorObject::getHeight() const
{
    return height;
}

void QnsbAuthorObject::setHeight(qreal height)
{
    this->height = height;

    QnsbGraphicsItem::setHeight(height+8);
}

qreal QnsbAuthorObject::getPressHeight()
{
    return pressHeight;
}

void QnsbAuthorObject::setPressHeight(qreal pressHeight)
{
    this->pressHeight = pressHeight;
}

qreal QnsbAuthorObject::getResizeHeight()
{
    return resizeHeight;
}

void QnsbAuthorObject::setResizeHeight(qreal resizeHeight)
{
    this->resizeHeight = resizeHeight;
}

int QnsbAuthorObject::getResizeType()
{
    return resizeType;
}

void QnsbAuthorObject::setResizeType(int resizeType)
{
    this->resizeType = resizeType;
}

QString QnsbAuthorObject::getType()
{
    return type;
}

void QnsbAuthorObject::setType(QString type)
{
    this->type = type;
}

void QnsbAuthorObject::setPanel(QnsbAuthorPanel* panel)
{
    this->panel = panel;
}

QnsbAuthorPanel* QnsbAuthorObject::getPanel() const
{
    return panel;
}

QString QnsbAuthorObject::getId() const
{
    return id;
}

void QnsbAuthorObject::setId(QString id)
{
    this->id = id;
}

QString QnsbAuthorObject::getSrc() const
{
    return src;
}

void QnsbAuthorObject::setSrc(QString src)
{
    this->src = src;

    img.load(src);
}

QString QnsbAuthorObject::getInstanceID() const
{
    return instanceID;
}

void QnsbAuthorObject::setInstanceID(QString instanceID)
{
    this->instanceID = instanceID;
}

QString QnsbAuthorObject::getStatusID() const
{
    return statusID;
}

void QnsbAuthorObject::setStatusID(QString statusID)
{
    setLastStatusID(this->statusID);

    this->statusID = statusID;
}

QString QnsbAuthorObject::getLastStatusID() const
{
    return lastStatusID;
}

void QnsbAuthorObject::setLastStatusID(QString lastStatusID)
{
    this->lastStatusID = lastStatusID;
}

QString QnsbAuthorObject::getVarValue() const
{
    return varvalue;
}

void QnsbAuthorObject::setVarValue(QString varvalue)
{
    this->varvalue = varvalue;
}

QString QnsbAuthorObject::getVarName() const
{
    return varname;
}

void QnsbAuthorObject::setVarName(QString varname)
{
    this->varname = varname;
}

void QnsbAuthorObject::adjust()
{

}

void QnsbAuthorObject::draw(QPainter* painter)
{
    painter->setRenderHint(QPainter::Antialiasing,false);

    if (type == "image"){
        painter->setBrush(QBrush("#FFFFCC"));

        if (selected){
            painter->setPen(QPen(QBrush(Qt::black), 0, Qt::DashLine));
        }

        if (src != ""){
            painter->drawPixmap(4,4,width-1,height-1,img);

        }else if (sketch != ""){
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

        painter->drawRect(4, 4, width-1, height-1);

        if (width > 32 && height > 32){
            painter->drawPixmap(8+4, 8+4, 24, 24,QPixmap(":/icon/video"));
        }

        if (preview != ""){
            painter->drawPixmap(4,4,width-1,height-1,QPixmap(preview));
//            painter->drawText(QRectF(36+4,12+4,getWidth()-40, getHeight()-16),"Video ("+id+")"+" : "+src);

        }else if (sketch != ""){
            painter->drawPixmap(4,4,width-1,height-1,QPixmap(sketch));

        }else{
            painter->drawText(QRectF(36+4,12+4,getWidth()-40, getHeight()-16),"Video ("+id+")");
        }

    }else if (type == "text"){
        painter->setBrush(QBrush("#E4F1FC"));

        if (selected){
            painter->setPen(QPen(QBrush(Qt::black), 0, Qt::DashLine));
        }

        painter->drawRect(4, 4, width-1, height-1);

        if (width > 32 && height > 32){
            painter->drawPixmap(8+4, 8+4, 24, 24,QPixmap(":/icon/text"));
        }

        if (src != ""){
            painter->drawText(QRectF(36+4,12+4,getWidth()-40, getHeight()-16),"Text ("+id+")"+" : "+src);

        }else{
            painter->drawText(QRectF(36+4,12+4,getWidth()-40, getHeight()-16),"Text ("+id+")");
        }

    }else if (type == "audio"){
        if (selected){
            painter->setPen(QPen(QBrush(Qt::black), 0, Qt::DashLine));
        }

        painter->drawPixmap(8+4, 8+4, 24, 24,QPixmap(":/icon/audio"));

        if (src != ""){
            painter->drawText(QRectF(36+4,12+4,getWidth()-40, getHeight()-16),"Audio ("+id+")"+" : "+src);

        }else{
            painter->drawText(QRectF(36+4,12+4,getWidth()-40, getHeight()-16),"Audio ("+id+")");
        }

    }else if (type == "script"){
        painter->setBrush(QBrush("#EEEEEE"));

        if (selected){
            painter->setPen(QPen(QBrush(Qt::black), 0, Qt::DashLine));
        }

        painter->drawRect(4, 4, width-1, height-1);

        painter->drawPixmap(8+4, 8+4, 24, 24,QPixmap(":/icon/preferences"));

        if (src != ""){
            painter->drawText(QRectF(36+4,12+4,getWidth()-40, getHeight()-16),"Script ("+id+")"+" : "+src);

        }else{
            painter->drawText(QRectF(36+4,12+4,getWidth()-40, getHeight()-16),"Script ("+id+")");
        }

    }else if (type == "variable"){
        if (selected){
            painter->setPen(QPen(QBrush(Qt::black), 0, Qt::DashLine));
        }

        painter->drawPixmap(8+4, 8+4, 24, 24,QPixmap(":/icon/variable"));

        if (src != ""){
            painter->drawText(QRectF(36+4,12+4,getWidth()-40, getHeight()-16),"Variable ("+id+")"+" : "+src);

        }else{
            painter->drawText(QRectF(36+4,12+4,getWidth()-40, getHeight()-16),"Variable ("+id+")");
        }
    }

    if (moving){
        painter->setBrush(Qt::NoBrush);
        painter->setPen(QPen(QBrush(Qt::black), 0));                // 0px = cosmetic border
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
            painter->drawRect(0,0,8,8);                               // topleft
            painter->drawRect((width+8)/2-4-1,0,8,8);                 // top
            painter->drawRect((width+8)-8-1,0,8,8);                   // topright
            painter->drawRect((width+8)-8-1,(height+8)/2-4-1,8,8);    // right
            painter->drawRect((width+8)-8-1,(height+8)-8-1,8,8);      // bottomright
            painter->drawRect((width+8)/2-4-1,(height+8)-8-1,8,8);    // bottom
            painter->drawRect(0,(height+8)-8-1,8,8);                  // bottomleft
            painter->drawRect(0,(height+8)/2-4-1,8,8);                // left
        }
    }
}

void QnsbAuthorObject::delineate(QPainterPath* painter) const
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

void QnsbAuthorObject::move(QGraphicsSceneMouseEvent* event)
{
    /* setting */
     qreal x = left;
     qreal y = top;

     /* setting minimal position */
     qreal minx;
     qreal miny;

     minx = 0;
     miny = 32;

     /* setting maximal position */
     qreal maxx;
     qreal maxy;

     maxx = panel->getWidth() - width;
//     maxy = panel->getHeight() - height;
     maxy = 256+32 - height;


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

void QnsbAuthorObject::resize(QGraphicsSceneMouseEvent* event)
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
    miny = 32;
    minw = -1; // not used
    minh = -1; // not used

    /* setting maximal bounds */
    qreal maxx;
    qreal maxy;
    qreal maxw;
    qreal maxh;

    maxx = panel->getWidth() - width;
//    maxy = panel->getHeight() - height;
    maxy = 256+32 - height;
    maxw = panel->getWidth();
//    maxh = panel->getHeight();
    maxh = 256+32;


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

void QnsbAuthorObject::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if (moving){
        move(event);

    }else if (resizing){
        resize(event);
    }
}

void QnsbAuthorObject::mousePressEvent(QGraphicsSceneMouseEvent* event)
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

void QnsbAuthorObject::mouseReleaseEvent(QGraphicsSceneMouseEvent*event)
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


void QnsbAuthorObject::createActions()
{
    // variable action
    variableAction = new QAction(this);
    variableAction->setText(tr("Variable"));
    variableAction->setIcon(QIcon(":/icon/variable"));

    variableAction->setEnabled(true);

    // source action
    sourceAction = new QAction(this);
    sourceAction->setText(tr("File..."));

    sourceAction->setEnabled(true);

    // preview action
    previewAction = new QAction(this);
    previewAction->setText(tr("Preview..."));

    previewAction->setEnabled(true);

    // property action
    propertyAction = new QAction(this);
    propertyAction->setText(tr("Properties"));

    propertyAction->setEnabled(false);


}

void QnsbAuthorObject::createMenus()
{
    // insert menu
    insertMenu = new QMenu();
    insertMenu->setTitle("Insert");
    insertMenu->addAction(variableAction);

    // context menu
    contextMenu = new QMenu();
    contextMenu->addMenu(insertMenu);
    contextMenu->addSeparator();
    contextMenu->addAction(sourceAction);
    contextMenu->addAction(previewAction);
    contextMenu->addSeparator();
    contextMenu->addAction(propertyAction);
}

void QnsbAuthorObject::createConnections()
{
    connect(variableAction,SIGNAL(triggered()), SIGNAL(variablePerformed()));

    connect(sourceAction, SIGNAL(triggered()), SLOT(performSource()));
    connect(previewAction, SIGNAL(triggered()), SLOT(performPreview()));
    connect(propertyAction, SIGNAL(triggered()), SLOT(performProperty()));
}

void QnsbAuthorObject::performSource()
{
    QString fs = QFileDialog::getOpenFileName();

    if (fs != ""){
        setSrc(fs);

        update();

        setInstanceChange(true);

        emit objectChanged(this);
    }
}

QString QnsbAuthorObject::getSketch() const
{
    return sketch;
}

void QnsbAuthorObject::setSketch(QString sketch)
{
    this->sketch = sketch;
}

QString QnsbAuthorObject::getPreview() const
{
    return preview;
}

void QnsbAuthorObject::setPreview(QString preview)
{
    this->preview = preview;
}

void QnsbAuthorObject::performPreview()
{

}

void QnsbAuthorObject::performProperty()
{
    if (varname != ""){
        d.lineEdit->setText(varname);
    }

    if (varvalue != ""){
        d.lineEdit_2->setText(varvalue);
    }

    if (properties->exec()){
        setStatusID(QUuid::createUuid().toString());

        setVarName(d.lineEdit->text());
        setVarValue(d.lineEdit_2->text());

        emit objectChanged(this);
    }
}

void QnsbAuthorObject::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    foreach(QUrl url, event->mimeData()->urls()){
        event->acceptProposedAction();

        return;
    }
}

void QnsbAuthorObject::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    foreach(QUrl url, event->mimeData()->urls()){
        QString name = url.toLocalFile();
        QString suffix = QFileInfo(name).suffix().toUpper();

        if (type == "image"){
            if(suffix=="PNG" || suffix=="JPEG" || suffix=="JPG"){
                event->acceptProposedAction(); src = name; update();

                setInstanceChange(true);

                setStatusID(QUuid::createUuid().toString());
                emit objectChanged(this);
            }
        }else if (type == "video"){
            if(suffix=="PNG" || suffix=="JPEG" || suffix=="JPG"){
                event->acceptProposedAction(); preview = name; update();

                setStatusID(QUuid::createUuid().toString());
                emit objectChanged(this);
            }
        }
    }
}

void QnsbAuthorObject::contextMenuEvent(QGraphicsSceneContextMenuEvent* event)
{
    QnsbGraphicsItem::contextMenuEvent(event);

    if (!event->isAccepted()){
        if (type == "variable"){
            propertyAction->setEnabled(true);
        }else{
            propertyAction->setEnabled(false);
        }

        if (type == "video"){
            previewAction->setEnabled(true);
        }else{
            previewAction->setEnabled(false);
        }

        contextMenu->exec(event->screenPos());

        event->accept();
    }
}

