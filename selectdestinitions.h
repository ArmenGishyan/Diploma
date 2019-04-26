#ifndef SELECTDESTINITIONS_H
#define SELECTDESTINITIONS_H

#include <QDialog>

class QLineEdit;

class SelectDestinitions : public QDialog
{
public:
    SelectDestinitions();
    QList<QString> getDestinitions() const;

private:
    QLineEdit* m_startDest;
    QLineEdit* m_endDest;
};

#endif // SELECTDESTINITIONS_H
