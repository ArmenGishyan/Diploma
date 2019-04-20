#ifndef SELECTEDGEWEIGHT_H
#define SELECTEDGEWEIGHT_H
#include <QDialog>

class QComboBox;

class SelectEdgeWeight : public QDialog
{
public:
    SelectEdgeWeight(QWidget* parent = nullptr);
    // chose what should be weight of Graph edges
    enum class GraphWeightPriority
    {
        OverLapSquare,
        MargeSauare
    };

    SelectEdgeWeight();
    GraphWeightPriority getSelectedType() const;
    GraphWeightPriority getDefault() const {return GraphWeightPriority::OverLapSquare;}

private:
    QComboBox* m_selectType;
};

#endif // SELECTEDGEWEIGHT_H
