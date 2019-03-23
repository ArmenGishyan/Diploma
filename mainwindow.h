#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private:
    Ui::MainWindow *ui;
    QToolBar* m_mainToolBar;
    QMenuBar* m_menuBar;
    QMenu* m_fileMenu;
    QMenu* m_drawMenu;
    QMenu* m_helpMenu;
    QToolButton* m_drawRect;
    QToolButton* m_drawLine;
    QToolButton* m_drawPoint;
    QToolButton* m_fillSelection;
    QToolButton* m_selectColor;
    Editor* m_editor;


};

#endif // MAINWINDOW_H
