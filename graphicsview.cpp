#include "graphicsview.h"
#include <QDebug>
#include <QWidget>
#include <QPainter>
#include <QRect>
#include <QGraphicsItem>
#include <QGridLayout>
#include <QApplication>
#include <QTableWidget>
#include <QScrollArea>
#include <QScrollBar>
#include <QEvent>
#include <QPaintEvent>

GraphicsView::GraphicsView(GraphicsScene* gScene, QWidget* parent):QGraphicsView (gScene, parent)
{
    if(parent != nullptr) {
        this->setSceneRect(QRectF(parent->rect()));
    } else {
        this->setSceneRect(QRectF(0, 0, 1000, 1000));
    }
    setBackgroundBrush(QBrush(Qt::darkBlue, Qt::SolidPattern));

    m_currentItem = nullptr;
    m_drawableItem = nullptr;

    setMouseTracking(true);

    QGridLayout* lay = new QGridLayout;
    setLayout(lay);
    m_gScene = gScene;

}

void GraphicsView::mouseReleaseEvent(QMouseEvent* ev)
{
    if(m_drawableItem && ev->buttons() == Qt::LeftButton) {

        m_drawableItem->setEndPoint(ev->pos() + QPoint(horizontalScrollBar()->value(), verticalScrollBar()->value()));
        m_drawableItem = nullptr;
        update();
    }

    qDebug()<<"GraphicsView::mouseReleaseEvent size = "<<items().size();
    QGraphicsView::mouseReleaseEvent(ev);
}
void GraphicsView::mousePressEvent(QMouseEvent* ev)
{
    qDebug()<<"Current item = "<<m_currentItem;
    if(m_currentItem && ev->buttons() == Qt::LeftButton) {
        m_drawableItem = m_currentItem->create(); // = new GGraphicsRectItem;
        m_drawableItem->setStartPoint(ev->pos() + QPoint(horizontalScrollBar()->value(), verticalScrollBar()->value()));
        if(m_gScene) {
            m_gScene->addItem(m_drawableItem);
        }
    }


    qDebug()<<"GraphicsView::mousePressEvent";
    QGraphicsView::mousePressEvent(ev);
}
void GraphicsView::mouseMoveEvent(QMouseEvent* ev)
{
    if(m_drawableItem && ev->buttons() == Qt::LeftButton) {
        qDebug()<<"inside if";
        QPoint point = (ev->pos()); // + QPoint(horizontalScrollBar()->value(), verticalScrollBar()->value()));
        QList<QPoint> itemsList;
        itemsList << point;
        m_drawableItem->changeSize(ev->pos());
        update();
    }
}


void GraphicsView::paintEvent(QPaintEvent* ev)
{
    qDebug()<<"--------------------------------------------------------------GraphicsView paint event";
    QGraphicsView::paintEvent(ev);
}

GGraphicsItem* GraphicsView::getCurrentItem() const
{
    return m_currentItem;
}

void GraphicsView::setCurrentItem(GGraphicsItem* item)
{
    qDebug()<<"GraphicsScene::setCurrentItem";
    delete m_currentItem;
    m_currentItem = item;
}

//---------------------------------------------------------------------GGraphicsScene----------------
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


void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    qDebug()<<"vfdbvjdbfvvbdfvdbvdbvdvbdjfvdjbvdvjdbvjdb";
}

void GraphicsScene::drawCoordinateLines()
{
    addLine(10,0,10,100, QPen(QBrush(Qt::green),10));
}


