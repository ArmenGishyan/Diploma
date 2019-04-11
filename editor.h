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
    void setCurrentItem(GGraphicsItem* item);

private:
      QPen m_pen;
      QBrush m_brush;
      GraphicsScene* m_grScene;
      GraphicsView* m_grView;
};

//get Rectangles from GraphicsScene
template <class T>
QList<T> Editor::getShapeItems() const
{
    QList<QGraphicsItem*> items;
    QList<T> shapeItems;
    if(m_grScene) {
        items = m_grScene->items();
    }

    T shape;
    for(QGraphicsItem* it : items) {
        shape = qgraphicsitem_cast<T>(it);
        if(shape != nullptr) {
            shapeItems.append(shape);
        }
    }
    return shapeItems;
}
#endif // COORDINATESYSTEM_H
