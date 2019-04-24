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

    //m_gScene->setSceneRect(QRectF(this->rect()));


    setBackgroundBrush(QBrush("#171F32", Qt::Dense1Pattern));

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
        QList<QGraphicsItem*> item = m_gScene->selectedItems();
        update();
        for(int i=0; i< item.size(); ++i) {
            item[i]->setSelected(true);
        }
    }

    qDebug()<<"GraphicsView::mouseReleaseEvent size = "<<items().size();
    QGraphicsView::mouseReleaseEvent(ev);
}
void GraphicsView::mousePressEvent(QMouseEvent* ev)
{
    qDebug()<<"Current item = "<<m_currentItem;
    if(!m_currentItem) {
        m_drawableItem = nullptr;
    }

    if(m_currentItem &&ev->buttons() == Qt::LeftButton) {
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
    if(m_drawableItem) {
        if(ev->buttons() == Qt::LeftButton) {
            qDebug()<<"inside if";
            QPoint point = (mapToScene(ev->pos() + QPoint(horizontalScrollBar()->value(), verticalScrollBar()->value())).toPoint()); // + QPoint(horizontalScrollBar()->value(), verticalScrollBar()->value()));
            QList<QPoint> itemsList;
            itemsList << point;
            m_drawableItem->changeSize(point);
            update();
        } else {
            QPainter painter(this);
            painter.drawText(ev->pos(), QString::number(ev->pos().x())+", " + QString::number(ev->pos().y()));

        }
    }
}


void GraphicsView::paintEvent(QPaintEvent* ev)
{
   // qDebug()<<"--------------------------------------------------------------GraphicsView paint event";
    QGraphicsView::paintEvent(ev);
    QPainter painter(this);
    QPen pen;
    pen.setWidth(5);
    pen.setColor(QColor(Qt::red));
    painter.setPen(pen);
    painter.drawLine(QPoint(0,0), QPoint(500,500));

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

void GraphicsView::mouseDoubleClickEvent(QMouseEvent* event)
{
    const auto trans = QGraphicsView::transform();
    if(!m_gScene)
        return;
    QGraphicsItem* item = m_gScene->itemAt(mapToScene(event->pos()), trans);
    qDebug()<<"event pos =------------------------------------------------------------------------ "<<event->pos();
    assert(item && "item == nullptr");
    GGraphicsItem* gItem = qgraphicsitem_cast<GGraphicsItem*>(item);
    assert(gItem && "GItem == nullptr");
    if(gItem) {
        gItem->setItemSelected(!gItem->isSelected());
    }
    if(m_gScene) {
       m_gScene->update();
    }

    qDebug()<<"GraphicsView::mouseDoubleClickEvent";
    QGraphicsView::mouseDoubleClickEvent(event);
}

QList<GGraphicsItem*> GraphicsView::getSelectedItems()
{
    QList<GGraphicsItem*> selectedItem;
    QList<QGraphicsItem*> items = this->items();
    for(QGraphicsItem* it : items) {
        GGraphicsItem* gItem = qgraphicsitem_cast<GGraphicsItem*>(it);
        if(gItem && gItem->isSelected()) {
            selectedItem.push_back(gItem);
        }
    }
    return selectedItem;
}

//---------------------------------------------------------------------GGraphicsScene----------------
GraphicsScene::GraphicsScene(QObject* parent):QGraphicsScene (parent)
{
    assert(connect(this, SIGNAL(focusItemChanged(QGraphicsItem*, QGraphicsItem*, Qt::FocusReason)), this, SLOT(handleFocusItemChanged(QGraphicsItem*, QGraphicsItem*, Qt::FocusReason))));
    drawCoordinateLines();
}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent* ev)
{
    qDebug()<<"mousePressEvent";
    //QGraphicsScene::mousePressEvent(ev);
}
void GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* ev)
{
    qDebug()<<"mouseReleaseEvent";
    //QGraphicsScene::mouseReleaseEvent(ev);
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

    addLine(QLine(0,0, 1000, 0), QPen(QColor(Qt::yellow)));
    addLine(QLine(0,0, 0, 1000), QPen(QColor(Qt::yellow)));
    addLine(QLine(0,0, -1000, 0), QPen(QColor(Qt::yellow)));
    addLine(QLine(0,0, 0, -1000), QPen(QColor(Qt::yellow)));

}

void GraphicsScene::handleFocusItemChanged(QGraphicsItem *newFocusItem, QGraphicsItem *oldFocusItem, Qt::FocusReason reason)
{
    qDebug()<<"------------------------------------------------GraphicsScene::handleFocusItemChanged";
}

//bool GraphicsScene::eventFilter(QObject* object, QEvent* event)
//{
//    //assert(false);
//    if(event->type() == QEvent::GraphicsSceneMousePress || event->type() == QEvent::GraphicsSceneMouseRelease) {
//        //assert(false);
//        return true;
//    }
//    return false;
//}
