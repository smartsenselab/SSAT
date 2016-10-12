#include "qboundingbox.h"
#include "boundingbox.h"

QBoundingBox::QBoundingBox(QObject* parent): QGraphicsScene(parent)
{
    this->itemToDraw = 0;
    this->moveEnabled = false;
    this->drawEnabled = false;
}

void QBoundingBox::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(this->drawEnabled == 1)
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
    if(this->drawEnabled){
        delete this->itemToDraw;

        this->itemToDraw = new QGraphicsRectItem;
        this->itemToDraw->setPen(QPen(Qt::black, 3, Qt::SolidLine));
        this->addItem(itemToDraw);

        this->pointXb = event->scenePos().x();
        this->pointYb = event->scenePos().y();
        this->weigth = this->pointXb - this->pointXa;
        this->heigth = this->pointYb - this->pointYa;

        std::cout << pointXa << "-" << pointYa << " = " << pointXb << "-" << pointYb << std::endl;

        if((this->weigth < 0) && (this->heigth < 0))
        {
            this->weigth = this->pointXa - this->pointXb;
            this->heigth = this->pointYa - this->pointYb;
            this->itemToDraw->setRect(
                        this->pointXb,
                        this->pointYb,
                        this->weigth,
                        this->heigth
                        );
        }
        else if((this->weigth > 0) && (this->heigth > 0))
        {
            this->itemToDraw->setRect(
                        this->pointXa,
                        this->pointYa,
                        this->weigth,
                        this->heigth);
        }
        else if((this->weigth < 0) && (this->heigth > 0))
        {
            this->weigth = this->pointXa - this->pointXb;
            this->itemToDraw->setRect(
                        this->pointXb,
                        this->pointYa,
                        this->weigth,
                        this->heigth
                        );
        }
        else
        {
            this->heigth = this->pointYa - this->pointYb;
            this->itemToDraw->setRect(
                        this->pointXa,
                        this->pointYb,
                        this->weigth,
                        this->heigth
                        );
        }
    }
    else
    {
        QGraphicsScene::mouseMoveEvent(event);
    }
}

void QBoundingBox::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    if((this->drawEnabled) && (this->itemToDraw != NULL))
    {
        this->drawEnabled = false;
        this->itemToDraw->setFlag(QGraphicsItem::ItemIsSelectable, true);
        this->itemToDraw->setFlag(QGraphicsItem::ItemIsMovable, true);
    }

    QGraphicsScene::mouseReleaseEvent(event);
}

void QBoundingBox::enableDraw()
{
    this->itemToDraw = 0;
    this->drawEnabled = true;
}
