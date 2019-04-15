#ifndef ENGINE_H
#define ENGINE_H

#include "polygons.h"
//#include "graphnode.h"
#include <vector>
#include <graph.h>

class MainWindow;
class QRect;

//template <class T>
//class Graph;

class Engine
{
public:
    Engine();
    template<class NodeValueType, class ShapesType>
    Graph<NodeValueType>* createGraph(const std::vector<ShapesType>& vecOfShapes) const;
    std::vector<Rectangle> getRectanglesFromGui() const;
    template<class ShapesType>
    std::vector<ShapesType> findPath() const;

private:
    MainWindow* m_mainWindow;
};

template<class NodeValueType, class ShapeType>
Graph<NodeValueType>* Engine::createGraph(const std::vector<ShapeType>& vecOfShapes) const
{
    Graph<NodeValueType>* graph = new Graph<NodeValueType>();

    const int size = vecOfShapes.size();
    for(int i = 1; i < size; ++i) {
        Rectangle rect = vecOfShapes[i];
        Node<T>* nodePtr = graph->getNode(rect.name());
        if(!nodePtr) {
            nodePtr = new Node<T>(rect.name());
            graph->addNode(nodePtr);
        }

        for(int j = 0; j < size; ++j) {
           if(i == j)
                continue;
           Node<T>* nodePtr = graph->getNode(vecOfShapes[j].name());
           if(!nodePtr) {
               nodePtr = new Node<T>(vecOfShapes[j].name());
               graph->addNode(nodePtr);
           }
           QRectF  intersectRect = rect.squareOfOverlapTest(&vecOfShapes[j]);
           int intersectSquare = static_cast<int>(intersectRect.width() * intersectRect.height());
           intersectSquare /= 300;

           if(intersectSquare == 0)
               continue;
            std::string nameFirst = rect.name();
            std::string nameSecond = vecOfShapes[j].name();
            bool isConnect = graph->connNodes(nameFirst, nameSecond, intersectSquare);
            if(!isConnect) {
                qDebug()<<"Shapes name "<<QString::fromStdString(nameFirst) << QString::fromStdString(nameSecond) <<"/n";
                assert(isConnect && "Cant connaect " ); //+ rect.name() && vecOfShapes[j] + " !!! ");
            }
        }
    }
    return graph;

}

template <class ShapesType>
std::vector<ShapesType> Engine::findPath() const
{
    std::vector<ShapesType> vectorOfShapes = getRectanglesFromGui();
    Graph<int>* graph = createGraph<int, ShapesType>(vectorOfShapes);
    int x = 0;
    ++x;
    return std::vector<ShapesType>();
}

#endif // ENGINE_H
