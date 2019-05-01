#ifndef COORDINATESYSTEM_H
#define COORDINATESYSTEM_H

#include <QWidget>
#include <QGraphicsView>
#include <map>
#include <set>

#include "graphicsview.h"

class QGraphicsRectItem;

class Editor : public QWidget
{
    Q_OBJECT
public:
    Editor(QWidget* parent = nullptr);
    void paintEvent(QPaintEvent* p) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void dragMoveEvent(QDragMoveEvent* event) override;
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent* event) override;
    template<class T>
    QList<T> getShapeItems() const;
    void setCurrentItem(GGraphicsItem* item);
    QList<GGraphicsItem*> getSelectedItems() const;
    void selectItems(const QList<GGraphicsItem*>& items);
    void selectItems(const QList<QString>& itemNames);
    void addShapes(QList<GGraphicsItem*> shapes);
    void setStyle(const std::shared_ptr<GGraphicsStyle>& style, bool force = true);
    std::shared_ptr<GGraphicsStyle> getStyle() const;

public slots:
    void clearAll();
    void clearSelectedItems();

private:
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
