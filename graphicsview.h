#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QEvent>
#include <QStack>
#include <QPushButton>
#include <QToolButton>
#include <QDebug>
#include <QApplication>
#include <QGraphicsRectItem>
#include <QListWidget>
#include <QListWidgetItem>
#include <QGridLayout>
#include <QDebug>

#include "ggraphicsitems.h"

class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    GraphicsScene(QObject* parent = nullptr);
    void mousePressEvent(QGraphicsSceneMouseEvent* ev) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* ev) override;
    QVector<QRect> getRects() const;
    void drawCoordinateLines();
    //bool eventFilter(QObject* object, QEvent* event) override;

public slots:
    void handleFocusItemChanged(QGraphicsItem *newFocusItem, QGraphicsItem *oldFocusItem, Qt::FocusReason reason);

    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    //void addItem() = delete;

private:
};

class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    GraphicsView() = default;
    GraphicsView(GraphicsScene* scene, QWidget* parent = nullptr);
    virtual ~GraphicsView(){}
    GGraphicsItem* getCurrentItem() const;
    void setCurrentItem(GGraphicsItem* item);
    QList<GGraphicsItem*> getSelectedItems();
    void visitAllItems(const std::function<void(GGraphicsItem*)>& func);
    // this function template
    template<class T>
    void setStyle(const std::shared_ptr<GGraphicsStyle>& style, bool force);
    std::shared_ptr<GGraphicsStyle> getStyle() const;
    void selectUnselectAll(bool select);

private slots:
    void sendEvent()
    {
        QPaintEvent event(QRect(10,10,50,50));
        QApplication::sendEvent(this, &event);
    }

private:
    void paintEvent(QPaintEvent* ev) override;
    void mouseReleaseEvent(QMouseEvent* ev) override;
    void mousePressEvent(QMouseEvent* ev) override;
    void mouseMoveEvent(QMouseEvent* ev) override;
    void mouseDoubleClickEvent(QMouseEvent* event) override;

//members
private:
    std::shared_ptr<GGraphicsStyle> m_style;
    QStack<GGraphicsItem*> m_selectedItem;
    GGraphicsItem* m_currentItem;
    GGraphicsItem* m_drawableItem;
    GraphicsScene* m_gScene;
};

template <class T>
void GraphicsView::setStyle(const std::shared_ptr<GGraphicsStyle> &style, bool force)
{
    if(force) {
        QList<QGraphicsItem*> itemList = items();
        for(int i = 0; i < itemList.size(); ++i) {
            T* item = qgraphicsitem_cast<T*>(itemList[i]);
            if(item) {
                item->setStyle(style);
            }
        }
    } else {
        m_style = style;
    }
}

#endif // GRAPHICSVIEW_H
