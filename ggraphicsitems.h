#ifndef GGRAPHICSITEMS_H
#define GGRAPHICSITEMS_H

#include <QGraphicsItem>
#include <QPoint>

// Base class all Graphics Item
class GGraphicsItem : public QGraphicsItem
{
public:
    GGraphicsItem(QGraphicsItem * parent = 0);
    virtual GGraphicsItem* create() = 0;
    virtual void changeSize(const QList<QPoint>& points) = 0;
};

// Graphics Rect Item
class GGraphicsRectItem : public GGraphicsItem
{
public:
    GGraphicsRectItem(QGraphicsItem* parent = nullptr);
    GGraphicsRectItem* create() override;
    QRectF boundingRect() const override;
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = nullptr) override;
    void changeSize(const QList<QPoint>& points) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent * event) override;
    bool sceneEvent(QEvent *event) override;


private:
    QRect m_rect;
};

// Point Item
class GGraphicsPointItem : public GGraphicsItem
{
public:
    GGraphicsPointItem(QGraphicsItem* parent = nullptr);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    virtual GGraphicsPointItem* create() override;
    virtual void changeSize(const QList<QPoint>& points) override;
    int getX() {return m_point.rx();}
    int getY() {return m_point.ry();}
    void setX(int x ) {m_point.setX(x);}
    void setY(int y) {m_point.setY(y);}

private:
    QPoint m_point;
};
#endif // GGRAPHICSITEMS_H
