#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsLineItem>
#include <QAction>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QToolBar>

class QBoundingBox : public QGraphicsScene
{
public:
    QBoundingBox(QObject* parent = 0);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
private:
    QGraphicsRectItem* itemToDraw;

    qreal pointXa, pointXb;
    qreal pointYa, pointYb;
    qreal weigth;
    qreal heigth;
    void makeItemsControllable(bool areControllable);

    bool drawEnabled, moveEnabled;

public slots:
    void enableDraw();
};

#endif // SCENE_H
