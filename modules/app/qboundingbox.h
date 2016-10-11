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

class QBoundingBox : public QGraphicsScene
{
public:
    QBoundingBox(QObject* parent = 0);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    void makeItemsControllable(bool areControllable);

    bool drawEnabled, moveEnabled;

    QGraphicsRectItem* itemToDraw;
    qreal heigth;
    qreal pointXa, pointXb;
    qreal pointYa, pointYb;
    qreal weigth;

public slots:
    void enableDraw();
};

#endif // SCENE_H
