#ifndef GSTYLEDIALOG_H
#define GSTYLEDIALOG_H

#include <QDialog>
#include <QMap>

class QSpinBox;
class QComboBox;

class GPenStyleDialog : public QDialog
{
    Q_OBJECT

public:
    GPenStyleDialog(QWidget* parent = nullptr, Qt::WindowFlags flag = Qt::Dialog);

public:
    int getWidth() const;
    Qt::PenStyle getStyle() const;

private:
    QPushButton* m_ok;
    QPushButton* m_cancel;
    QSpinBox* m_widthSB;
    QComboBox* m_penStyle;
};

#endif // GSTYLEDIALOG_H
