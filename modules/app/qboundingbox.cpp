#include "qboundingbox.h"
#include "boundingbox.h"
#include "qdebug.h"
#include "string"

QBoundingBox::QBoundingBox(QObject* parent): QGraphicsScene(parent)
{
    // std::cout << this->items().size() << std::endl;
    this->itemToDraw = 0;

    this->moveEnabled = false;
    this->drawEnabled = false;

    this->heightD = 0;
    this->widthD = 0;
}

void QBoundingBox::deleteBBox()
{
    foreach(QGraphicsItem *item, selectedItems())
    {
        removeItem(item);
        delete item;
    }
}

void QBoundingBox::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    this->pointXa = event->scenePos().x();
    this->pointYa = event->scenePos().y();
    QGraphicsScene::mousePressEvent(event);
}

int convertNumber(std::string str, std::string color){
    int a;
    if(color == "red") a = 1;
    if(color == "green") a = 3;
    if(color == "blue") a = 5;


    std::string str1 = str.substr(a,2);

    int rgb = 0;

    for(int i =1; i>=0; i--){
        if(str1[i] == 'f') rgb += 15;
        else if(str1[i] == 'e') rgb += 14;
        else if(str1[i] == 'd') rgb += 13;
        else if(str1[i] == 'c') rgb += 12;
        else if(str1[i] == 'b') rgb += 11;
        else if(str1[i] == 'a') rgb += 10;
        else rgb += (str1[i] - '0');
        if(i == 1) rgb *= 16;
    }

    return rgb;
}

void QBoundingBox::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    if(this->drawEnabled)
    {
        double mouse_posX = event->scenePos().x();
        double mouse_posY = event->scenePos().y();
        if(this->widthD == 0)
        {
            this->widthD = sceneRect().width();
        }
        if(this->heightD == 0)
        {
            this->heightD = sceneRect().height();
        }

        // the initial point must be inside the video resolution
        if((this->pointXa >= 0) && (this->pointYa >= 0) && (this->pointXa <= this->widthD) && (this->pointYa <= this->heightD))
        {
            delete(this->itemToDraw);
            this->itemToDraw = NULL;

            this->itemToDraw = new QGraphicsRectItem;
            QString color = this->array_of_colors[this->color_counter];
            this->itemToDraw->setPen(QPen(QColor(color), 3, Qt::SolidLine));

            std::string color_string = color.toUtf8().constData(); // qstring to string

            int red = convertNumber(color_string, "red");
            int green = convertNumber(color_string, "green");
            int blue = convertNumber(color_string, "blue");

            this->itemToDraw->setBrush(QBrush(QColor(red, green, blue, 50)));

            this->addItem(itemToDraw);


            if(mouse_posX < 0) mouse_posX = 0;
            if(mouse_posY < 0) mouse_posY = 0;
            if(mouse_posX > this->widthD) mouse_posX = this->widthD;
            if(mouse_posY > this->heightD) mouse_posY = this->heightD;

            this->pointXb = mouse_posX;
            this->pointYb = mouse_posY;
            this->width = this->pointXb - this->pointXa;
            this->height = this->pointYb - this->pointYa;

            if((this->width < 0) && (this->height < 0))
            {
                this->width = this->pointXa - this->pointXb;
                this->height = this->pointYa - this->pointYb;
                this->itemToDraw->setRect(
                            this->pointXb,
                            this->pointYb,
                            this->width,
                            this->height
                            );
                this->box.x = static_cast<int>(this->pointXb);
                this->box.y = static_cast<int>(this->pointYb);
                this->box.width = static_cast<int>(this->width);
                this->box.height = static_cast<int>(this->height);
            }
            else if((this->width > 0) && (this->height > 0))
            {
                this->itemToDraw->setRect(
                            this->pointXa,
                            this->pointYa,
                            this->width,
                            this->height);
                this->box.x = static_cast<int>(this->pointXa);
                this->box.y = static_cast<int>(this->pointYa);
                this->box.width = static_cast<int>(this->width);
                this->box.height = static_cast<int>(this->height);
            }
            else if((this->width < 0) && (this->height > 0))
            {
                this->width = this->pointXa - this->pointXb;
                this->itemToDraw->setRect(
                            this->pointXb,
                            this->pointYa,
                            this->width,
                            this->height
                            );
                this->box.x = static_cast<int>(this->pointXb);
                this->box.y = static_cast<int>(this->pointYa);
                this->box.width = static_cast<int>(this->width);
                this->box.height = static_cast<int>(this->height);
            }
            else
            {
                this->height = this->pointYa - this->pointYb;
                this->itemToDraw->setRect(
                            this->pointXa,
                            this->pointYb,
                            this->width,
                            this->height
                            );
                this->box.x = static_cast<int>(this->pointXa);
                this->box.y = static_cast<int>(this->pointYb);
                this->box.width = static_cast<int>(this->width);
                this->box.height = static_cast<int>(this->height);
            }
        }
    }
    else
    {
        this->mouseMoveX = this->pointXa - event->scenePos().x(); // Init position - End position  X - Deslocamento para a esquerda
        this->mouseMoveY = this->pointYa - event->scenePos().y(); // Init position - End position  Y

        //qDebug() << "X = " << this->box.x - mouseMoveX << endl;
        //qDebug() << "Y = " << this->box.y - mouseMoveY << endl;
        //qDebug() << "W = " << this->box.width << endl;
        //qDebug() << "H = " << this->box.height << endl;

        QGraphicsScene::mouseMoveEvent(event);
    }
}

void QBoundingBox::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if((this->drawEnabled) && (this->itemToDraw != NULL))
    {
        this->drawEnabled = false;
        this->itemToDraw->setFlag(QGraphicsItem::ItemIsSelectable, true);
        this->itemToDraw->setFlag(QGraphicsItem::ItemIsMovable, true);
        qDebug() << "Box = " << this->box.x << ":" << this->box.y << ":"
                 << this->box.width << ":" << this->box.height << endl;
        emit this->signal_addBoundingBoxToCore(this->box);

        if(this->color_counter == 41){
            this->color_counter = 0;
        }
        else{
            this->color_counter++;
        }
    }
    else
    {
        //this->box.x = static_cast<int>(this->box.x - mouseMoveX);
        //this->box.y = static_cast<int>(this->box.y - mouseMoveY);
    }

    QGraphicsScene::mouseReleaseEvent(event);
}

void QBoundingBox::slot_drawFrameBboxes(const Frame _frame)
{
    map<string, BoundingBox> bboxes = _frame.getBoxes();
    for(map<string, BoundingBox>::iterator it = bboxes.begin(); it != bboxes.end(); it++)
    {
        QString color = this->array_of_colors[this->color_counter];

        this->itemToDraw = new QGraphicsRectItem;
        this->itemToDraw->setPen(QPen(QColor(color), 3, Qt::SolidLine)); // Save bbox color.
        this->itemToDraw->setBrush(QBrush(QColor(255, 0, 0, 50)));
        this->itemToDraw->setRect(it->second.getX(),
                                  it->second.getY(),
                                  it->second.getW(),
                                  it->second.getH());
        // when going back to a frame, is possible to select and move the BBox already created
        this->itemToDraw->setFlag(QGraphicsItem::ItemIsSelectable, true);
        this->itemToDraw->setFlag(QGraphicsItem::ItemIsMovable, true);
        this->addItem(this->itemToDraw);
    }
}

void QBoundingBox::slot_enableDraw()
{
    this->itemToDraw = 0;
    this->drawEnabled = true;
}

void QBoundingBox ::keyPressEvent(QKeyEvent* e)
{
    switch(e->key())
    {
    case Qt::Key_Delete:
        removeItem(selectedItems().front());
    }
}
