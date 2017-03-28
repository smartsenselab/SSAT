#ifndef QBOUNDINGBOXRECTANGLE_H
#define QBOUNDINGBOXRECTANGLE_H

#include <QGraphicsItem>

class QBoundingBoxRectangle : public QObject, public QGraphicsRectItem
{
    Q_OBJECT

private:
    unsigned int identifier;

public:
    QBoundingBoxRectangle();
    QBoundingBoxRectangle(unsigned int _id);

    unsigned int getIdentifier();
    void setIdentifier(unsigned int _id);
};

#endif // QBOUNDINGBOXRECTANGLE_H
