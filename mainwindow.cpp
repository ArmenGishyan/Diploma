#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMenuBar>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    createMenuBar();
    createToolBar();
}

MainWindow::~MainWindow()
{
    qDebug()<<"Destructor";
    m_menuBar->deleteLater();
    m_mainToolBar->deleteLater();
}

void MainWindow::createToolBar()
{
    m_mainToolBar = new QToolBar(nullptr);
    m_mainToolBar->addAction(new QAction("Rect"));

    addToolBar(m_mainToolBar);
}

void MainWindow::createMenuBar()
{
    m_menuBar = new QMenuBar(this);
    QMenu* fileMenu = new QMenu("File");
    fileMenu->addAction(new QAction("New"));
    menuBar()->addMenu(fileMenu);
    setMenuBar(m_menuBar);
}
