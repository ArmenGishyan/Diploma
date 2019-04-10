#include "engine.h"
#include "mainwindow.h"
#include "editor.h"
#include <QGraphicsRectItem>
#include <QList>
#include <QRect>

Engine::Engine()
{
    m_mainWindow = new MainWindow;
    m_mainWindow->show();
}

std::vector<Rectangle> Engine::getRectangles() const
{
   const Editor* editor = m_mainWindow ? m_mainWindow->getEditor() : nullptr;

   std::vector<Rectangle> rectVector;
   QList<QGraphicsRectItem*> rectItems;
   if(editor) {
       rectItems = editor->getShapeItems<QGraphicsRectItem*>();
   }

   for(int i = 0; i < rectItems.size(); ++i) {
       QRect rect = rectItems[i]->rect().toRect();
       QPoint topLeft = rect.topLeft();
       QPoint bottomRight = rect.bottomRight();
       rectVector.push_back(Rectangle(Point(topLeft.x(), topLeft.y()), Point(bottomRight.x(), bottomRight.y())));
   }

   return rectVector;

}
