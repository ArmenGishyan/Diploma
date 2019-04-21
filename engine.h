#ifndef ENGINE_H
#define ENGINE_H

#include "polygons.h"
//#include "graphnode.h"
#include <vector>
#include <graph.h>
#include "shortestpathproblem.h"
#include "selectedgeweight.h"

class MainWindow;
class QRect;

class Engine
{
public:
    Engine();
    template<class NodeValueType, class ShapesType>
    Graph<NodeValueType>* createGraph(const std::vector<ShapesType>& vecOfShapes) const;
    std::vector<Rectangle> getRectanglesFromGui() const;
    template<class ShapesType>
    std::vector<std::string> findPath(const std::string& firstName, const std::string& secondName) const;
    void setWeightPriority(SelectEdgeWeight::GraphWeightPriority priority) {m_priority = priority;}
    template<class T>
    int calculateWeight(const T& shape1, const T& shape2) const;

private:
    MainWindow* m_mainWindow;
    SelectEdgeWeight::GraphWeightPriority m_priority;
};

Q_DECLARE_METATYPE(SelectEdgeWeight::GraphWeightPriority);

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
           int weight = calculateWeight(rect, vecOfShapes[j]);
           if(weight == 0)
               continue;
            std::string nameFirst = rect.name();
            std::string nameSecond = vecOfShapes[j].name();
            bool isConnect = graph->connNodes(nameFirst, nameSecond, weight);
            if(!isConnect) {
                qDebug()<<"Shapes name "<<QString::fromStdString(nameFirst) << QString::fromStdString(nameSecond) <<"/n";
                assert(isConnect && "Cant connect " );
            }
        }
    }
    return graph;

}

template <class ShapesType>
std::vector<std::string> Engine::findPath(const std::string& firstName, const std::string& secondName) const
{
    std::vector<ShapesType> vectorOfShapes = getRectanglesFromGui();
    Graph<int>* graph = createGraph<int, ShapesType>(vectorOfShapes);

    Node<T>* first = graph->getNode(firstName);
    Node<T>* second = graph->getNode(secondName);

    std::vector<Node<T>*> vec = ShortestPathProblem<int>::shortestPath(*graph, first, second);
    std::vector<std::string> vecOfPathShapesName;
    vecOfPathShapesName.reserve(vec.size());
    for(const Node<T>* item : vec) {
        vecOfPathShapesName.push_back(item->name());
    }
    return vecOfPathShapesName; // std::vector<ShapesType>();
}

template<class T>
int Engine::calculateWeight(const T& shape1, const T& shape2) const
{
    QRectF  intersectRect = shape1.squareOfOverlapTest(&shape2);
    int weightOfGraphVertex = 0;
    weightOfGraphVertex = static_cast<int>(intersectRect.width() * intersectRect.height());
    if(m_priority == SelectEdgeWeight::GraphWeightPriority::MargeSauare) {
        int margeSquare = shape1.square() + shape2.square();
        weightOfGraphVertex = margeSquare - weightOfGraphVertex;
    }

    weightOfGraphVertex /= 300;
    return weightOfGraphVertex;
}
#endif // ENGINE_H
