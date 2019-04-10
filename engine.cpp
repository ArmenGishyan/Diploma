#include "engine.h"
#include "mainwindow.h"
#include "editor.h"
#include "ggraphicsitems.h"
#include <QGraphicsRectItem>
#include <QList>
#include <QRect>

Engine::Engine()
{
    m_mainWindow = new MainWindow;
    m_mainWindow->show();
    m_mainWindow->initEngine(this);
}

std::vector<Rectangle> Engine::getRectangles() const
{
   const Editor* editor = m_mainWindow ? m_mainWindow->getEditor() : nullptr;

   std::vector<Rectangle> rectVector;
   QList<GRectItem*> rectItems;
   if(editor) {
       rectItems = editor->getShapeItems<GRectItem*>();
       auto text = editor->getShapeItems<QGraphicsTextItem*>();
       int x = 10;
       ++x;
   }

   for(int i = 0; i < rectItems.size(); ++i) {
       QRect rect = rectItems[i]->rect().toRect();
       QPoint topLeft = rect.topLeft();
       QPoint bottomRight = rect.bottomRight();
       rectVector.push_back(Rectangle(Point(topLeft.x(), topLeft.y()), Point(bottomRight.x(), bottomRight.y())));
   }

   return rectVector;

}
