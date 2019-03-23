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

class RectItem;

class GraphicsScene : public QGraphicsScene
{
  public:
    GraphicsScene(QObject* parent = nullptr);
    void mousePressEvent(QGraphicsSceneMouseEvent* ev) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* ev) override;
    QVector<QRect> getRects() const;
    void drawCoordinateLines();
};

class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    GraphicsView() = default;
    GraphicsView(QGraphicsScene* scene, QWidget* parent = nullptr);
    virtual ~GraphicsView(){}
    virtual void print(){}
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
    QStack<RectItem*> m_items;
    QToolButton* rectSelect;
    QToolButton* m_paint;
    bool m_mousePress;
    QGraphicsScene* m_scene;
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

class MyWidget : public QWidget
{
    Q_OBJECT
public:
    MyWidget(int count, QWidget* parent = nullptr): QWidget(parent)
    {
        QGridLayout* lay = new QGridLayout;
        m_list = new QListWidget(this);
        m_list->setSelectionMode(QAbstractItemView::MultiSelection);
        for(int i = 0;i<count;++i) {
           m_list->addItem(new QListWidgetItem("item ("+QString::number(i)+")"));
           m_list->item(i)->setCheckState(Qt::Checked);
           m_list->item(i)->setFlags(Qt::ItemIsDragEnabled | Qt::ItemIsEnabled);
        }

        lay->addWidget(m_list);
        qDebug()<<"flags"<<m_list->item(1)->flags();
        if(m_list->item(3)->flags() & Qt::ItemIsSelectable) {
            qDebug()<<"is Selectable";
        } else {
            qDebug()<<"not selectabvle";
        }
        connect(m_list, SIGNAL(itemSelectionChanged()), this, SLOT(itemSelect()));
        setLayout(lay);
    }
public slots:
    void itemSelect()
    {
        qDebug()<<m_list->selectedItems();
    }
private:
    QListWidget* m_list;

};





#endif // GRAPHICSVIEW_H
