#include <QtMath>
#include <cstdlib>
#include <iostream>

#include "qboundingbox.h"
#include "boundingbox.h"

QBoundingBox::QBoundingBox(QObject* parent): QGraphicsScene(parent)
{
    itemToDraw = 0;
    this->drawEnabled = false;
}

void QBoundingBox::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(drawEnabled == 1){
        origPoint = event->scenePos().x();
        endPoint = event->scenePos().y();
    }
    else{
        QGraphicsScene::mousePressEvent(event);
    }
}

void QBoundingBox::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    if(this->drawEnabled){
        delete itemToDraw;
        //if(itemToDraw == 0){
            itemToDraw = new QGraphicsRectItem;
            this->addItem(itemToDraw);
            itemToDraw->setPen(QPen(Qt::black, 3, Qt::SolidLine));
        //}
        this->origPoint2 = event->scenePos().x();
        this->endPoint2 = event->scenePos().y();
        this->weigth = origPoint2 - origPoint;
        this->heigth = endPoint2 - endPoint;

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
    else{
        QGraphicsScene::mouseMoveEvent(event);
    }
}

void QBoundingBox::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    //itemToDraw = 0;
    this->drawEnabled = false;

    itemToDraw->setFlag(QGraphicsItem::ItemIsSelectable, true);
    itemToDraw->setFlag(QGraphicsItem::ItemIsMovable, true);

    QGraphicsScene::mouseReleaseEvent(event);
}

void QBoundingBox::enableDraw()
{
    itemToDraw = 0;
    this->drawEnabled = true;
}
