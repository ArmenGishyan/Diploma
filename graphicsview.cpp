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
#include <QPainterPath>

GraphicsView::GraphicsView(GraphicsScene* gScene, QWidget* parent):QGraphicsView (gScene, parent)
{
    m_gScene = gScene;
   // gScene->setSceneRect(this->rect());

    //m_gScene->setSceneRect(QRectF(this->rect()));


    setBackgroundBrush(QBrush("#C3E1F5", Qt::SolidPattern));

    m_currentItem = nullptr;
    m_drawableItem = nullptr;

    int height = parent->rect().height(); // + QPoint(50,50);
    int width = parent->rect().width(); //- QPoint(50,50);

    //setFixedSize(height, width);
    //setSceneRect(QRectF(0, 0, 690, 800)); // 295, 295));
    setMouseTracking(true);

    QGridLayout* lay = new QGridLayout;
    setLayout(lay);
    //scale(1, -1);

    rotate(270);
}

void GraphicsView::mouseReleaseEvent(QMouseEvent* ev)
{
    if(m_drawableItem && ev->buttons() == Qt::LeftButton) {

        m_drawableItem->setEndPoint(mapToScene(ev->pos() + QPoint(horizontalScrollBar()->value(), verticalScrollBar()->value())).toPoint());
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
        m_drawableItem = m_currentItem->create();
        m_drawableItem->setStartPoint(mapToScene(ev->pos() + QPoint(horizontalScrollBar()->value(), verticalScrollBar()->value())).toPoint());
        qDebug()<<"Scence rect = "<<scene()->sceneRect();
        if(m_gScene) {
            QList<QGraphicsItem*> items = m_gScene->items();
            m_drawableItem->setName("Shape_"+QString::number(items.count()));
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
        QPoint point = (mapToScene(ev->pos() + QPoint(horizontalScrollBar()->value(), verticalScrollBar()->value())).toPoint()); // + QPoint(horizontalScrollBar()->value(), verticalScrollBar()->value()));
        QList<QPoint> itemsList;
        itemsList << point;
        m_drawableItem->changeSize(point);
        update();
    }
}


void GraphicsView::paintEvent(QPaintEvent* ev)
{
   // qDebug()<<"--------------------------------------------------------------GraphicsView paint event";
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
   // addLine(QLine(0,0, 100, 0), QPen(QColor(Qt::yellow)));
   // addLine(QLine(0,0, 0, 100), QPen(QColor(Qt::yellow)));
}


