#ifndef GGRAPHICSITEMS_H
#define GGRAPHICSITEMS_H

#include <QGraphicsItem>

#include <QPoint>
#include <QDebug>
#include <memory>

class GGraphicsStyle;

// Base class all Graphics Item
class GGraphicsItem : public QGraphicsItem
{
public:
    GGraphicsItem(std::string name, QGraphicsItem * parent = nullptr);
    GGraphicsItem(QGraphicsItem * parent = nullptr);
    virtual ~GGraphicsItem(){}
    virtual GGraphicsItem* create() = 0;
    virtual void setStartPoint(const QPoint& point) = 0;
    virtual void setEndPoint(const QPoint& point) = 0;
    virtual void changeSize(const QPoint& point) = 0;
    inline void setStyle(std::shared_ptr<GGraphicsStyle> style) { m_style = style;}
    inline std::shared_ptr<GGraphicsStyle> style() const {return m_style;}
    inline void setName(const QString& name) {m_name = name.toStdString();}
    std::string name() const ;
    static void setSelectionStyle(std::unique_ptr<GGraphicsStyle> style);
    static const std::unique_ptr<GGraphicsStyle>* getSelectionStyle();

protected:
    std::string m_name;
    std::shared_ptr<GGraphicsStyle> m_style;
    // this static member describe how item should behave when selected
    static std::unique_ptr<GGraphicsStyle> m_styleInSelection;

};

// Graphics Rect Item
class GGraphicsRectItem : public GGraphicsItem
{
public:
    GGraphicsRectItem(std::string name, QGraphicsItem* parent = nullptr);
    GGraphicsRectItem(QGraphicsItem* parent = nullptr);
    GGraphicsRectItem* create() override;
    void setStartPoint(const QPoint& point) override;
    void setEndPoint(const QPoint& point) override;
    void changeSize(const QPoint& points) override;
    QRectF boundingRect() const override;
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = nullptr) override;
    QRectF rect() const {return m_rect;}
    void setRect(QRectF rect) {m_rect = rect.toRect();}
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event);

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
