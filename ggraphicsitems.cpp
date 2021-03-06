#include "ggraphicsitems.h"
#include <QDebug>
#include <QPainter>
#include <QApplication>
#include <utility>
#include <QPen>

#include "ggraphicsstyle.h"

std::unique_ptr<GGraphicsStyle> GGraphicsItem::m_styleInSelection = std::make_unique<GGraphicsStyle>(QPen(QColor(Qt::yellow)),QBrush(Qt::green));

//-----------------Base Graphics Item
GGraphicsItem::GGraphicsItem(QGraphicsItem * parent) : QGraphicsItem(parent)
{
    m_name = "";
    m_style = std::make_shared<GGraphicsStyle>(QPen(QColor("#005500")), QBrush(QColor("#005500")));
    m_isSelected = false;
}

GGraphicsItem::GGraphicsItem(std::string name, QGraphicsItem * parent): GGraphicsItem(parent)
{
    m_name = name;
    m_style = std::make_shared<GGraphicsStyle>(QPen(QColor("#005500")), QBrush(QColor("#005500")));
    //m_style = std::make_shared<GGraphicsStyle>(QColor(Qt::green));
    m_isSelected = false;
}

std::string GGraphicsItem::name() const
{
    try {
        return  m_name;
    } catch (...) {
        return "";
    }

}

void GGraphicsItem::setSelectionStyle(std::unique_ptr<GGraphicsStyle> style) {
    m_styleInSelection = std::move(style);
}

const std::unique_ptr<GGraphicsStyle>* GGraphicsItem::getSelectionStyle() {
    return &m_styleInSelection;
}

//-------------------------------------------------Rect Item------------------------------
GGraphicsRectItem::GGraphicsRectItem(QGraphicsItem* parent):GGraphicsItem (parent)
{
    m_rect = QRect();
    setFlag(QGraphicsItem::ItemIsSelectable);
}

GGraphicsRectItem::GGraphicsRectItem(std::string name, QGraphicsItem* parent) : GGraphicsItem (name,parent)
{
    m_rect = QRect();
    setFlag(QGraphicsItem::ItemIsSelectable);
}

GGraphicsRectItem* GGraphicsRectItem::create()
{
    return new GGraphicsRectItem;
}


QRectF GGraphicsRectItem::boundingRect() const
{
    QPoint leftTop = m_rect.topLeft();
    QPoint bottomRight = m_rect.bottomRight();

    return QRectF((leftTop + QPoint(-1, 1)), bottomRight + QPoint(1, -1));
}


GGraphicsRectItem* GGraphicsRectItem::parseShape(QStringList str) const
{
    //Shape{Rect{50, 30, 100, 100}; Name{"Shape_1"}; Color{red, green}});

}

void GGraphicsRectItem::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    GGraphicsStyle style;
    if(isSelected()) {
        auto stylePtr = GGraphicsItem::getSelectionStyle();
        if(stylePtr) {
           style.setPen(stylePtr->get()->pen());
           style.setBrush(stylePtr->get()->brush());
        }
    } else {
        auto stylePtr = this->style();
        if(stylePtr) {
           style.setPen(stylePtr->pen());
           style.setBrush(stylePtr->brush());
        }
    }
    painter->setPen(style.pen());
    painter->setBrush(style.brush());

    painter->drawRect(m_rect);
    QString rightBottom = QString::number(m_rect.bottomRight().x()) + ", " + QString::number(m_rect.bottomRight().y());
    QString leftTop = QString::number(m_rect.topLeft().x()) + ", " + QString::number(m_rect.topLeft().y());

    //transform.rotateRadians(23);
    QPoint point1 = m_rect.bottomRight() + QPoint(2, -1);
    QPoint point2 = m_rect.topLeft() + QPoint(-1, 1);
    //painter->rotate(90); //setTransform(transform);
    painter->drawText(mapFromScene(m_rect.bottomRight() + QPoint(2, -1)), rightBottom);
    painter->drawText(mapFromScene(m_rect.topLeft() + QPoint(-1, 1)), leftTop);
    QFont font;
    font.setBold(true);
    font.setWeight(2);

    painter->drawText(m_rect.center(), QString::fromStdString(name()));
}


void GGraphicsRectItem::changeSize(const QPoint& points)
{
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

void GGraphicsRectItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event)
{
   // setItemSelected(!m_isSelected);
   // update();
   // std::shared_ptr<GGraphicsStyle> style = std::make_shared<GGraphicsStyle>();
   // style->setBrush(QBrush(Qt::yellow));
   // style->setPen(QColor(Qt::red));

   // setStyle(style);
   // //m_rect.setBobottomRight()
   // //update();
   //// parentWidget()->update();
   // setSelected(true);
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

GGraphicsPointItem* GGraphicsPointItem::parseShape(QStringList str) const
{
    new GGraphicsPointItem;
}

void GGraphicsPointItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
     painter->drawLine(m_point, m_point);
}

//------------------------------------------GGraphics Line Item------------------------

GGraphicsLineItem::GGraphicsLineItem(QGraphicsItem* parent):GGraphicsItem (parent)
{
    m_start = QPoint();
    m_end = QPoint();
}

GGraphicsLineItem* GGraphicsLineItem::create()
{
    return new GGraphicsLineItem;
}

void GGraphicsLineItem::setStartPoint(const QPoint& point)
{
    m_start = point;
    m_end = point;
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

GGraphicsLineItem* GGraphicsLineItem::parseShape(QStringList str) const
{
    return new GGraphicsLineItem;
}
void GGraphicsLineItem::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    painter->drawLine(m_start, m_end);
}




