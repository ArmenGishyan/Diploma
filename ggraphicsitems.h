#ifndef GGRAPHICSITEMS_H
#define GGRAPHICSITEMS_H

#include <QGraphicsItem>

#include <QPoint>
#include <QDebug>

// Base class all Graphics Item
class GGraphicsItem : public QGraphicsItem
{
public:
    GGraphicsItem(QGraphicsItem * parent = 0);
    virtual GGraphicsItem* create() = 0;
    virtual void setStartPoint(const QPoint& point) = 0;
    virtual void setEndPoint(const QPoint& point) = 0;
    virtual void changeSize(const QPoint& point) = 0;
};

// Graphics Rect Item
class GGraphicsRectItem : public GGraphicsItem
{
public:
    GGraphicsRectItem(QGraphicsItem* parent = nullptr);
    GGraphicsRectItem* create() override;
    void setStartPoint(const QPoint& point) override;
    void setEndPoint(const QPoint& point) override;
    void changeSize(const QPoint& points) override;
    QRectF boundingRect() const override;
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = nullptr) override;
    QRectF rect() const {return m_rect;}
    void setRect(QRectF rect) {m_rect = rect.toRect();}

private:
    QRect m_rect;
};

// Point Item
class GGraphicsPointItem : public GGraphicsItem
{
public:
    GGraphicsPointItem(QGraphicsItem* parent = nullptr);
    virtual GGraphicsPointItem* create() override;
    virtual void setStartPoint(const QPoint& point) override;
    virtual void setEndPoint(const QPoint& point) override;
    virtual void changeSize(const QPoint& points) override;
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    int getX() {return m_point.rx();}
    int getY() {return m_point.ry();}
    void setX(int x ) {m_point.setX(x);}
    void setY(int y) {m_point.setY(y);}

private:
    QPoint m_point;
};

// Graphics Line Item
class GGraphicsLineItem : public GGraphicsItem
{
public:
    GGraphicsLineItem(QGraphicsItem* parent = nullptr);
    GGraphicsLineItem* create() override;
    void setStartPoint(const QPoint& point) override;
    void setEndPoint(const QPoint& point) override;
    void changeSize(const QPoint& points) override;
    QRectF boundingRect() const override;
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = nullptr) override;

private:
    QPoint m_start;
    QPoint m_end;
};

#endif // GGRAPHICSITEMS_H
