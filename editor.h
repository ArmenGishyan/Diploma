#ifndef COORDINATESYSTEM_H
#define COORDINATESYSTEM_H

#include <QWidget>
#include <QGraphicsView>

#include "graphicsview.h"

class QGraphicsRectItem;

class Editor : public QWidget
{
public:
    Editor(QWidget* parent = nullptr);
    void paintEvent(QPaintEvent* p) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void dragMoveEvent(QDragMoveEvent* event) override;
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent* event) override;
    void setPen(QPen pen) {m_pen = pen;}
    void setBrush(QBrush brush) {m_brush = brush;}
    template<class T>
    QList<T> getShapeItems() const;
    QPen getPen() const {return m_pen;}
    QBrush getBrush() const {return m_brush;}

public:
    void setCurrentItem(QGraphicsItem* item);

private:
      QPen m_pen;
      QBrush m_brush;
      GraphicsScene* m_grScene;
      GraphicsView* m_grView;
};

#endif // COORDINATESYSTEM_H
