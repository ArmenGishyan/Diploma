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

GraphicsView::GraphicsView(QGraphicsScene* scene, QWidget* parent):QGraphicsView (scene, parent)
                                                                  ,m_scene(scene)
{
    this->setSceneRect(QRectF(0,0,1000, 1000));
    rectSelect = new QToolButton(this);
    m_paint = new QToolButton(this);
    m_paint->setText("paint");
    m_paint->setGeometry(100,0,60,30);
    m_paint->setCheckable(true);
    connect(m_paint, SIGNAL(clicked(true)), this, SLOT(sendEvent()));
    rectSelect->setText("Rect");
    rectSelect->setCheckable(true);

    QGridLayout* lay = new QGridLayout;
    setLayout(lay);

}

void GraphicsView::mouseReleaseEvent(QMouseEvent* ev)
{
    m_mousePress = false;
    if(rectSelect->isChecked()) {
       QRectF rect = m_items.top()->rect();
       rect.setBottomRight(ev->pos() + QPoint(horizontalScrollBar()->value(), verticalScrollBar()->value()));
       m_items.top()->setRect(rect);
       update();
    }
    qDebug()<<"GraphicsView::mouseReleaseEvent size = "<<items().size();
    QGraphicsView::mouseReleaseEvent(ev);
}
void GraphicsView::mousePressEvent(QMouseEvent* ev)
{
    if(rectSelect->isChecked()) {
       m_mousePress = true;
       m_items.push(new RectItem());
       QPoint pos = ev->pos() + QPoint(horizontalScrollBar()->value(), verticalScrollBar()->value());
       QRect rect(pos,pos);
       m_items.top()->setRect(rect);
       m_scene->addItem(m_items.top());
    }
    qDebug()<<"GraphicsView::mousePressEvent";
    QGraphicsView::mousePressEvent(ev);
}
void GraphicsView::mouseMoveEvent(QMouseEvent* ev)
{
    if(m_mousePress && rectSelect->isChecked()) {
       QRectF rect = m_items.top()->rect();
       rect.setBottomRight(ev->pos() + QPoint(horizontalScrollBar()->value(), verticalScrollBar()->value()));
       m_items.top()->setRect(rect);
       m_items.top()->reDrawCoordinate();
    }

    qDebug()<<"GraphicsView::mouseMoveEvent";
    QGraphicsView::mouseMoveEvent(ev);
}

void GraphicsView::paintEvent(QPaintEvent* ev)
{
    if(m_paint->isChecked()) {
        m_scene->addItem(new QGraphicsRectItem(QRect(50,50,200,200)));
        qDebug()<<"Rect Added";
    }
    qDebug()<<"GraphicsView paint event";
    QGraphicsView::paintEvent(ev);
}
GraphicsScene::GraphicsScene(QObject* parent):QGraphicsScene (parent)
{
    drawCoordinateLines();

    // setSceneRect(0 , -800, 800, 0);
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
   // qDebug()
   // for()
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

void GraphicsScene::drawCoordinateLines()
{
    addLine(10,0,10,100, QPen(QBrush(Qt::green),10));
}
