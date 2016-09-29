#include <QtMath>

#include <cstdlib>
#include <iostream>

#include "boundingbox.h"

BoundingBox::BoundingBox(QObject* parent): QGraphicsScene(parent)
{
    itemToDraw = 0;
    this->drawEnabled = false;
}

void BoundingBox::mousePressEvent(QGraphicsSceneMouseEvent *event){
    origPoint = event->scenePos().x();
    endPoint = event->scenePos().y();
}

void BoundingBox::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    if(this->drawEnabled){
    //delete itemToDraw;
        if( itemToDraw == 0){
            itemToDraw = new QGraphicsRectItem;
            this->addItem(itemToDraw);
            itemToDraw->setPen(QPen(Qt::black, 3, Qt::SolidLine));
        }
        origPoint2 = event->scenePos().x();
        endPoint2 = event->scenePos().y();
        weigth = origPoint2 - origPoint;
        heigth = endPoint2 - endPoint;

        if( weigth < 0 && heigth < 0){
            weigth = origPoint - origPoint2;
            heigth = endPoint - endPoint2;
            itemToDraw->setRect(origPoint2, endPoint2, weigth, heigth);
        }
        else if( weigth > 0 && heigth > 0){
            itemToDraw->setRect(origPoint, endPoint, weigth, heigth);
        }
        else if( weigth < 0 && heigth > 0){
            weigth = origPoint - origPoint2;
            itemToDraw->setRect(origPoint2, endPoint, weigth, heigth);
        }
        else{
            heigth = endPoint - endPoint2;
            itemToDraw->setRect(origPoint, endPoint2, weigth, heigth);
        }
    }
}

void BoundingBox::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    itemToDraw = 0;
    this->drawEnabled = false;
    QGraphicsScene::mouseReleaseEvent(event);
}

void BoundingBox::enableDraw()
{
    this->drawEnabled = true;
}
