#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMenuBar>
#include <QMenu>
#include <QDebug>
#include <QIcon>
#include <QToolButton>
#include <editor.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createMenuBar();
    createToolBar();
    createFileMenu();
}

MainWindow::~MainWindow()
{
    qDebug()<<"Destructor";
    m_menuBar->deleteLater();
    delete ui;
}

void MainWindow::createToolBar()
{
    m_mainToolBar = new QToolBar(this);
    m_drawLine = new QToolButton(m_mainToolBar);
    m_drawLine->setIcon(QIcon(":/Icons/line.png"));
    m_drawLine->setText("Draw Line");

    m_drawRect = new QToolButton(m_mainToolBar);
    m_drawRect->setIcon(QIcon(":/Icons/rect.png"));
    m_drawRect->setText("Draw Rect");

    m_drawPoint = new QToolButton(m_mainToolBar);
    m_drawPoint->setIcon(QIcon(":/Icons/point.png"));
    m_drawPoint->setText("Draw Point");

    m_mainToolBar->addWidget(m_drawLine);
    m_mainToolBar->addWidget(m_drawRect);
    m_mainToolBar->addWidget(m_drawPoint);

    //init Editor
    initEditor();
    setCentralWidget(m_editor);

    addToolBar(m_mainToolBar);
}

void MainWindow::createMenuBar()
{
    m_menuBar = new QMenuBar(this);
    setMenuBar(m_menuBar);
}

void MainWindow::createFileMenu()
{
    m_fileMenu = menuBar()->addMenu("File");
    m_fileMenu->addAction(new QAction("New"));
    m_fileMenu->addAction(new QAction("Open"));
    m_fileMenu->addAction(new QAction("Save"));
    m_fileMenu->addAction(new QAction("Save As"));

    QList<QAction*> it = m_fileMenu->actions();
}

void MainWindow::createDrawMenu()
{

}


void MainWindow::initEditor()
{
    m_editor = new Editor(this);
}
