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

    QString array_of_colors[42] = {"#ff0000", "#aaff00", "#000080", "#bf0000", "#1f7300", "#c8bfff", "#99574d", "#ace6bb", "#3c394d", "#ffa280", "#304034",
                                "#7340ff", "#ffd0bf", "#00d957", "#7159b3", "#732e00", "#165931", "#827399", "#594c43", "#00e6b8", "#3a1659", "#bf7c30",
                                "#005f66", "#d900ca", "#a6987c", "#73dee6", "#663355", "#8c7000", "#00a2f2", "#e5007a", "#4c3d00", "#002b40", "#ffbfd9",
                                "#f2e63d", "#234d8c", "#ff4059", "#fffbbf", "#000733", "#59161f", "#7e8c46", "#00008c", "#8c696e"};
    int color_counter = 0;

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
    /// \brief slot_drawFrameBboxes Slot to draw a new bbox
    /// \param _frame frame where the bbox is gonna be drawn
    ///
    void slot_drawFrameBboxes(const Frame _frame);

    ///
    /// \brief slot_enableDraw Allow the user to draw a new bbox
    ///
    void slot_enableDraw();

signals:
    ///
    /// \brief signal_addBoundingBoxToCore signal to add the bbox to singleton
    /// \param newBox bbox to add
    ///
    void signal_addBoundingBoxToCore(const Rect _box);
};

#endif // SCENE_H
