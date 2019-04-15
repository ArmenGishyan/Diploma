#ifndef GGRAPHICSSTYLE_H
#define GGRAPHICSSTYLE_H

#include <QPen>
#include <QBrush>

class GGraphicsStyle
{
public:
    GGraphicsStyle(QPen pen = QPen(), QBrush brush = QBrush());
    QPen pen(){return  m_pen;}
    QBrush brush(){return m_brush;}
    void setPen(QPen pen) { m_pen = pen;}
    void setBrush(QBrush brush){ m_brush = brush;}


private:
    QPen m_pen;
    QBrush m_brush;
};

#endif // GGRAPHICSSTYLE_H
