#include <QtMath>

#include <cstdlib>
#include <iostream>

#include "qboundingbox.h"

QBoundingBox::QBoundingBox(QObject* parent): QGraphicsScene(parent)
{
    itemToDraw = 0;
}

void QBoundingBox::mousePressEvent(QGraphicsSceneMouseEvent *event){
    origPoint = event->scenePos().x();
    endPoint = event->scenePos().y();
}

void QBoundingBox::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
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

void QBoundingBox::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    itemToDraw = 0;
    QGraphicsScene::mouseReleaseEvent(event);
}
