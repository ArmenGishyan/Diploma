#include "dockwidgets.h"
#include <QLineEdit>
#include <QSizePolicy>
#include <QLabel>
#include <QVBoxLayout>

CommandLineGui::CommandLineGui(QWidget* parent):QDockWidget (parent)
{
    setStyleSheet("background-color:#5F9EA0");

    setFixedHeight(150);
    setWindowTitle("Command Line");
    QLabel* label = new QLabel("fvnfdnvkdnfvdkvkdn", this);
    QHBoxLayout* lay = new QHBoxLayout;
    lay->addWidget(label);
    m_lineEdit = new QLineEdit(this);
    lay->addWidget(m_lineEdit);
    m_lineEdit->setMinimumWidth(300);
    m_lineEdit->setBackgroundRole(QPalette::Window);
    setLayout(lay);
}
