#include "graphicsview.h"
#include <QDebug>
#include <QWidget>
#include <QPainter>
#include <QRect>
#include <QGraphicsRectItem>
#include <QGridLayout>
#include <QApplication>
#include <QTableWidget>
#include <QScrollArea>
#include <QScrollBar>
#include <QEvent>
#include <QPaintEvent>

GraphicsView::GraphicsView(GraphicsScene* gScene, QWidget* parent):QGraphicsView (gScene, parent)
{
    this->setSceneRect(QRectF(0,0,1000, 1000));

    m_gScene = dynamic_cast<GraphicsScene*>(scene());
    setMouseTracking(true);

    QGridLayout* lay = new QGridLayout;
    setLayout(lay);

}

void GraphicsView::mouseReleaseEvent(QMouseEvent* ev)
{
    if(m_gScene) {
        m_gScene->addItem(m_gScene->getCurrentItem());
    }
    update();
    //QGraphicsView::mouseReleaseEvent(ev);
}
void GraphicsView::mousePressEvent(QMouseEvent* ev)
{
    GGraphicsItem* gItem = m_gScene->getCurrentItem();

    if(gItem) {
       m_gScene->setCurrentItem(gItem->create());
       m_gScene->update(gItem->boundingRect());
       qDebug()<<"GraphicsView::mousePressEvent";
    }
   // QGraphicsView::mousePressEvent(ev);
}
void GraphicsView::mouseMoveEvent(QMouseEvent* ev)
{
    qDebug()<<"GraphicsView::mouseMoveEvent";
    if(m_gScene) {
       qDebug()<<"inside if";
       GGraphicsItem* item = m_gScene->getCurrentItem();
       if(item) {
          item->changeSize(QList<QPoint>() << ev->pos() + QPoint(horizontalScrollBar()->value(), verticalScrollBar()->value()));
         // repaint(m_gScene->sceneRect().toRect());
          //item->show();
         //  QPainter* painter = new QPainter(this);
         // QStyleOptionGraphicsItem* style = new QStyleOptionGraphicsItem();
          item->update();
          //paint(painter,style,this);
         // QRect bRect(item->boundingRect().toRect());
         // QPaintEvent* paintEv = new QPaintEvent(bRect);
         // qDebug()<<"-----------Success = "<<m_gScene->sendEvent(item, paintEv);
       }
       //item->update(item->boundingRect());
       //m_gScene->update(item->boundingRect());
    }

    qDebug()<<"GraphicsView::mouseMoveEvent";
    //QGraphicsView::mouseMoveEvent(ev);
}

void GraphicsView::paintEvent(QPaintEvent* ev)
{
    qDebug()<<"--------------------------------------------------------------GraphicsView paint event";
    QGraphicsView::paintEvent(ev);
}

GraphicsScene::GraphicsScene(QObject* parent):QGraphicsScene (parent)
{
    drawCoordinateLines();
}


void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent* ev)
{
    qDebug()<<"mousePressEvent";
    QGraphicsScene::mousePressEvent(ev);
}
void GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* ev)
{
    qDebug()<<"mouseReleaseEvent";
    QGraphicsScene::mouseReleaseEvent(ev);
}

QVector<QRect> GraphicsScene::getRects() const
{
    QVector<QRect> vec;
    QList<QGraphicsItem*> rects = items();
}

GGraphicsItem* GraphicsScene::getCurrentItem() const
{
    return m_currentItem;
}

void GraphicsScene::setCurrentItem(GGraphicsItem* item)
{
    qDebug()<<"GraphicsScene::setCurrentItem";
    m_currentItem = item;
}

void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    qDebug()<<"vfdbvjdbfvvbdfvdbvdbvdvbdjfvdjbvdvjdbvjdb";
}

void GraphicsScene::drawCoordinateLines()
{
    addLine(10,0,10,100, QPen(QBrush(Qt::green),10));
}

RectItem::RectItem(QGraphicsItem* parent) : QGraphicsRectItem (parent)
{
    m_textItem = new QGraphicsTextItem(this);
}

void RectItem::reDrawCoordinate()
{
    QPoint point = rect().bottomRight().toPoint();
    m_textItem->setHtml(QString::number((point.x())) + ", " + QString::number(point.y()));
    m_textItem->setPos(point);
}

