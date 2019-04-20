#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMenuBar>
#include <QMenu>
#include <QDebug>
#include <QIcon>
#include <QToolButton>
#include <QDesktopWidget>
#include "editor.h"
#include "dockwidgets.h"
#include "engine.h"
#include <assert.h>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createMenuBar();
    createToolBar();
    createFileMenu();
    createWeigthPriorityMenu();
    createStyleToolBar();

    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int width = screenGeometry.width();
    int height = screenGeometry.height();
    width -= 0.1*width;
    height -= 0.1*height;
   // setFixedSize(QSize(x, y));
    //init Editor
    setMinimumHeight(height);
    setMinimumWidth(width);
    initEditor();
    setCentralWidget(m_editor);

    //create Command Line
    createCommandLineDockW();

    // create Action ToolBar
    createActionToolBar();

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
    m_drawLine = new GLineAction(m_mainToolBar);
    m_drawLine->setIcon(QIcon(":/Icons/line.png"));
    m_drawLine->setText("Draw Line");

    m_drawRect = new GRectAction(m_mainToolBar);
    m_drawRect->setIcon(QIcon(":/Icons/rect.png"));
    m_drawRect->setText("Draw Rect");

    m_drawPoint = new QAction(m_mainToolBar);
    m_drawPoint->setIcon(QIcon(":/Icons/point.png"));
    m_drawPoint->setText("Draw Point");

    GNoneShapeAction* noneShape = new GNoneShapeAction(this);
    noneShape->setIcon(QIcon(":/Icons/noShape.png"));
    noneShape->setText("None Shape");
    m_mainToolBar->addAction(m_drawLine);
    m_mainToolBar->addAction(m_drawRect);
    m_mainToolBar->addAction(m_drawPoint);
    m_mainToolBar->addAction(noneShape);
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
    m_fileMenu->addAction(new QAction("Save As"));

    QAction* openAction = new QAction("Open");
    connect(openAction, SIGNAL(triggered(bool)), this, SLOT(openClicked()));
    m_fileMenu->addAction(new QAction("Save"));

    QList<QAction*> it = m_fileMenu->actions();
}

void MainWindow::createDrawMenu()
{
    QMenu *edit = new QMenu;
    edit->addAction("");
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
    if(gaction) {
        m_editor->setCurrentItem(gaction->getObject());
    }
}

void MainWindow::styleActionClicked(QAction* action)
{
    GStyleAction* styleAction = dynamic_cast<GStyleAction*>(action);
    if(styleAction) {
        styleAction->execute(m_editor);
    }
}

void MainWindow::createCommandLineDockW()
{
    m_commandLine = new CommandLineGui(this);
    m_commandLine->setFixedHeight(100);
    addDockWidget(Qt::BottomDockWidgetArea, m_commandLine);
}

void MainWindow::createActionToolBar()
{
    m_actionToolBar = new QToolBar(this);

    m_getShortPath = new QAction("get Shortest Path");
    m_getShortPath->setIcon(QIcon(":/Icons/shortPath.png"));
    m_actionToolBar->addAction(m_getShortPath);

    QAction* clearEitor = new QAction("Delete All Shapes");
    clearEitor->setIcon(QIcon(":/Icons/clear.png"));
    m_actionToolBar->addAction(clearEitor);

    assert(connect(clearEitor, SIGNAL(triggered(bool)), m_editor, SLOT(clearAll())));

    addToolBar(Qt::LeftToolBarArea, m_actionToolBar);
    connect(m_getShortPath, SIGNAL(triggered(bool)), this, SLOT(handleshortedPathAction()));
}

void MainWindow::handleshortedPathAction()
{
    qDebug()<<"handleshortedPathAction";

    if(m_engine && m_editor) {
        QList<GGraphicsItem*> items = m_editor->getSelectedItems();
        if(items.empty())
            return;
        std::vector<std::string> rects = m_engine->findPath<Rectangle>("Shape_0", items[0]->name());
        QList<QString> pathNames;
        for(const std::string& it : rects) {
            pathNames.push_back(QString::fromStdString(it));
        }

        m_editor->selectItems(pathNames);
    }


}

void MainWindow::openClicked()
{
    qDebug()<<"open Clicked";
}


void MainWindow::createWeigthPriorityMenu()
{
    QMenu* pathSolution = menuBar()->addMenu("Path");
    QAction* weightPriority = new QAction("Weight Priority");
    assert(connect(weightPriority, SIGNAL(triggered(bool)), this, SLOT(selectWeightPriority())));

    pathSolution->addAction(weightPriority);
}

void MainWindow::selectWeightPriority()
{
    SelectEdgeWeight* weightPriority = new SelectEdgeWeight(this);
    auto returnCode = weightPriority->exec();
    if (returnCode == QDialog::Accepted) {
         m_engine->setWeightPriority(weightPriority->getSelectedType());
    } else {
        m_engine->setWeightPriority(weightPriority->getDefault());
    }
}












