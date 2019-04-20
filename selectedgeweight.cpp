#include "selectedgeweight.h"

#include <QHBoxLayout>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include "engine.h"

SelectEdgeWeight::SelectEdgeWeight(QWidget* parent):QDialog(parent)
{
    QHBoxLayout* HBLayout1 = new QHBoxLayout;
    QHBoxLayout* HBLayout2 = new QHBoxLayout;
    QVBoxLayout* VBoxLayout = new QVBoxLayout;

    m_selectType = new QComboBox();
    m_selectType->addItem("Square of Overlap", QVariant(static_cast<int>(GraphWeightPriority::OverLapSquare)));
    m_selectType->addItem("Marge Square", QVariant(static_cast<int>(GraphWeightPriority::MargeSauare)));
    QPushButton* okButton = new QPushButton("Ok",this);
    QPushButton* cancelButton = new QPushButton("Cancel", this);
    assert(connect(okButton, SIGNAL(clicked(bool)), this, SLOT(accept())));
    assert(connect(cancelButton, SIGNAL(clicked(bool)), this, SLOT(reject())));
    HBLayout2->addWidget(cancelButton);
    HBLayout2->addWidget(okButton);

    QLabel* name = new QLabel("Select Weight Priority");
    HBLayout1->addWidget(name);
    HBLayout1->addWidget(m_selectType);
    VBoxLayout->addItem(HBLayout1);
    VBoxLayout->addItem(HBLayout2);
    setLayout(VBoxLayout);
    setModal(true);
}

SelectEdgeWeight::GraphWeightPriority SelectEdgeWeight::getSelectedType() const
{
    if(m_selectType) {
        QVariant value = m_selectType->currentData();
        return static_cast<SelectEdgeWeight::GraphWeightPriority>(value.toInt());
    }
    return GraphWeightPriority::OverLapSquare;
}
