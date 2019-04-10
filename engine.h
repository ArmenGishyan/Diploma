#ifndef ENGINE_H
#define ENGINE_H

#include "polygons.h"
#include <vector>

class MainWindow;
class QRect;

template <class T>
class Graph;

class Engine
{
public:
    Engine();
    template<class T>
    Graph<T>* createGraph() const;
    std::vector<Rectangle> getRectangles() const;

private:
    MainWindow* m_mainWindow;
};

template <class T>
Graph<T>* Engine::createGraph() const
{
    Graph<T>* graph = new Graph<T>();

}

#endif // ENGINE_H
