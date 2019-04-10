#ifndef GGRAPHICSITEMS_H
#define GGRAPHICSITEMS_H

#include <QGraphicsItem>

#include <QPoint>
#include <QDebug>

// Base class all Graphics Item
class GGraphicsItem : public QAbstractGraphicsShapeItem
{
public:
    GGraphicsItem(QGraphicsItem * parent = 0);
    virtual GGraphicsItem* create() = 0;
    virtual void changeSize(const QList<QPoint>& points) = 0;
    void mouseMoveEvent(QGraphicsSceneMouseEvent * event) override;
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
   // void mouseMoveEvent(QGraphicsSceneMouseEvent * event) override;
    //bool sceneEvent(QEvent *event) override;
    QRectF rect() const {return m_rect;}
    void setRect(QRectF rect) {m_rect = rect.toRect();}
    QPainterPath shape() const override
    {
        qDebug()<<"shape Rect";
        QPainterPath path;
        path.addRect(boundingRect());
        return path;
    }
    QPainterPath opaqueArea() const override
    {
        qDebug()<<"opaqueArea()";
        return QPainterPath();
    }

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


//temporary item
class GRectItem : public QGraphicsRectItem
{
public:
   GRectItem(QGraphicsItem* parent = nullptr);
   QGraphicsTextItem* getTextItem(){return m_textItem;}
   void reDrawCoordinate();
   void setTextPos(const QPoint&);
   void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
   QRectF boundingRect() const override;


private:
    QGraphicsTextItem* m_textItem;
};

#endif // GGRAPHICSITEMS_H
