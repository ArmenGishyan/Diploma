#include "guierrors.h"
#include <QMessageBox>
#include <QString>

GuiMessageWirter::GuiMessageWirter(GuiMessageWirter::Priority priority,
                     std::string errorMassage)
{
    m_errorMassage = errorMassage;
    m_priority = priority;
}

WrongSelectionCount::WrongSelectionCount(GuiMessageWirter::Priority priority,
                     std::string errorMassage):GuiMessageWirter (priority,errorMassage)
{
}

bool WrongSelectionCount::execute()
{
    QMessageBox mb;
    mb.setWindowTitle("Wrong Selection Count");
    mb.setText(QString::fromStdString(m_errorMassage));
    mb.setIcon(QMessageBox::Critical);
    mb.addButton(QMessageBox::Ok);
    if(mb.exec() == QDialog::Accepted) {
        return true;
    }
    return false;
}
