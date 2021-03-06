#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gaction.h"

class GuiMessageWirter;
class QToolButton;
class Editor;
class CommandLineGui;
class Engine;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

// public methods
    const Editor* getEditor() const {return m_editor;}
    void initEngine(Engine* engine) {m_engine = engine;}
    void setCurrentMessage(GuiMessageWirter* message);
    void executeCurrentMessage();


private:
    void createToolBar();
    void createMenuBar();
    void createFileMenu();
    void createDrawMenu();
    void createHelpMenu();
    void createStyleToolBar();
    void createCommandLineDockW();
    void createActionToolBar();
    void initEditor();
    void createWeigthPriorityMenu();


private slots:
    void actionClicked(QAction*);
    void styleActionClicked(QAction*);
    void handleshortedPathAction();
    void openClicked();
    void saveClicked();
    void selectWeightPriority();
    void twoDestinition();

  //  void handleDrawRect();
  //  void handleDrawLine();
  //  void handleDrawPoint();

private:
    //Ui::MainWindow *ui;
    QToolBar* m_mainToolBar;
    QToolBar* m_styleToolBar;
    QToolBar* m_actionToolBar;
    QMenuBar* m_menuBar;
    QMenu* m_fileMenu;
    QMenu* m_drawMenu;
    QMenu* m_helpMenu;
    GAction* m_drawRect;
    QAction* m_drawLine;
    QAction* m_drawPoint;
    QAction* m_fillSelection;
    QAction* m_selectColor;
    QAction* m_getShortPath;
    Editor* m_editor;
    CommandLineGui* m_commandLine;
    Engine* m_engine;
    GuiMessageWirter* m_currentMessage;

};

#endif // MAINWINDOW_H
