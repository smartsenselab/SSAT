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
    double mouse_posX = event->pos().x();
    double mouse_posY = event->pos().y();

    if( (this->isSelected()) && (event->button() == Qt::LeftButton) )
    {
        int adjust = 20;

        if( (mouse_posX > this->boundingRect().left() + adjust) &&
                (mouse_posX < this->boundingRect().right() - adjust) &&
                (mouse_posY < this->boundingRect().bottom() + adjust) &&
                (mouse_posY > this->boundingRect().bottom() - adjust) )
        {
            // bottom
            this->resizeMode = 1;
            this->pointY = mouse_posY;
            QApplication::setOverrideCursor(QCursor(Qt::SizeVerCursor));
        }
        else if( (mouse_posX > this->boundingRect().right() - adjust) &&
                 (mouse_posX < this->boundingRect().right() + adjust) &&
                 (mouse_posY < this->boundingRect().bottom() + adjust) &&
                 (mouse_posY > this->boundingRect().bottom() - adjust) )
        {
            // bottom right
            this->resizeMode = 2;
            this->pointX = mouse_posX;
            this->pointY = mouse_posY;
            QApplication::setOverrideCursor(QCursor(Qt::SizeFDiagCursor));
        }
        else if( (mouse_posX > this->boundingRect().right() - adjust) &&
                 (mouse_posX < this->boundingRect().right() + adjust) &&
                 (mouse_posY < this->boundingRect().bottom() - adjust) &&
                 (mouse_posY > this->boundingRect().top() + adjust) )
        {
            // right
            this->resizeMode = 3;
            this->pointX = mouse_posX;
            QApplication::setOverrideCursor(QCursor(Qt::SizeHorCursor));
        }
        else if( (mouse_posX > this->boundingRect().left() - adjust) &&
                 (mouse_posX < this->boundingRect().left() + adjust) &&
                 (mouse_posY > this->boundingRect().top() - adjust) &&
                 (mouse_posY < this->boundingRect().top() + adjust) )
        {
            // top left
            this->resizeMode = 4;
            this->pointX = mouse_posX;
            this->pointY = mouse_posY;
            QApplication::setOverrideCursor(QCursor(Qt::SizeFDiagCursor));
        }
        else if( (mouse_posX > this->boundingRect().left() - adjust) &&
                 (mouse_posX < this->boundingRect().left() + adjust) &&
                 (mouse_posY < this->boundingRect().bottom() - adjust) &&
                 (mouse_posY > this->boundingRect().top() + adjust))
        {
            // left
            this->resizeMode = 5;
            this->pointX = mouse_posX;
            QApplication::setOverrideCursor(QCursor(Qt::SizeHorCursor));
        }
        else if( (mouse_posX > this->boundingRect().left() - adjust) &&
                 (mouse_posX < this->boundingRect().left() + adjust) &&
                 (mouse_posY < this->boundingRect().bottom() + adjust) &&
                 (mouse_posY > this->boundingRect().bottom() - adjust))
        {
            // bottom left
            this->resizeMode = 6;
            this->pointX = mouse_posX;
            this->pointY = mouse_posY;
            QApplication::setOverrideCursor(QCursor(Qt::SizeBDiagCursor));
        }
        else if( (mouse_posX > this->boundingRect().left() + adjust) &&
                 (mouse_posX < this->boundingRect().right() - adjust) &&
                 (mouse_posY < this->boundingRect().top() + adjust) &&
                 (mouse_posY > this->boundingRect().top() - adjust))
        {
            // top
            this->resizeMode = 7;
            this->pointY = mouse_posY;
            QApplication::setOverrideCursor(QCursor(Qt::SizeVerCursor));
        }
        else if( (mouse_posX < this->boundingRect().right() + adjust) &&
                 (mouse_posX > this->boundingRect().right() - adjust) &&
                 (mouse_posY < this->boundingRect().top() + adjust) &&
                 (mouse_posY > this->boundingRect().top() - adjust))
        {
            // top right
            this->resizeMode = 8;
            this->pointX = mouse_posX;
            this->pointY = mouse_posY;
            QApplication::setOverrideCursor(QCursor(Qt::SizeBDiagCursor));
        }
        else
        {
            this->resizeMode = 0;
            QApplication::setOverrideCursor(QCursor(Qt::OpenHandCursor));
        }
    }

    this->update();
    QGraphicsItem::mousePressEvent(event);
}

void QBoundingBoxRectangle::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QApplication::setOverrideCursor(QCursor(Qt::ClosedHandCursor));
    QGraphicsItem::mouseMoveEvent(event);
}

void QBoundingBoxRectangle::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QApplication::setOverrideCursor(QCursor(Qt::OpenHandCursor));
    QGraphicsItem::mouseReleaseEvent(event);
}

