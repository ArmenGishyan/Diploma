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

#include "ggraphicsstyle.h"

Editor::Editor(QWidget* parent):QWidget (parent)
{
    int x = this->width();
    int y = this->height();
    m_grScene  = new GraphicsScene(this);
    m_grView = new GraphicsView(m_grScene, this);
    m_grScene->setSceneRect(0,0, 1150, 500);
    installEventFilter(m_grScene);
    //m_grScene->setSceneRect(0,0,this->width(), this->height());
    setStyleSheet("background-color: #F08080");

    QHBoxLayout* lay = new QHBoxLayout;
    lay->addWidget(m_grView);
    setLayout(lay);
}

void Editor::paintEvent(QPaintEvent* p)
{
   // QPainter painter(this);
   // painter.drawLine(QPoint(0,0), QPoint(50,0));
   // painter.drawLine(QPoint(0,0), QPoint(0,50));
   // m_grScene->update();
    QWidget::paintEvent(p);
}

//void Editor::resizeEvent(QResizeEvent *event)
//{
//    m_grView->setFixedSize(this->width(), this->height());
//    m_grScene->setSceneRect(this->rect());
//    //QWidget::resizeEvent(event);
//}

void Editor::mouseMoveEvent(QMouseEvent* ev)
{
    QWidget::mouseMoveEvent(ev);
    QPoint po = ev->pos();
    //QPainter ptr(this);
    //ptr.setPen(Qt::green);

    //ptr.drawPoint(po);

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
    if(event->mimeData()->hasFormat("text/plain") /*&& event->answerRect().intersects(drowFrame->)*/)
        event->acceptProposedAction();

    QWidget::dragMoveEvent(event);
}

void Editor::dragEnterEvent(QDragEnterEvent* event)
{
    if(event->mimeData()->hasUrls())
        event->acceptProposedAction();

    QWidget::dragEnterEvent(event);
}

void Editor::dropEvent(QDropEvent* eve)
{
    if(eve->mimeData()->hasUrls()) {
       // foreach(QUrl url, eve->mimeData()->hasUrls()) {
       // }
    }
    QWidget::dropEvent(eve);
}

// set Current QGraphics Item
void Editor::setCurrentItem(GGraphicsItem* item)
{
    if(m_grView) {
        m_grView->setCurrentItem(item);
    }
}

void Editor::clearAll()
{
    if(m_grScene) {
        auto selItems = m_grScene->selectedItems();
        int i = 0;
        ++i;
        m_grScene->clear();
        m_grScene->update();
        m_grScene->drawCoordinateLines();
    }
}


QList<GGraphicsItem*> Editor::getSelectedItems() const
{
    if(m_grView) {
        auto items = m_grView->getSelectedItems();
        return m_grView->getSelectedItems();
    }

    return QList<GGraphicsItem*>();
}

void Editor::selectItems(const QList<QString>& itemsName)
{
     std::shared_ptr<GGraphicsStyle> style = std::make_shared<GGraphicsStyle>(GGraphicsItem::getSelectionStyle()->get()->pen(), GGraphicsItem::getSelectionStyle()->get()->brush());
     selectItems(itemsName, style);
}

void Editor::selectItems(const QList<QString>& itemsName, const std::shared_ptr<GGraphicsStyle>& style)
{
     QList<GGraphicsItem*> items = Converter::convert(m_grScene->items());
     auto findSelection = [&itemsName, &style](GGraphicsItem* item) {
         for(const auto& name : itemsName) {
             if(name == QString::fromStdString(item->name())) {
                 item->setStyle(style);
             }
         }};

     std::for_each(items.begin(), items.end(), findSelection);
     if(m_grScene) {
        m_grScene->update();
     }
}
void Editor::selectItems(const QList<GGraphicsItem*>& itemsName)
{

}

void Editor::clearSelectedItems()
{
    if(m_grView) {
        QList<GGraphicsItem*> items = m_grView->getSelectedItems();
        for(GGraphicsItem* it : items) {
            delete it;
        }
    }
}

QList<GGraphicsItem*> Converter::convert(const QList<QGraphicsItem*>& items)
{
    QList<GGraphicsItem*> gItems;
    for(int i = 0; i< items.size(); ++i) {
         GGraphicsItem* item = qgraphicsitem_cast<GGraphicsItem*>(items[i]);
         if(item) {
            gItems.push_back(item);
         }
    }
    return gItems;
}

void Editor::addShapes(QList<GGraphicsItem*> shapes)
{
    if(m_grScene) {
        for(GGraphicsItem* item : shapes) {
           m_grScene->addItem(item);
        }
    }
}

void Editor::setStyle(const std::shared_ptr<GGraphicsStyle>& style, bool force)
{
    if(m_grView) {
        m_grView->setStyle<GGraphicsRectItem>(style, force);
    }
}

std::shared_ptr<GGraphicsStyle> Editor::getStyle() const
{
    if(m_grView) {
        return m_grView->getStyle();
    }
}

void Editor::toDefaultState()
{
    if(m_grView) {
        m_grView->selectUnselectAll(false);
    }
}
