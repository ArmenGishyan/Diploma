#ifndef DOCKWIDGETS_H
#define DOCKWIDGETS_H

#include <QWidget>
#include <QDockWidget>

class CommandLineGui : public QDockWidget
{
public:
    CommandLineGui(QWidget* parent = nullptr);
};

#endif // DOCKWIDGETS_H
