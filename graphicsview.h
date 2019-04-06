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

class RectItem;

class GraphicsScene : public QGraphicsScene
{
  public:
    GraphicsScene(QObject* parent = nullptr);
    void mousePressEvent(QGraphicsSceneMouseEvent* ev) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* ev) override;
    QVector<QRect> getRects() const;
    void drawCoordinateLines();
    GGraphicsItem* getCurrentItem() const;
    void setCurrentItem(GGraphicsItem* item);

    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    GGraphicsItem* m_currentItem;
};

class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    GraphicsView() = default;
    GraphicsView(GraphicsScene* scene, QWidget* parent = nullptr);
    virtual ~GraphicsView(){}

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

//members
private:
    QGraphicsItem* m_rect;
    GraphicsScene* m_gScene;
};

class RectItem : public QGraphicsRectItem
{
public:
   RectItem(QGraphicsItem* parent = nullptr);
   QGraphicsTextItem* getTextItem(){return m_textItem;}
   void reDrawCoordinate();
   void setTextPos(const QPoint&);

private:
    QGraphicsTextItem* m_textItem;
};





#endif // GRAPHICSVIEW_H
