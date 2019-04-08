#include <iostream>
#include <algorithm>
#include <list>
#include <QDebug>
//#include "graph.h"
#include "shortestpathproblem.h"

#include "mainwindow.h"
#include <QApplication>
#include <QColorDialog>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

	Graph<int> obj;
    Node<int>* ccA = new Node<int>("A");
    Node<int>* ccB = new Node<int>("B");
    Node<int>* ccC = new Node<int>("C");
    Node<int>* ccD = new Node<int>("D");

    obj.addNode(ccA);
    obj.addNode(ccB);
    obj.addNode(ccC);
    obj.addNode(ccD);
//	obj.addNode(cc5);
//	obj.addNode(cc6);

    obj.connNodes(ccA, ccC, 10);
    obj.connNodes(ccA, ccB, 1);
    obj.connNodes(ccA, ccD, 20);
    obj.connNodes(ccB, ccD, 10);
    obj.connNodes(ccC, ccD, 100);

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

    std::vector<Node<int>*> shortVec = ShortestPathProblem<int>::shortestPath(obj, ccA, ccD);
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
    return a.exec();
}
