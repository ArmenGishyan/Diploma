#include "ggraphicsitems.h"
#include <QDebug>
#include <QPainter>
#include <QApplication>

//-----------------Base Graphics Item
GGraphicsItem::GGraphicsItem(QGraphicsItem * parent) : QGraphicsItem(parent)
{

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

    return QRectF((leftTop + QPoint(-1, 1)), bottomRight + QPoint(1, 1));
}

void GGraphicsRectItem::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    qDebug()<<"-------------------GGraphicsRectItem::paint";
    painter->drawRect(m_rect);
}


void GGraphicsRectItem::changeSize(const QPoint& points)
{
    qDebug()<<"-------------------GGraphicsRectItem::changeSize";
    m_rect.setBottomRight(points);
}

void GGraphicsRectItem::setStartPoint(const QPoint& point)
{
    m_rect = QRect(point, point);
}
void GGraphicsRectItem::setEndPoint(const QPoint& point)
{
    m_rect.setBottomRight(point);
}

//--------------------------------Point Item---------------------------------------
GGraphicsPointItem::GGraphicsPointItem(QGraphicsItem* parent) : GGraphicsItem (parent)
{
    m_point = QPoint();
}


GGraphicsPointItem* GGraphicsPointItem::create()
{
    return new GGraphicsPointItem;
}

void GGraphicsPointItem::changeSize(const QPoint& points)
{
    return;
}

void GGraphicsPointItem::setStartPoint(const QPoint& point)
{
    m_point = point;
}

void GGraphicsPointItem::setEndPoint(const QPoint& point)
{
    return;
}

QRectF GGraphicsPointItem::boundingRect() const
{
    QRectF(m_point+ QPoint(-1,1), m_point + QPoint(1,1));
}

void GGraphicsPointItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
     painter->drawLine(m_point, m_point);
}

//------------------------------------------GGraphics Line Item------------------------

GGraphicsLineItem::GGraphicsLineItem(QGraphicsItem* parent):GGraphicsItem (parent)
{}

GGraphicsLineItem* GGraphicsLineItem::create()
{
    return new GGraphicsLineItem;
}

void GGraphicsLineItem::setStartPoint(const QPoint& point)
{
    m_start = point;
}

void GGraphicsLineItem::setEndPoint(const QPoint& point)
{
    m_end = point;
}

void GGraphicsLineItem::changeSize(const QPoint& point)
{
   m_end = point;
}

QRectF GGraphicsLineItem::boundingRect() const
{
    return QRectF(m_start+QPoint(-1, 1), m_end + QPoint(1,-1));
}

void GGraphicsLineItem::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    painter->drawLine(m_start, m_end);
}




