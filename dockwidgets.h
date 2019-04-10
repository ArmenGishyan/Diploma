#ifndef DOCKWIDGETS_H
#define DOCKWIDGETS_H

#include <QWidget>
#include <QDockWidget>

class QLineEdit;

class CommandLineGui : public QDockWidget
{
public:
    CommandLineGui(QWidget* parent = nullptr);

private:
    QLineEdit* m_lineEdit;
};

#endif // DOCKWIDGETS_H
