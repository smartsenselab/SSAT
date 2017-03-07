#ifndef SCENE_H
#define SCENE_H

#include <QAction>
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QtMath>
#include <QToolBar>

#include <cstdlib>
#include <iostream>

#include <opencv2/core.hpp>
using cv::Rect;

#include "frame.h"

class QBoundingBox : public QGraphicsScene
{
    Q_OBJECT

public:
    ///
    /// \brief QBoundingBox Constructor for a new bbox
    /// \param parent
    ///
    QBoundingBox(QObject* parent = 0);

    ///
    /// \brief keyPressEvent
    /// \param e
    ///
    void keyPressEvent(QKeyEvent* e);

    ///
    /// \brief deleteBBox Removes a bbox
    ///
    void deleteBBox();

protected:
    ///
    /// \brief mousePressEvent When mouse button is pressed
    /// \param event Event sent by mouse
    ///
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    ///
    /// \brief mouseMoveEvent When mouse is moved
    /// \param event Event sent by mouse
    ///
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

    ///
    /// \brief mouseReleaseEvent Mouse button released
    /// \param event Event sent by mouse
    ///
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    void makeItemsControllable(bool areControllable);

    ///
    /// \brief drawEnabled Bool to indicate if the user can draw a bbox
    /// \brief moveEnabled Bool to indicate if teh user can move a bbox
    bool drawEnabled, moveEnabled;
    double heightD, widthD;
    double mouseMoveX, mouseMoveY;

    QGraphicsRectItem* itemToDraw = NULL;
    qreal height;
    qreal pointXa, pointXb;
    qreal pointYa, pointYb;
    qreal width;

    Rect box;

signals:
    ///
    /// \brief signal_addBoundingBoxToCore signal to add the bbox to singleton
    /// \param newBox bbox to add
    ///
    void signal_addBoundingBoxToCore(const Rect _newBox);

public slots:
    ///
    /// \brief slot_drawFrameBboxes Slot to draw a new bbox
    /// \param _frame frame where the bbox is gonna be drawn
    ///
    void slot_drawFrameBboxes(const Frame _frame);

    ///
    /// \brief slot_enableDraw Allow the user to draw a new bbox
    ///
    void slot_enableDraw();
};

#endif // SCENE_H
