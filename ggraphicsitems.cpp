#include "ggraphicsitems.h"
#include <QDebug>
#include <QPainter>
#include <QApplication>

//-----------------Base Graphics Item
GGraphicsItem::GGraphicsItem(QGraphicsItem * parent) : QAbstractGraphicsShapeItem(parent)
{

}

void GGraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent * event)
{
    qDebug()<<"GGraphicsItem::mouseMoveEvent";
    QGraphicsItem::mouseMoveEvent(event);
}

//----------------Rect Item
GGraphicsRectItem::GGraphicsRectItem(QGraphicsItem* parent):GGraphicsItem (parent)
{
    m_rect = QRect();
    show();
}

GGraphicsRectItem* GGraphicsRectItem::create()
{
    return new GGraphicsRectItem;
}


QRectF GGraphicsRectItem::boundingRect() const
{
    qDebug()<<"GGraphicsRectItem::boundingRect";
    QPoint leftTop = m_rect.topLeft();
    QPoint bottomRight = m_rect.bottomRight();

    return QRectF((leftTop+QPoint(-1, 1)), bottomRight + QPoint(1, 1));
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

//void GGraphicsRectItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
//{
//    qDebug()<<"GGraphicsRectItem::mouseMoveEvent";
//    QGraphicsItem::mouseMoveEvent(event);
//}

//bool GGraphicsRectItem::sceneEvent(QEvent* event)
//{
//    qDebug()<<"---------------GGraphicsRectItem::sceneEvent";
//    if(event->type() == QEvent::MouseMove) {
//        qDebug()<<"MouseMove";
//    }
//    if(event->type() == QEvent::Paint)
//    {
//        qDebug()<<"Paint Eventnvdfvdbfvd";
//    }
//
//}

//--------------------------------Point Item---------------------------------------
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

//----------------------------------------------temporary item-------------------------------
GRectItem::GRectItem(QGraphicsItem* parent) : QGraphicsRectItem (parent)
{
    m_textItem = new QGraphicsTextItem(this);
}

void GRectItem::reDrawCoordinate()
{
    QPoint point = rect().bottomRight().toPoint();
    m_textItem->setHtml(QString::number((point.x())) + ", " + QString::number(point.y()));
    m_textItem->setPos(point);
}

void GRectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    qDebug()<<"--------------------------------------GRectPaint------------------------";
    painter->drawRect(this->rect());
    painter->drawText(this->rect().topLeft(), QString("Armen"));
}


QRectF GRectItem::boundingRect() const
{
    qDebug()<<"bounding rect GRectItem";
    QRect rect = this->rect().toRect();

    QPoint leftTop = rect.topLeft();
    QPoint bottomRight = rect.bottomRight();

    return QRectF((leftTop+QPoint(-1, 1)), bottomRight + QPoint(1, 1));
}
