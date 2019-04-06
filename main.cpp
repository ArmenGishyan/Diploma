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
	Node<int>* cc1 = new Node<int>("0");
	Node<int>* cc2 = new Node<int>("1");
	Node<int>* cc3 = new Node<int>("2");
	Node<int>* cc4 = new Node<int>("3");
	Node<int>* cc5 = new Node<int>("4");
	Node<int>* cc6 = new Node<int>("5");


	obj.addNode(cc1);
	obj.addNode(cc2);
	obj.addNode(cc3);
	obj.addNode(cc4);
	obj.addNode(cc5);
	obj.addNode(cc6);

	obj.connNodes(cc1, cc2);
	obj.connNodes(cc2, cc3);
	obj.connNodes(cc3, cc1);
	obj.connNodes(cc2, cc5);
	obj.connNodes(cc2, cc4);
	obj.connNodes(cc3, cc5);
	obj.connNodes(cc4, cc5);
	obj.connNodes(cc4, cc6);
	obj.connNodes(cc5, cc6);

   // qDebug()<<ShortestPathProblem<int>::shortestPath(obj, cc1, cc2);

	std::vector<Node<int>*> nodes = obj.BFS();
	std::cout << "------------------BFS---------------------- " << std::endl;

	std::for_each(nodes.begin(), nodes.end(), [](Node<int>* it) {std::cout << "<< " << it->name; });
	std::cout << std::endl;
	std::vector<int> vec;
	std::cout << "-----------------DFS--------------------- " << std::endl;

	std::vector<Node<int>*> list = obj.DFS();
	std::for_each(list.begin(), list.end(), [](Node<int>* it) {std::cout << "<< " << it->name; });

	std::cout << "\n-----------------print--------------------- " << std::endl;

	obj.print();

    obj.deleteNode(cc1);


    qDebug()<<"----------------------------after delete";

    std::vector<Node<int>*> nodes1 = obj.BFS();
    std::cout << "------------------BFS---------------------- " << std::endl;

    std::for_each(nodes1.begin(), nodes1.end(), [](Node<int>* it) {std::cout << "<< " << it->name; });
    std::cout << std::endl;
    std::vector<int> vec1;
    std::cout << "-----------------DFS--------------------- " << std::endl;

    std::vector<Node<int>*> list1 = obj.DFS();
    std::for_each(list1.begin(), list1.end(), [](Node<int>* it) {std::cout << "<< " << it->name; });

    std::cout << "\n-----------------print--------------------- " << std::endl;

    obj.print();
    return a.exec();
}
