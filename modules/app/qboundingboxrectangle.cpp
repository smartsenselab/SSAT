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
    qreal mousePosX = event->pos().x();
    qreal mousePosY = event->pos().y();

    if( (this->isSelected()) && (event->button() == Qt::LeftButton) )
    {
        qreal adjust = 15.0;

        QRectF bbox = this->sceneBoundingRect();
        this->pointXa = bbox.x();
        this->pointYa = bbox.y();
        this->pointXb = bbox.x() + bbox.width();
        this->pointYb = bbox.y() + bbox.height();

        if( (mousePosX > this->sceneBoundingRect().left()) &&
                (mousePosX < this->sceneBoundingRect().right()) &&
                (mousePosY < this->sceneBoundingRect().bottom() + adjust) &&
                (mousePosY > this->sceneBoundingRect().bottom() - adjust) )
        {
            // bottom
            this->resizeMode = 1;
            this->mouseX = mousePosX;
            this->mouseY = mousePosY;
            this->setFlag(QGraphicsItem::ItemIsMovable, false);

            QApplication::setOverrideCursor(QCursor(Qt::SizeVerCursor));
        }
        else if( (mousePosX > this->sceneBoundingRect().right() - adjust) &&
                 (mousePosX < this->sceneBoundingRect().right() + adjust) &&
                 (mousePosY < this->sceneBoundingRect().bottom()) &&
                 (mousePosY > this->sceneBoundingRect().top()) )
        {
            // right
            this->resizeMode = 2;
            this->mouseX = mousePosX;
            this->mouseY = mousePosY;
            this->setFlag(QGraphicsItem::ItemIsMovable, false);

            QApplication::setOverrideCursor(QCursor(Qt::SizeHorCursor));
        }
        else if( (mousePosX > this->sceneBoundingRect().left() - adjust) &&
                 (mousePosX < this->sceneBoundingRect().left() + adjust) &&
                 (mousePosY < this->sceneBoundingRect().bottom()) &&
                 (mousePosY > this->sceneBoundingRect().top()) )
        {
            // left
            this->resizeMode = 3;
            this->mouseX = mousePosX;
            this->mouseY = mousePosY;
            this->setFlag(QGraphicsItem::ItemIsMovable, false);

            QApplication::setOverrideCursor(QCursor(Qt::SizeHorCursor));
        }
        else if( (mousePosX > this->sceneBoundingRect().left()) &&
                 (mousePosX < this->sceneBoundingRect().right()) &&
                 (mousePosY < this->sceneBoundingRect().top() + adjust) &&
                 (mousePosY > this->sceneBoundingRect().top() - adjust) )
        {
            // top
            this->resizeMode = 4;
            this->mouseX = mousePosX;
            this->mouseY = mousePosY;
            this->setFlag(QGraphicsItem::ItemIsMovable, false);

            QApplication::setOverrideCursor(QCursor(Qt::SizeVerCursor));
        }
        else
        {
            this->resizeMode = 0;
            this->mouseX = mousePosX;
            this->mouseY = mousePosY;
            this->setFlag(QGraphicsItem::ItemIsMovable, true);

            QApplication::setOverrideCursor(QCursor(Qt::OpenHandCursor));
        }
    }

    QGraphicsItem::mousePressEvent(event);
}

void QBoundingBoxRectangle::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QApplication::setOverrideCursor(QCursor(Qt::ClosedHandCursor));

    qreal mousePosX = event->scenePos().x();
    qreal mousePosY = event->scenePos().y();

    if(this->resizeMode > 0)
    {
        switch(this->resizeMode)
        {
        case 1:
            // bottom
            if(mousePosY > this->pointYa)
            {
                qreal height = mousePosY - this->pointYa;
                qreal width = this->pointXb - this->pointXa;
                this->setRect(this->pointXa, this->pointYa, width, height);
                this->prepareGeometryChange();
            }
            break;

        case 2:
            // right
            if(mousePosX > this->pointXa)
            {
                qreal height = this->pointYb - this->pointYa;
                qreal width = mousePosX - this->pointXa;
                this->setRect(this->pointXa, this->pointYa, width, height);
                this->prepareGeometryChange();
            }
            break;

        case 3:
            // left
            if(mousePosX < this->pointXb)
            {
                qreal height = this->pointYb - this->pointYa;
                qreal width = (this->pointXb - mousePosX);
                this->setRect(mousePosX, this->pointYa, width, height);
                this->prepareGeometryChange();
            }
            break;

        case 4:
            // top
            if(mousePosY < this->pointYb)
            {
                qreal height = this->pointYb - mousePosY;
                qreal width = (this->pointXb - this->pointXa);
                this->setRect(this->pointXa, mousePosY, width, height);
                this->prepareGeometryChange();
            }
            break;
        }
    }

    this->update();
    QGraphicsItem::mouseMoveEvent(event);
}

void QBoundingBoxRectangle::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QRectF bbox = this->sceneBoundingRect();
    this->pointXa = bbox.x();
    this->pointYa = bbox.y();
    this->pointXb = bbox.x() + bbox.width();
    this->pointYb = bbox.y() + bbox.height();
    this->resizeMode = 0;

    this->prepareGeometryChange();
    this->setFlag(QGraphicsItem::ItemIsMovable, true);

    QApplication::setOverrideCursor(QCursor(Qt::ArrowCursor));
    QGraphicsItem::mouseReleaseEvent(event);
}

