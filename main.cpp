#include <iostream>
#include <algorithm>
#include <list>
#include <QDebug>
//#include "graph.h"
#include "shortestpathproblem.h"
#include "engine.h"

#include "mainwindow.h"
#include <QApplication>
#include <QColorDialog>
#include <QtQml/QJSValue>
#include <QQmlEngine>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQmlComponent>
#include <QVariantList>
#include <stack>
#include <set>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Engine engine;
  //  engine.createGraph<int, Rectangle>();
  //  engine.findPath<Rectangle>();
  //  MainWindow w;
  //  w.show();

	Graph<int> obj;
    Node<int>* ccA = new Node<int>("A");
    Node<int>* ccB = new Node<int>("B");
    Node<int>* ccC = new Node<int>("C");
    Node<int>* ccD = new Node<int>("D");
    Node<int>* ccE = new Node<int>("E");
    Node<int>* ccF = new Node<int>("F");
    Node<int>* ccX = new Node<int>("X");
    Node<int>* ccY = new Node<int>("Y");

    obj.addNode(ccA);
    obj.addNode(ccB);
    obj.addNode(ccC);
    obj.addNode(ccD);
    obj.addNode(ccE);
    obj.addNode(ccF);
    obj.addNode(ccX);
    obj.addNode(ccY);

    obj.connNodes(ccA, ccB, 1);
    obj.connNodes(ccB, ccC, 1);
    obj.connNodes(ccC, ccD, 1);
    obj.connNodes(ccD, ccE, 1);
    obj.connNodes(ccE, ccF, 1);
    obj.connNodes(ccA, ccX, 2);
    obj.connNodes(ccX, ccY, 2);
    obj.connNodes(ccY, ccF, 2);
    obj.connNodes(ccA, ccF, 10);


//	Node<int>* cc5 = new Node<int>("4");
//	Node<int>* cc6 = new Node<int>("5");


//	obj.addNode(cc1);
//	obj.addNode(cc2);
//	obj.addNode(cc3);
//	obj.addNode(cc4);
//	obj.addNode(cc5);
//	obj.addNode(cc6);

  //  obj.connNodes(cc1, cc2);
  //  obj.connNodes(cc2, cc3);
  //  obj.connNodes(cc3, cc1);
  ////  obj.connNodes(cc2, cc5);
  //  obj.connNodes(cc2, cc4);
   // obj.connNodes(cc3, cc5);
   // obj.connNodes(cc4, cc5);
   // obj.connNodes(cc4, cc6);
   // obj.connNodes(cc5, cc6);

    std::vector<Node<int>*> shortVec = ShortestPathProblem<int>::shortestPath(obj, ccA, ccF);
    std::cout << "------------------Shortest Path---------------------- " << std::endl;

    std::for_each(shortVec.begin(), shortVec.end(), [](Node<int>* it) {std::cout << "<< " << it->name(); });
    std::cout << std::endl;

    std::vector<Node<int>*> nodes = obj.BFS();
    std::cout << "------------------BFS---------------------- " << std::endl;

    std::for_each(nodes.begin(), nodes.end(), [](Node<int>* it) {std::cout << "<< " << it->name(); });
    std::cout << std::endl;
    std::vector<int> vec;
    std::cout << "-----------------DFS--------------------- " << std::endl;

    std::vector<Node<int>*> list = obj.DFS();
    std::for_each(list.begin(), list.end(), [](Node<int>* it) {std::cout << "<< " << it->name(); });

    std::cout << "\n-----------------print--------------------- " << std::endl;

	obj.print();


//    std::cout<<"----------------------------after delete--------------\n";
//
//    std::vector<Node<int>*> nodes1 = obj.BFS();
//    std::cout << "------------------BFS---------------------- " << std::endl;
//
//    std::for_each(nodes1.begin(), nodes1.end(), [](Node<int>* it) {std::cout << "<< " << it->name(); });
//    std::cout << std::endl;
//    std::vector<int> vec1;
//    std::cout << "-----------------DFS--------------------- " << std::endl;
//
//    std::vector<Node<int>*> list1 = obj.DFS();
//    std::for_each(list1.begin(), list1.end(), [](Node<int>* it) {std::cout << "<< " << it->name(); });
//
//    std::cout << "\n-----------------print--------------------- " << std::endl;
//
//    obj.print();
//
//    std::cout << "-----------------DFS--------------------- " << std::endl;
//    std::vector<Node<int>*> list2 = obj.DFS();
//    std::for_each(list2.begin(), list2.end(), [](Node<int>* it) {std::cout << "<< " << it->name(); });
//
//    std::cout << "\n-----------------print--------------------- " << std::endl;
   // std::vector<int> vec34 = {1,2,3,4,5,6,7};
   // std::remove(std::find(vec34.begin(), vec34.end(), 3), vec.end());


      // qmlRegisterType<Person>("People", 1,0, "Person");

    //  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    //  QQmlApplicationEngine qmengine;
    //  QVariantList rectlist;
    //  rectlist<<QRect{50, 30, 100, 100}
    //          << QRect{200, 20, 30, 30}
    //          <<QRect{300, 300, 200, 33}
    //          <<QRect{400, 23, 44, 55};
    //  qmengine.rootContext()->setContextProperty("rectlist", rectlist);
    //  qmengine.load(QUrl(QStringLiteral("qrc:/example.qml")));
    //  if (qmengine.rootObjects().isEmpty())
      //        return -1;


    return a.exec();
}
