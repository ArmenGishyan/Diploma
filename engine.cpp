#include "engine.h"
#include "mainwindow.h"
#include "editor.h"
#include "ggraphicsitems.h"
#include <QGraphicsRectItem>
#include <QList>
#include <QRect>

Engine::Engine()
{
    m_priority = SelectEdgeWeight::GraphWeightPriority::OverLapSquare;
    m_mainWindow = new MainWindow;
    m_mainWindow->show();
    m_mainWindow->initEngine(this);
}

std::vector<Rectangle> Engine::getRectanglesFromGui() const
{
   const Editor* editor = m_mainWindow ? m_mainWindow->getEditor() : nullptr;

   Graph<int>* graph = new Graph<int>;
   std::vector<Rectangle> rectVector;
   QList<GGraphicsRectItem*> rectItems;
   if(editor) {
       rectItems = editor->getShapeItems<GGraphicsRectItem*>();
       auto text = editor->getShapeItems<QGraphicsTextItem*>();
       int x = 10;
       ++x;
   }

   for(int i = 0; i < rectItems.size(); ++i) {
       QRect rect = rectItems[i]->rect().toRect();
       QPoint topLeft = rect.topLeft();
       QPoint bottomRight = rect.bottomRight();
       Rectangle rectangle(Point(topLeft.x(), topLeft.y()), Point(bottomRight.x(), bottomRight.y()));
       std::string name = rectItems[i]->name();
       int x =0;
       ++x;
       rectangle.setName(name);
       rectVector.push_back(rectangle);
   }

   return rectVector;

}


