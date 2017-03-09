#ifndef DRAGGABLERECTITEM_H
#define DRAGGABLERECTITEM_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

class QDraggableRectItem : public QGraphicsRectItem
{
private:
    ///
    /// \brief anchorPoint Center point of the bbox
    ///
    QPointF anchorPoint;

    /// Sets the mouse to start to draw bboxes
    bool m_dragged;

public:
    ///
    /// \brief QDraggableRectItem Constructor for a new bbox
    /// \param parent New bbox parent
    QDraggableRectItem(QGraphicsItem* parent = 0);

    ///
    /// \brief setAnchorPoint set the central point of the bbox also called an anchorpoint
    /// \param anchorPoint center of the bbox
    ///
    void setAnchorPoint(const QPointF &anchorPoint);

protected:
    ///
    /// \brief mouseMoveEvent Executed when the user is moving the mouse to draw a bbox
    /// \param event Event of moving the mouse or releasing mouse button
    ///
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

    ///
    /// \brief mouseReleaseEvent Executed when the user release the mouse button
    /// \param event Event of releasing mouse button or moving the mouse
    ///
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // DRAGGABLERECTITEM_H
