void Myclass::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(isSelected())
    {

        qDebug()<<"isseldeted";
        qreal adjust = 8;
        if( (event->pos().x() > boundingRect().left() + adjust) && 
            (event->pos().x() < boundingRect().right() - adjust) && 
            (event->pos().y() < boundingRect().bottom() + adjust) && 
            (event->pos().y() > boundingRect().bottom() - adjust) )
        {
            _adj = event->pos().y();
            _resizemode = true;
            qDebug()<<"bottom";
        }

        if( (event->pos().x() > boundingRect().right() - adjust) && 
            (event->pos().x() < boundingRect().right() + adjust) && 
            (event->pos().y() < boundingRect().bottom() + adjust) && 
            (event->pos().y() > boundingRect().bottom() - adjust) )
        {
            _adj = event->pos().y();
            _adj2 = event->pos().x();
            _resizemode2 = true;
            qDebug()<<"bottom right";
        }

        if( (event->pos().x() > boundingRect().right() - adjust) && 
            (event->pos().x() < boundingRect().right() + adjust) && 
            (event->pos().y() < boundingRect().bottom() - adjust) && 
            (event->pos().y() > boundingRect().top() + adjust) )
        {
            _adj2 = event->pos().x();
            _resizemode3 = true;
            qDebug()<<"right";
        }

        if( (event->pos().x() > boundingRect().left() - adjust) && 
            (event->pos().x() < boundingRect().left() + adjust) && 
            (event->pos().y() > boundingRect().top() - adjust) && 
            (event->pos().y() < boundingRect().top() + adjust) )
        {
            _adj = event->pos().y();
            _adj2 = event->pos().x();
            _resizemode4 = true;
            qDebug()<<"top left";
        }

        if( (event->pos().x() > boundingRect().left() - adjust) && 
            (event->pos().x() < boundingRect().left() + adjust) && 
            (event->pos().y() < boundingRect().bottom() - adjust) && 
            (event->pos().y() > boundingRect().top() + adjust))
        {
            _adj2 = event->pos().x();
            _resizemode5 = true;
            qDebug()<<"left";
        }

        if( (event->pos().x() > boundingRect().left() - adjust) && 
            (event->pos().x() < boundingRect().left() + adjust) && 
            (event->pos().y() < boundingRect().bottom() + adjust) && 
            (event->pos().y() > boundingRect().bottom() - adjust))
        {
            _adj = event->pos().y();
            _adj2 = event->pos().x();
            _resizemode6 = true;
            qDebug()<<"bottom left";
        }

        if( (event->pos().x() > boundingRect().left() + adjust) && 
            (event->pos().x() < boundingRect().right() - adjust) && 
            (event->pos().y() < boundingRect().top() + adjust) && 
            (event->pos().y() > boundingRect().top() - adjust))
        {
            _adj = event->pos().y();
            _resizemode7 = true;
            qDebug()<<"top";
        }

        if( (event->pos().x() < boundingRect().right() + adjust) && 
            (event->pos().x() > boundingRect().right() - adjust) && 
            (event->pos().y() < boundingRect().top() + adjust) && 
            (event->pos().y() > boundingRect().top() - adjust))
        {
            _adj = event->pos().y();
            _adj2 = event->pos().x();
            _resizemode8 = true;
            qDebug()<<"top right";
        }
    }

    update();
    QGraphicsItem::mousePressEvent(event);
}

void Myclass::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(_resizemode)
    {
        prepareGeometryChange();
        _h += event->pos().y() - _adj; //good
        setPos(pos().x(), pos().y() + (event->pos().y() - _adj)/2 );//good

        _resizemode = false;
    }

    if(_resizemode2)
    {
        _h += event->pos().y() - _adj; //good
        _w += event->pos().x() - _adj2;
        setPos(pos().x() + (event->pos().x() - _adj2)/2, pos().y() + (event->pos().y() - _adj)/2 );//good

        _resizemode2 = false;
    }

    if(_resizemode3)
    {
        _w += event->pos().x() - _adj2;
        setPos(pos().x() + (event->pos().x() - _adj2)/2, pos().y());//good

        _resizemode3 = false;
    }

    if(_resizemode4)
    {
        _h -= event->pos().y() - _adj; //good
        _w -= event->pos().x() - _adj2;
        setPos(pos().x() + (event->pos().x() - _adj2)/2, pos().y() + (event->pos().y() - _adj)/2 );//good

        _resizemode4 = false;
    }

    if(_resizemode5)
    {
        _w -= event->pos().x() - _adj2;
        setPos(pos().x() + (event->pos().x() - _adj2)/2, pos().y());//good

        _resizemode5 = false;
    }

    if(_resizemode6)
    {
        _h += event->pos().y() - _adj;
        _w -= event->pos().x() - _adj2;
        setPos(pos().x() + (event->pos().x() - _adj2)/2, pos().y() + (event->pos().y() - _adj)/2);//good

        _resizemode6= false;
    }

    if(_resizemode7)
    {
        _h -= event->pos().y() - _adj;
        setPos(pos().x(), pos().y() + (event->pos().y() - _adj)/2);//good

        _resizemode7= false;
    }

    if(_resizemode8)
    {
        _h -= event->pos().y() - _adj;
        _w += event->pos().x() - _adj2;
        setPos(pos().x() + (event->pos().x() - _adj2)/2, pos().y() + (event->pos().y() - _adj)/2);//good

        _resizemode8= false;
    }

    update();
    QGraphicsItem::mouseReleaseEvent(event);
}

void Myclass::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{   if(!_resizemode&&!_resizemode2&&!_resizemode3&&!_resizemode4&&!_resizemode5&&!_resizemode6&&!_resizemode7&&!_resizemode8)
    {
        update();
        QGraphicsItem::mouseMoveEvent(event);
    }
}