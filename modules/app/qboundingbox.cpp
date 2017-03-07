#include "qboundingbox.h"
#include "boundingbox.h"
#include "qdebug.h"

QBoundingBox::QBoundingBox(QObject* parent): QGraphicsScene(parent)
{
//    std::cout << this->items().size() << std::endl;
    this->itemToDraw = 0;

    this->moveEnabled = false;
    this->drawEnabled = false;

    this->heightD = 0;
    this->widthD = 0;
}

void QBoundingBox::deleteBBox()
{
    foreach(QGraphicsItem *item, selectedItems())
    {
        removeItem(item);
        delete item;
    }
}

void QBoundingBox::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    this->pointXa = event->scenePos().x();
    this->pointYa = event->scenePos().y();
    QGraphicsScene::mousePressEvent(event);
}

void QBoundingBox::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    if(this->drawEnabled)
    {
        double mouse_posX = event->scenePos().x();
        double mouse_posY = event->scenePos().y();
        if(this->widthD == 0)
        {
            this->widthD = sceneRect().width();
        }
        if(this->heightD == 0)
        {
            this->heightD = sceneRect().height();
        }

        // the initial point must be inside the video resolution
        if((this->pointXa >= 0) && (this->pointYa >= 0) && (this->pointXa <= this->widthD) && (this->pointYa <= this->heightD))
        {
            delete(this->itemToDraw);
            this->itemToDraw = NULL;

            this->itemToDraw = new QGraphicsRectItem;
            this->itemToDraw->setPen(QPen(Qt::yellow, 3, Qt::SolidLine));
            this->itemToDraw->setBrush(QBrush(QColor(255, 255, 0, 50)));
            this->addItem(itemToDraw);


            if(mouse_posX < 0) mouse_posX = 0;
            if(mouse_posY < 0) mouse_posY = 0;
            if(mouse_posX > this->widthD) mouse_posX = this->widthD;
            if(mouse_posY > this->heightD) mouse_posY = this->heightD;

            this->pointXb = mouse_posX;
            this->pointYb = mouse_posY;
            this->width = this->pointXb - this->pointXa;
            this->height = this->pointYb - this->pointYa;

            if((this->width < 0) && (this->height < 0))
            {
                this->width = this->pointXa - this->pointXb;
                this->height = this->pointYa - this->pointYb;
                this->itemToDraw->setRect(
                            this->pointXb,
                            this->pointYb,
                            this->width,
                            this->height
                            );
                this->box.x = static_cast<int>(this->pointXb);
                this->box.y = static_cast<int>(this->pointYb);
                this->box.width = static_cast<int>(this->width);
                this->box.height = static_cast<int>(this->height);
            }
            else if((this->width > 0) && (this->height > 0))
            {
                this->itemToDraw->setRect(
                            this->pointXa,
                            this->pointYa,
                            this->width,
                            this->height);
                this->box.x = static_cast<int>(this->pointXa);
                this->box.y = static_cast<int>(this->pointYa);
                this->box.width = static_cast<int>(this->width);
                this->box.height = static_cast<int>(this->height);
            }
            else if((this->width < 0) && (this->height > 0))
            {
                this->width = this->pointXa - this->pointXb;
                this->itemToDraw->setRect(
                            this->pointXb,
                            this->pointYa,
                            this->width,
                            this->height
                            );
                this->box.x = static_cast<int>(this->pointXb);
                this->box.y = static_cast<int>(this->pointYa);
                this->box.width = static_cast<int>(this->width);
                this->box.height = static_cast<int>(this->height);
            }
            else
            {
                this->height = this->pointYa - this->pointYb;
                this->itemToDraw->setRect(
                            this->pointXa,
                            this->pointYb,
                            this->width,
                            this->height
                            );
                this->box.x = static_cast<int>(this->pointXa);
                this->box.y = static_cast<int>(this->pointYb);
                this->box.width = static_cast<int>(this->width);
                this->box.height = static_cast<int>(this->height);
            }
        }
    }
    else
    {
        this->mouseMoveX = this->pointXa - event->scenePos().x(); // Init position - End position  X - Deslocamento para a esquerda
        this->mouseMoveY = this->pointYa - event->scenePos().y(); // Init position - End position  Y

//        qDebug() << "X = " << this->box.x - mouseMoveX << endl;
//        qDebug() << "Y = " << this->box.y - mouseMoveY << endl;
//        qDebug() << "W = " << this->box.width << endl;
//        qDebug() << "H = " << this->box.height << endl;


        QGraphicsScene::mouseMoveEvent(event);
    }
}

void QBoundingBox::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if((this->drawEnabled) && (this->itemToDraw != NULL))
    {
        this->drawEnabled = false;
        this->itemToDraw->setFlag(QGraphicsItem::ItemIsSelectable, true);
        this->itemToDraw->setFlag(QGraphicsItem::ItemIsMovable, true);
        emit this->signal_addBoundingBoxToCore(this->box);
    }
    else
    {
//        this->box.x = static_cast<int>(this->box.x - mouseMoveX);
//        this->box.y = static_cast<int>(this->box.y - mouseMoveY);

    }

    QGraphicsScene::mouseReleaseEvent(event);
}

void QBoundingBox::slot_drawFrameBboxes(const Frame _frame)
{
    map<string, BoundingBox> bboxes = _frame.getBoxes();
    for(map<string, BoundingBox>::iterator it = bboxes.begin(); it != bboxes.end(); it++)
    {
        this->itemToDraw = new QGraphicsRectItem;
        this->itemToDraw->setPen(QPen(Qt::yellow, 3, Qt::SolidLine));
        this->itemToDraw->setBrush(QBrush(QColor(255, 255, 0, 50)));
        this->addItem(this->itemToDraw);
        this->itemToDraw->setRect(it->second.getX(),
                                  it->second.getY(),
                                  it->second.getW(),
                                  it->second.getH());
        this->itemToDraw->setFlag(QGraphicsItem::ItemIsSelectable, true); // when come back to a frame, is possible to select and move the BBox already created
        this->itemToDraw->setFlag(QGraphicsItem::ItemIsMovable, true);
    }
}

void QBoundingBox::slot_enableDraw()
{
    this->itemToDraw = 0;
    this->drawEnabled = true;
}

void QBoundingBox ::keyPressEvent(QKeyEvent* e)
{
    switch(e->key())
{
    case Qt::Key_Delete:
        removeItem(selectedItems().front());
    }
}
