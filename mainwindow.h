#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gaction.h"

namespace Ui {
class MainWindow;
}

class QToolButton;
class Editor;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void createToolBar();
    void createMenuBar();
    void createFileMenu();
    void createDrawMenu();
    void createHelpMenu();
    void initEditor();

public slots:
    void actionClicked(QAction*);
  //  void handleDrawRect();
  //  void handleDrawLine();
  //  void handleDrawPoint();

private:
    Ui::MainWindow *ui;
    QToolBar* m_mainToolBar;
    QMenuBar* m_menuBar;
    QMenu* m_fileMenu;
    QMenu* m_drawMenu;
    QMenu* m_helpMenu;
    GAction* m_drawRect;
    QAction* m_drawLine;
    QAction* m_drawPoint;
    QAction* m_fillSelection;
    QAction* m_selectColor;
    Editor* m_editor;


};

#endif // MAINWINDOW_H
