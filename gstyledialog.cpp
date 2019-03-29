#include "gstyledialog.h"
#include <QSpinBox>
#include <QComboBox>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QPushButton>

GPenStyleDialog::GPenStyleDialog(QWidget* parent, Qt::WindowFlags flag) :QDialog (parent, flag)
{
    setWindowTitle("Pen Style");
    m_widthSB = new QSpinBox(this);
    m_penStyle = new QComboBox(this);
    m_ok = new QPushButton("Ok", this);
    connect(m_ok, SIGNAL(pressed()), this, SLOT(accept()));
    m_cancel = new QPushButton("Cancel", this);
    connect(m_cancel, SIGNAL(pressed()), this, SLOT(hide()));

    QFormLayout* widthFLay = new QFormLayout;
    widthFLay->addRow(new QLabel("Width", this), m_widthSB);
    widthFLay->setSpacing(1);
    widthFLay->addRow(new QLabel("Pen Style", this), m_penStyle);
    widthFLay->setSpacing(15);

    m_penStyle->addItem(QIcon(), "Solid Line", QVariant(static_cast<int>(Qt::SolidLine)));
    m_penStyle->addItem(QIcon(), "Dash Line", QVariant(static_cast<int>(Qt::DashLine)));
    m_penStyle->addItem(QIcon(), "Dot Line", QVariant(static_cast<int>(Qt::DotLine)));
    m_penStyle->addItem(QIcon(), "Dash Dot Line", QVariant(static_cast<int>(Qt::DashDotLine)));
    m_penStyle->addItem(QIcon(), "Dash Dot Dot Line", QVariant(static_cast<int>(Qt::DashDotDotLine)));

    QGridLayout* gridLay = new QGridLayout;
    gridLay->addItem(widthFLay,0,0,4,5);
    gridLay->addWidget(m_cancel,4,3);
    gridLay->addWidget(m_ok,4,4);

    setLayout(gridLay);
}

Qt::PenStyle GPenStyleDialog::getStyle() const
{
    return static_cast<Qt::PenStyle>(m_penStyle->currentData().toInt());
}

int GPenStyleDialog::getWidth() const
{
    return m_widthSB->value();
}
