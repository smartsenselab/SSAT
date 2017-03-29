#include "qboundingboxscene.h"

QBoundingBoxScene::QBoundingBoxScene(QObject* parent): QGraphicsScene(parent)
{
    this->itemToDraw = 0;

    this->moveEnabled = false;
    this->drawEnabled = false;

    this->heightD = 0;
    this->widthD = 0;
}

void QBoundingBoxScene::deleteBBox()
{
    foreach(QGraphicsItem *item, selectedItems())
    {
        removeItem(item);
        delete item;
    }
}

void QBoundingBoxScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    this->pointXa = event->scenePos().x();
    this->pointYa = event->scenePos().y();
    QGraphicsScene::mousePressEvent(event);
}

void QBoundingBoxScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
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

            this->itemToDraw = new QBoundingBoxRectangle(qrand() % 100);
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
        this->mouseMoveX = this->pointXa - event->scenePos().x(); // Init position - End position  X - Shift to the left
        this->mouseMoveY = this->pointYa - event->scenePos().y(); // Init position - End position  Y

        QGraphicsScene::mouseMoveEvent(event);
    }
}

void QBoundingBoxScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
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
        if (this->selectedItems().size() == 1)
        {
            QBoundingBoxRectangle *temp = static_cast<QBoundingBoxRectangle*>(this->selectedItems().first());

            qDebug() << "Clicked Box"
                     << "=" << selectedItems().first()->sceneBoundingRect().x()
                     << ":" << selectedItems().first()->sceneBoundingRect().y()
                     << ":" << selectedItems().first()->sceneBoundingRect().width()
                     << ":" << selectedItems().first()->sceneBoundingRect().height();
            qDebug() << "Identifier: " << temp->getIdentifier();
        }
        else if (this->selectedItems().size() > 1)
        {
            QList<QGraphicsItem*> temps = this->selectedItems();
            foreach(QGraphicsItem *item, temps)
            {
                QBoundingBoxRectangle *conv = static_cast<QBoundingBoxRectangle*>(item);
                qDebug() << "Identifier on Release: " << conv->getIdentifier();
            }
        }
    }

    QGraphicsScene::mouseReleaseEvent(event);
}

void QBoundingBoxScene::slot_drawFrameBboxes(const Frame &_frame)
{
    map<unsigned int, BoundingBox> bboxes = _frame.getBoxes();
    for(map<unsigned int, BoundingBox>::iterator it = bboxes.begin(); it != bboxes.end(); it++)
    {       
        unsigned int id = it->second.getId();
        qDebug() << id;
        this->itemToDraw = new QBoundingBoxRectangle(id);
        this->itemToDraw->setPen(QPen(Qt::yellow, 3, Qt::SolidLine));
        this->itemToDraw->setBrush(QBrush(QColor(255, 255, 0, 50)));
        this->itemToDraw->setRect(it->second.getX(),
                                  it->second.getY(),
                                  it->second.getW(),
                                  it->second.getH());
        // when going back to a frame, is possible to select and move the BBox already created
        this->itemToDraw->setFlag(QGraphicsItem::ItemIsSelectable, true);
        this->itemToDraw->setFlag(QGraphicsItem::ItemIsMovable, true);
        this->addItem(this->itemToDraw);
    }
}

void QBoundingBoxScene::slot_enableDraw()
{
    this->itemToDraw = 0;
    this->drawEnabled = true;
}

void QBoundingBoxScene ::keyPressEvent(QKeyEvent* e)
{
    switch(e->key())
    {
    case Qt::Key_Delete:
        this->removeItem(selectedItems().front());
    }
}
