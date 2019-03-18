#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void createToolBar();
    void createMenuBar();

private:
    QToolBar* m_mainToolBar;
    QMenuBar* m_menuBar;
};

#endif // MAINWINDOW_H
