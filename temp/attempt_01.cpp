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
    if(event->button() == Qt::LeftButton) {
        if(event->modifiers() == Qt::AltModifier) {
            qDebug() << "Custom item left clicked with shift key.";
            // add the item to the selection
            setSelected(true);
        } else if(event->modifiers() == Qt::ShiftModifier){
            qDebug() << "Custom item left clicked with alt key.";
            // resize the item
            double radius = boundingRect().width() / 2.0;
            _center = QPointF(boundingRect().topLeft().x() + pos().x() + radius, boundingRect().topLeft().y() + pos().y() + radius);
            QPointF pos = event->scenePos();
            qDebug() << boundingRect() << radius << this->pos() << pos << event->pos();
            double dist = sqrt(pow(_center.x()-pos.x(), 2) + pow(_center.y()-pos.y(), 2));
            if(dist / radius > 0.8) {
                qDebug() << dist << radius << dist / radius;
                _isResizing = true;
            } else {
                _isResizing = false;
            }
        } else {
            qDebug() << "Custom item left clicked.";
            QGraphicsItem::mousePressEvent(event);
            event->accept();
        }
    } else if(event->button() == Qt::RightButton) {
        qDebug() << "Custom item right clicked.";
        event->ignore();
    }
}

void QBoundingBoxRectangle::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->modifiers() == Qt::ShiftModifier && _isResizing){
        QPointF pos = event->scenePos();
        double dist = sqrt(pow(_center.x()-pos.x(), 2) + pow(_center.y()-pos.y(), 2));
        setRect(_center.x()-this->pos().x()-dist, _center.y()-this->pos().y()-dist, dist*2, dist*2);
    } else if(event->modifiers() != Qt::ShiftModifier) {
        qDebug() << "Custom item moved.";
        QGraphicsItem::mouseMoveEvent(event);
        qDebug()<<"moved"<<pos();
    }
}

void QBoundingBoxRectangle::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->modifiers() == Qt::ShiftModifier && _isResizing) {
        _isResizing = false;
    } else if(event->modifiers() != Qt::AltModifier) {
        QGraphicsItem::mouseReleaseEvent(event);
    }
}

int QBoundingBoxRectangle::type() const
{
    // Enable the use of qgraphicsitem_cast with this item.
    return UserType+1;
}

