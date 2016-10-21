#include "qboundingbox.h"
#include "boundingbox.h"

QBoundingBox::QBoundingBox(QObject* parent): QGraphicsScene(parent)
{
    std::cout << this->items().size() << std::endl;
    this->itemToDraw = 0;
    this->moveEnabled = false;
    this->drawEnabled = false;
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
    if(this->drawEnabled)
    {
        this->pointXa = event->scenePos().x();
        this->pointYa = event->scenePos().y();
    }
    else
    {
        QGraphicsScene::mousePressEvent(event);
    }
}

void QBoundingBox::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    if(this->drawEnabled)
    {
        delete(this->itemToDraw);
        this->itemToDraw = NULL;

        this->itemToDraw = new QGraphicsRectItem;
        this->itemToDraw->setPen(QPen(Qt::yellow, 3, Qt::SolidLine));
        this->itemToDraw->setBrush(QBrush(QColor(255, 255, 0, 50)));
        this->addItem(itemToDraw);

        this->pointXb = event->scenePos().x();
        this->pointYb = event->scenePos().y();
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
    else
    {
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
        this->itemToDraw->setFlag(QGraphicsItem::ItemIsSelectable, true);
        this->itemToDraw->setFlag(QGraphicsItem::ItemIsMovable, true);
    }
}

void QBoundingBox::slot_enableDraw()
{
    this->itemToDraw = 0;
    this->drawEnabled = true;
}
