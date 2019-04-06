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

    setFixedSize(1500, 800);
    m_grScene  = new GraphicsScene(this);
    m_grView = new GraphicsView(m_grScene);
    QHBoxLayout* lay = new QHBoxLayout;;
    lay->addWidget(m_grView);
    setLayout(lay);
}

void Editor::paintEvent(QPaintEvent* p)
{
    QPainter painter(this);
    QRect rec(10,10,50,50);

    painter.setPen(Qt::blue);
    painter.drawRect(rec);

    painter.setFont(QFont("Arial", 30));
    painter.drawText(rect(), Qt::AlignCenter, "Qt");
    qDebug()<<"paint event";
    QWidget::paintEvent(p);
}

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
void Editor::setCurrentItem(QGraphicsItem* item)
{
    if(item && m_grScene) {
        GGraphicsItem* gItem = dynamic_cast<GGraphicsItem*>(item);
        Q_ASSERT(gItem);
        m_grScene->setCurrentItem(gItem);
    }
}


