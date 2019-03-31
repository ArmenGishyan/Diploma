#ifndef GGRAPHICSSHAPESITEM_H
#define GGRAPHICSSHAPESITEM_H


#include <QAbstractGraphicsShapeItem>
#include <QPoint>

class GGraphicsPointItem : public QAbstractGraphicsShapeItem
{
public:
    GGraphicsPointItem(QGraphicsItem* parent = nullptr);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    int getX() {return m_point.rx();}
    int getY() {return m_point.ry();}
    void setX(int x ) {m_point.setX(x);}
    void setY(int y) {m_point.setY(y);}

private:
    QPoint m_point;
};

class GGraphicsShapesItem
{
public:
    GGraphicsShapesItem();
};

#endif // GGRAPHICSSHAPESITEM_H
