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

private slots:
    void sendEvent()
    {
        QPaintEvent event(QRect(10,10,50,50));
        QApplication::sendEvent(this, &event);
        qDebug()<<"event sended";
    }

private:
    void paintEvent(QPaintEvent* ev) override;
    void mouseReleaseEvent(QMouseEvent* ev) override;
    void mousePressEvent(QMouseEvent* ev) override;
    void mouseMoveEvent(QMouseEvent* ev) override;
    void mouseDoubleClickEvent(QMouseEvent* event) override;

//members
private:
    QStack<GGraphicsItem*> m_selectedItem;
    GGraphicsItem* m_currentItem;
    GGraphicsItem* m_drawableItem;
    GraphicsScene* m_gScene;
};






#endif // GRAPHICSVIEW_H
