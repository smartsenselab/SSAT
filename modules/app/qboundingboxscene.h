#ifndef SCENE_H
#define SCENE_H

#include <QAction>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QtMath>
#include <QToolBar>

#include <qdebug.h>

#include <cstdlib>
#include <iostream>

#include <opencv2/core.hpp>
using cv::Rect;

#include "frame.h"
#include "qboundingboxrectangle.h"

class QBoundingBoxScene : public QGraphicsScene
{
    Q_OBJECT

private:
    void makeItemsControllable(bool areControllable);

    /// \brief drawEnabled Bool to indicate if the user can draw a bbox
    /// \brief moveEnabled Bool to indicate if teh user can move a bbox
    bool drawEnabled, moveEnabled;
    double heightD, widthD;
    double mouseMoveX, mouseMoveY;

    QGraphicsRectItem *itemToDraw = NULL;

    qreal height;
    qreal pointXa, pointXb;
    qreal pointYa, pointYb;
    qreal width;

    Rect box;

public:
    ///
    /// \brief QBoundingBoxScene Constructor for a new bbox
    /// \param parent
    ///
    QBoundingBoxScene(QObject* parent = 0);

    ///
    /// \brief keyPressEvent
    /// \param e
    ///
    void keyPressEvent(QKeyEvent* e) Q_DECL_OVERRIDE;

    ///
    /// \brief deleteBBox Removes a bbox
    ///
    void deleteBBox();

protected:
    ///
    /// \brief mousePressEvent When mouse button is pressed
    /// \param event Event sent by mouse
    ///
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;

    ///
    /// \brief mouseMoveEvent When mouse is moved
    /// \param event Event sent by mouse
    ///
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;

    ///
    /// \brief mouseReleaseEvent Mouse button released
    /// \param event Event sent by mouse
    ///
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;

public slots:
    ///
    /// \brief slot_drawFrameBboxes Slot to draw all Bboxes in a given frame
    /// \param _frame frame where the bbox is gonna be drawn
    ///
    void slot_drawFrameBboxes(const Frame &_frame);

    ///
    /// \brief slot_enableDraw Allow the user to draw a new bbox
    ///
    void slot_enableDraw();

signals:
    ///
    /// \brief signal_drawFrameBboxes   Signal to call slot_drawFrameBboxes
    ///
    void signal_drawFrameBboxes();

    ///
    /// \brief signal_addBoundingBoxToCore signal to add the bbox to core
    /// \param newBox bbox to add
    ///
    void signal_addBoundingBoxToCore(const Rect _box);

    ///
    /// \brief signal_moveBoundingBoxInCore signal to update core with new bbox position
    /// \param _frameId frame which bbox will be updated
    /// \param _bboxId  id of bounding box that will be updated
    ///
    void signal_moveBoundingBoxInCore(const unsigned int _bboxId, const Rect _box);

    ///
    /// \brief signal_removeBoundingBoxFromCore signal to remove bbox from core
    /// \param _frameId frame which bbox will be removed from
    /// \param _bboxId  id of bounding box that will be deleted
    ///
    void signal_removeBoundingBoxFromCore(const unsigned int _frameId, const unsigned int _bboxId);
};

#endif // SCENE_H
