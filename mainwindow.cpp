#include "mainwindow.h"
#include <QMenuBar>
#include <QToolBar>
#include <QMenu>
#include <QDebug>
#include <QIcon>
#include <QToolButton>
#include <QDesktopWidget>
#include <QRgb>
#include "editor.h"
#include "dockwidgets.h"
#include "engine.h"
#include <assert.h>
#include <QApplication>
#include <guierrors.h>
#include <QMessageBox>
#include <QDir>
#include <QFileDialog>
#include "parsetext.h"
#include "selectdestinitions.h"
#include "ggraphicsstyle.h"

#include "readshapesfromfile.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)/*, ui(new Ui::MainWindow)*/
{
   // ui->setupUi(this);
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
    m_menuBar->deleteLater();
   // delete ui;
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

    QAction* circleAction = new QAction(m_mainToolBar);
    circleAction->setIcon(QIcon(":/Icons/circle.png"));
    circleAction->setText("Draw Circle");

    QAction* squareAction = new QAction(m_mainToolBar);
    squareAction->setIcon(QIcon(":/Icons/square.png"));
    squareAction->setText("Draw Square");

    GNoneShapeAction* noneShape = new GNoneShapeAction(this);
    noneShape->setIcon(QIcon(":/Icons/noShape.png"));
    noneShape->setText("None Shape");
    m_mainToolBar->addAction(m_drawLine);
    m_mainToolBar->addAction(m_drawRect);
    m_mainToolBar->addAction(m_drawPoint);
    m_mainToolBar->addAction(circleAction);
    m_mainToolBar->addAction(squareAction);
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
    //m_fileMenu = menuBar()->addMenu("File");
    //m_fileMenu->addAction(new QAction("New"));
    //QAction* openAction = new QAction("Open");
    //m_fileMenu->addAction(openAction);
    //QAction* saveAction = new QAction("Save");
    //m_fileMenu->addAction(saveAction);
    //m_fileMenu->addAction(new QAction("Save As"));
    //assert(connect(openAction, SIGNAL(triggered(bool)), this, SLOT(openClicked())));
    //assert(connect(saveAction, SIGNAL(triggered(bool)), this, SLOT(saveClicked())));


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
    m_styleToolBar->addAction(lineColor);

    GPenStyle* penStyle = new GPenStyle;
    penStyle->setText("Pen Style");
    penStyle->setIcon(QIcon(":/Icons/penStyle.png"));
    m_styleToolBar->addAction(penStyle);

    GBrushColor* brushColor = new GBrushColor;
    m_styleToolBar->addAction(brushColor);

    addToolBar(Qt::LeftToolBarArea, m_styleToolBar);
}
void MainWindow::initEditor()
{
    m_editor = new Editor(this);
}

void MainWindow::actionClicked(QAction* action)
{
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

    QAction* clearSelected = new QAction("Delete Selected Items");
    clearSelected->setIcon(QIcon(":/Icons/clearSelected.png"));
    m_actionToolBar->addAction(clearSelected);

    QAction* selectTwoItem = new QAction("Chose Two Destinations");
    selectTwoItem->setIcon(QIcon(":/Icons/selectTwoItem.png"));
    m_actionToolBar->addAction(selectTwoItem);
    assert(connect(clearEitor, SIGNAL(triggered(bool)), m_editor, SLOT(clearAll())));
    assert(connect(clearSelected, SIGNAL(triggered(bool)), m_editor, SLOT(clearSelectedItems())));
    assert(connect(selectTwoItem, SIGNAL(triggered(bool)), this, SLOT(twoDestinition())));

    addToolBar(Qt::LeftToolBarArea, m_actionToolBar);
    connect(m_getShortPath, SIGNAL(triggered(bool)), this, SLOT(handleshortedPathAction()));
}

void MainWindow::handleshortedPathAction()
{
    if(m_engine && m_editor) {
        QList<GGraphicsItem*> items = m_editor->getSelectedItems();
        if(!(items.size() == 2)) {
            WrongSelectionCount error(GuiMessageWirter::Priority::ERROR, "Please Select 2 shape before click on the button");
            error.execute();
            return;
        }
        std::vector<std::string> rects = m_engine->findPath<Rectangle>(items[0]->name(), items[1]->name());
        QList<QString> pathNames;
        for(const std::string& it : rects) {
            pathNames.push_back(QString::fromStdString(it));
        }

        m_editor->selectItems(pathNames);
    }


}

void MainWindow::openClicked()
{
    //assert(false);
    QDir filePath(QCoreApplication::applicationDirPath());
    QString path = QFileDialog::getOpenFileName(nullptr, tr("Open"), filePath.path());
    ReadWriteFile file(path.toStdString(), std::ios::in);
    std::vector<std::string> lines = file.getLinesFromFile();
    if(m_editor) {
        ParseText text(lines);
        auto shp = text.parseShapes();
        m_editor->addShapes(shp);
        m_editor->update();
    }
}

void MainWindow::saveClicked()
{
    QDir filePath(QCoreApplication::applicationDirPath());
    QString path = QFileDialog::getSaveFileName(nullptr, tr("Save"), filePath.path());
    ReadWriteFile file(path.toStdString(), std::ios::in);
    std::vector<std::string> lines = file.getLinesFromFile();
    if(m_editor) {
        ParseText text(lines);
        auto shp = text.parseShapes();
        m_editor->addShapes(shp);
        m_editor->update();
    }

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

void MainWindow::setCurrentMessage(GuiMessageWirter *message)
{
    delete m_currentMessage;
    m_currentMessage = message;
}

void MainWindow::executeCurrentMessage()
{
    if(m_currentMessage) {
        m_currentMessage->execute();
    }
}

void MainWindow::twoDestinition()
{
   if(m_editor) {
       m_editor->toDefaultState();
   }
   SelectDestinitions* dest = new SelectDestinitions;
   dest->setModal(true);
   if(dest->exec() == QDialog::Accepted) {
      QList<QString> values = dest->getDestinitions();
      if(m_engine && values.size() > 1) {
         const std::string startName = values[0].toStdString();
         const std::string endName = values[1].toStdString();
         std::vector<std::string> rects = m_engine->findPath<Rectangle>(startName, endName);
         QList<QString> pathNames;
             for(const std::string& it : rects) {
             pathNames.push_back(QString::fromStdString(it));
         }
         QList<QString> startEnd;
         startEnd << values[0] << values[1];
         std::shared_ptr<GGraphicsStyle> style = std::make_shared<GGraphicsStyle>();
         style->setBrush(QColor(48, 209, 70));
         m_editor->selectItems(pathNames);
         m_editor->selectItems(startEnd, style);
      }
   }
}

TooManySelection::TooManySelection(int count, GuiMessageWirter::Priority priority, std::string message):GuiMessageWirter (priority,message)
{
    m_selectionCount = count;
}

bool TooManySelection::execute()
{
    QMessageBox error;
    error.setText(QString::fromStdString(m_errorMassage));
    error.setIcon(QMessageBox::Critical);
    error.setWindowTitle("Too Many Selection");
    error.addButton(QMessageBox::Ok);

    return true;
}







