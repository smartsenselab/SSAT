#include "qboundingboxrectangle.h"

QBoundingBoxRectangle::QBoundingBoxRectangle() : QGraphicsRectItem()
{
}

QBoundingBoxRectangle::QBoundingBoxRectangle(unsigned int _id) : QGraphicsRectItem()
{
    this->setIdentifier(_id);
}

unsigned int QBoundingBoxRectangle::getIdentifier()
{
    return this->identifier;
}

void QBoundingBoxRectangle::setIdentifier(unsigned int _id)
{
    this->identifier = _id;
}

void QBoundingBoxRectangle::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if( (this->isSelected()) && (event->button() == Qt::LeftButton) )
    {
        qDebug() << "BBOX is selected " << this->identifier;
        QGraphicsItem::mousePressEvent(event);
    }
}

void QBoundingBoxRectangle::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseMoveEvent(event);
}

void QBoundingBoxRectangle::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
}

int QBoundingBoxRectangle::type() const
{
}

