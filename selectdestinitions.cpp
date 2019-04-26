#include "selectdestinitions.h"
#include <QFormLayout>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <assert.h>

SelectDestinitions::SelectDestinitions()
{
     QGridLayout* grLay = new QGridLayout;
     QFormLayout* formLay = new QFormLayout;
     m_startDest = new QLineEdit(this);
     m_endDest = new QLineEdit(this);
     formLay->addRow(new QLabel("Start Shape "), m_startDest);
     formLay->addRow(new QLabel("End Shape "), m_endDest);
     formLay->setSpacing(10);
     QPushButton* findPath = new QPushButton("Find Path", this);
     QPushButton* cancel = new QPushButton("Cancel", this);
     grLay->addItem(formLay,0, 0, 5, 10);
     grLay->addWidget(cancel, 5, 0, 1, 5);
     grLay->addWidget(findPath,5,5,1,10);
     setLayout(grLay);
     assert(connect(cancel, SIGNAL(clicked(bool)), this, SLOT(reject())));
     assert(connect(findPath, SIGNAL(clicked(bool)), this, SLOT(accept())));
}

QList<QString> SelectDestinitions::getDestinitions() const
{
     QList<QString> valueList;
     valueList.push_back(m_startDest->text());
     valueList.push_back(m_endDest->text());
     return valueList;
}
