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
    createStyleToolBar();

    //init Editor
    initEditor();
    setCentralWidget(m_editor);

    //
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
    m_drawLine = new QAction(m_mainToolBar);
    m_drawLine->setIcon(QIcon(":/Icons/line.png"));
    m_drawLine->setText("Draw Line");

    m_drawRect = new GRectAction(m_mainToolBar);
    m_drawRect->setIcon(QIcon(":/Icons/rect.png"));
    m_drawRect->setText("Draw Rect");

    m_drawPoint = new QAction(m_mainToolBar);
    m_drawPoint->setIcon(QIcon(":/Icons/point.png"));
    m_drawPoint->setText("Draw Point");

    m_mainToolBar->addAction(m_drawLine);
    m_mainToolBar->addAction(m_drawRect);
    m_mainToolBar->addAction(m_drawPoint);
    connect(m_mainToolBar, SIGNAL(actionTriggered(QAction*)), this, SLOT(actionClicked(QAction*)));

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

void MainWindow::createStyleToolBar()
{
    m_styleToolBar = new QToolBar(this);
    connect(m_styleToolBar, SIGNAL(actionTriggered(QAction*)), this, SLOT(styleActionClicked(QAction*)));
    GPenColor* lineColor = new GPenColor;
    lineColor->setText("Color");
    lineColor->setIcon(QIcon(":/Icons/color.png"));
    m_styleToolBar->addAction(lineColor);

    GPenStyle* penStyle = new GPenStyle;
    penStyle->setText("Pen Style");
    penStyle->setIcon(QIcon(":/Icons/penStyle.png"));
    m_styleToolBar->addAction(penStyle);


    addToolBar(Qt::LeftToolBarArea, m_styleToolBar);
}
void MainWindow::initEditor()
{
    m_editor = new Editor(this);
}

void MainWindow::actionClicked(QAction* action)
{
    qDebug()<<"actionClicked";
    GAction* gaction = dynamic_cast<GAction*>(action);
    m_editor->setCurrentItem(gaction->getObject());
}

void MainWindow::styleActionClicked(QAction* action)
{
    GStyleAction* styleAction = dynamic_cast<GStyleAction*>(action);
    if(styleAction) {
        styleAction->execute(m_editor);
    }
}
