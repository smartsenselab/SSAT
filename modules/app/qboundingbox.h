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
    QBoundingBox(QObject* parent = 0);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    void makeItemsControllable(bool areControllable);

    bool drawEnabled, moveEnabled;

    QGraphicsRectItem* itemToDraw = NULL;
    qreal height;
    qreal pointXa, pointXb;
    qreal pointYa, pointYb;
    qreal width;

    Rect box;

signals:
    void signal_addBoundingBoxToCore(Rect newBox);

public slots:
    void slot_drawFrameBboxes(const Frame _frame);
    void slot_enableDraw();
};

#endif // SCENE_H
