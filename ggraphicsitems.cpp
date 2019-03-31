#include "ggraphicsitems.h"
#include <QDebug>
#include <QPainter>
#include <QApplication>

//-----------------Base Graphics Item
GGraphicsItem::GGraphicsItem(QGraphicsItem * parent) : QGraphicsItem (parent)
{

}

//----------------Rect Item
GGraphicsRectItem::GGraphicsRectItem(QGraphicsItem* parent):GGraphicsItem (parent)
{
    m_rect = QRect();
}

GGraphicsRectItem* GGraphicsRectItem::create()
{
    return new GGraphicsRectItem;
}


QRectF GGraphicsRectItem::boundingRect() const
{
    qDebug()<<"bounding rect";
    int x1, x2, y1, y2;
    m_rect.getCoords(&x1,&y2,&x2,&y2);
    return QRect(QPoint(x1+1,y1+1),QPoint(x2+1,y2+1));
}

void GGraphicsRectItem::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    qDebug()<<"-------------------GGraphicsRectItem::paint";
    painter->drawRect(m_rect);
    //GGraphicsItem::paint(painter,option,widget);

}

void GGraphicsRectItem::changeSize(const QList<QPoint>& points)
{
    qDebug()<<"-------------------GGraphicsRectItem::changeSize";
    if(!points.empty()) {
        QPoint newPoint = m_rect.bottomRight()+points[0];
        qDebug() << points[0];
        m_rect.setBottomRight(newPoint);
    }
}

void GGraphicsRectItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    qDebug()<<"GGraphicsRectItem::mouseMoveEvent";
}

bool GGraphicsRectItem::sceneEvent(QEvent* event)
{
    qDebug()<<"---------------GGraphicsRectItem::sceneEvent";
    if(event->type() == QEvent::MouseMove) {
        qDebug()<<"MouseMove";
    }
    if(event->type() == QEvent::Paint)
    {
        qDebug()<<"Paint Eventnvdfvdbfvd";
    }

}
//---------------------Point Item
GGraphicsPointItem::GGraphicsPointItem(QGraphicsItem* parent) : GGraphicsItem (parent)
{

}


GGraphicsPointItem* GGraphicsPointItem::create()
{
    return new GGraphicsPointItem;
}

void GGraphicsPointItem::changeSize(const QList<QPoint>& points)
{

}
