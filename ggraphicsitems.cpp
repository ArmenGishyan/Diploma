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

