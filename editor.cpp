#include "editor.h"
#include <QPen>
#include <QBrush>
#include <QPainter>
#include <QRect>
#include <QDebug>
#include <QMouseEvent>
#include <QPoint>
#include <QDrag>
#include <QMimeData>
#include <QUrl>
#include <QPushButton>


Editor::Editor(QWidget* parent):QWidget (parent)
{
    m_pen = QPen();
    m_brush = QBrush();

   // setFixedSize(QSize(300,300));
   // setFixedSize(parent->width(), parent->height());
    qDebug()<<"parent  width = "<<parent->width();
    qDebug()<<"parent height = "<<parent->height();
    m_grScene  = new GraphicsScene(this);
    m_grView = new GraphicsView(m_grScene, this);
    m_grScene->setSceneRect(0,0,100, 100);
    //m_grScene->setSceneRect(0,0,this->width(), this->height());
    setStyleSheet("background-color: #F08080");

    QHBoxLayout* lay = new QHBoxLayout;
    qDebug()<<"View rect = "<<m_grView->rect();
    qDebug()<<"Scene rect = "<<m_grScene->sceneRect();
    lay->addWidget(m_grView);
    setLayout(lay);
}

void Editor::paintEvent(QPaintEvent* p)
{
    QPainter painter(this);
    painter.drawLine(QPoint(0,0), QPoint(50,0));
    painter.drawLine(QPoint(0,0), QPoint(0,50));
    m_grScene->update();
    QWidget::paintEvent(p);
}

//void Editor::resizeEvent(QResizeEvent *event)
//{
//    qDebug()<<"--------------"<<"Editor::resizeEvent";
//    m_grView->setFixedSize(this->width(), this->height());
//    m_grScene->setSceneRect(this->rect());
//    //QWidget::resizeEvent(event);
//}

void Editor::mouseMoveEvent(QMouseEvent* ev)
{
    QPoint po = ev->pos();
    QPainter ptr(this);
    ptr.setPen(Qt::green);

    ptr.drawPoint(po);

    qDebug()<<"mouse move";
    QWidget::mouseMoveEvent(ev);
}

void Editor::mousePressEvent(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton) {
        QDrag *drag = new QDrag(this);
        QMimeData *mimeData = new QMimeData;

        mimeData->setText("Armen Gishyan");
        drag->setMimeData(mimeData);
        drag->setPixmap(QPixmap());

        //Qt::DropAction dropAction = drag->exec();
    }

    QWidget::mousePressEvent(event);
}

void Editor::dragMoveEvent(QDragMoveEvent *event)
{
    qDebug()<<"dragMoveEvent";
    if(event->mimeData()->hasFormat("text/plain") /*&& event->answerRect().intersects(drowFrame->)*/)
        event->acceptProposedAction();

    QWidget::dragMoveEvent(event);
}

void Editor::dragEnterEvent(QDragEnterEvent* event)
{
    qDebug()<<"dragEnterEvent";
    if(event->mimeData()->hasUrls())
        event->acceptProposedAction();

    QWidget::dragEnterEvent(event);
}

void Editor::dropEvent(QDropEvent* eve)
{
    qDebug()<<"dropEvent";
    if(eve->mimeData()->hasUrls()) {
       // foreach(QUrl url, eve->mimeData()->hasUrls()) {
       //     qDebug()<<"hello";
       // }
    }
    QWidget::dropEvent(eve);
}

// set Current QGraphics Item
void Editor::setCurrentItem(GGraphicsItem* item)
{
    if(item && m_grScene) {
        m_grView->setCurrentItem(item);
    }
}

void Editor::clearAll()
{
    qDebug()<<"Editor::clear";
    if(m_grScene) {
        m_grScene->clear();
        m_grScene->update();
        m_grScene->drawCoordinateLines();
    }
}
