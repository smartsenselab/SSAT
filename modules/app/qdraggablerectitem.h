#ifndef DRAGGABLERECTITEM_H
#define DRAGGABLERECTITEM_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

class QDraggableRectItem : public QGraphicsRectItem
{
public:
    QDraggableRectItem(QGraphicsItem* parent = 0);
    void setAnchorPoint(const QPointF &anchorPoint);

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
private:
    QPointF anchorPoint;
    bool m_dragged;
};

#endif // DRAGGABLERECTITEM_H
