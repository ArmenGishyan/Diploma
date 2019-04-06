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
    setBackgroundBrush(QBrush(Qt::red, Qt::SolidPattern));

    m_rect = nullptr;

    setMouseTracking(true);

    QGridLayout* lay = new QGridLayout;
    setLayout(lay);
    m_gScene = gScene;

}

void GraphicsView::mouseReleaseEvent(QMouseEvent* ev)
{
    QGraphicsRectItem* rectItem = qgraphicsitem_cast<QGraphicsRectItem*>(m_rect);
    if(rectItem) {
       QRectF rect = rectItem->rect();// m_items.top()->rect();
       rect.setBottomRight(ev->pos() + QPoint(horizontalScrollBar()->value(), verticalScrollBar()->value()));
       rectItem->setRect(rect);
       m_rect = nullptr;
       update();
    }

    qDebug()<<"GraphicsView::mouseReleaseEvent size = "<<items().size();
    QGraphicsView::mouseReleaseEvent(ev);
}
void GraphicsView::mousePressEvent(QMouseEvent* ev)
{
    m_rect = new QGraphicsRectItem;
    QGraphicsRectItem* rectItem = qgraphicsitem_cast<QGraphicsRectItem*>(m_rect);
    if(rectItem) {
        QPoint pos = ev->pos() + QPoint(horizontalScrollBar()->value(), verticalScrollBar()->value());
        QRectF rect(pos,pos);
        rectItem->setRect(rect);
        m_gScene->addItem(m_rect);
    }

    qDebug()<<"GraphicsView::mousePressEvent";
    QGraphicsView::mousePressEvent(ev);
}
void GraphicsView::mouseMoveEvent(QMouseEvent* ev)
{
    QGraphicsRectItem* rectItem = qgraphicsitem_cast<QGraphicsRectItem*>(m_rect);
    if(rectItem) {
       QRectF rect = rectItem->rect();
       rect.setBottomRight(ev->pos() + QPoint(horizontalScrollBar()->value(), verticalScrollBar()->value()));
       rectItem->setRect(rect);

        if(m_gScene && ev->button() == Qt::RightButton) {
            m_gScene->addItem(rectItem);
        }
        update();
    //QGraphicsView::mouseReleaseEvent(ev);
    }
}


void GraphicsView::paintEvent(QPaintEvent* ev)
{
    qDebug()<<"GraphicsView paint event";
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

