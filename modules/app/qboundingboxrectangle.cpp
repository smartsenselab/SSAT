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
