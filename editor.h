#ifndef COORDINATESYSTEM_H
#define COORDINATESYSTEM_H

#include <QWidget>
#include <QGraphicsView>

#include "graphicsview.h"

class QGraphicsRectItem;

class Editor : public QWidget
{
    Q_OBJECT
public:
    Editor(QWidget* parent = nullptr);
    void paintEvent(QPaintEvent* p) override;
    //void resizeEvent(QResizeEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void dragMoveEvent(QDragMoveEvent* event) override;
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent* event) override;
    void setPen(const QPen& pen);
    void setBrush(const QBrush& brush);
    //void setSenceRect(const QRect& rect) {m_grScene->setSceneRect(rect);}
    template<class T>
    QList<T> getShapeItems() const;
    QPen getPen() const {return m_pen;}
    QBrush getBrush() const {return m_brush;}
    void setCurrentItem(GGraphicsItem* item);
    QList<GGraphicsItem*> getSelectedItems() const;
    void selectItems(const QList<GGraphicsItem*>& items);
    void selectItems(const QList<QString>& itemNames);

public slots:
 //   template<class T>
 //   void clear();
    void clearAll();

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


//--------------------------Converter Class --------------
// convert List of QGraphicsItem to GGraphicsITem
class Converter
{
public:
    static QList<GGraphicsItem*> convert(const QList<QGraphicsItem*>& items);
};


#endif // COORDINATESYSTEM_H
