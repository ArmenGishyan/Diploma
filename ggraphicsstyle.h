#ifndef GGRAPHICSSTYLE_H
#define GGRAPHICSSTYLE_H

#include <QPen>
#include <QBrush>
#include <memory>

class GGraphicsStyle
{
public:
    GGraphicsStyle(QPen pen = QPen(QColor(Qt::red)), QBrush brush = QBrush(QColor(0,85,0)));
    ~GGraphicsStyle();
    QPen pen(){return  m_pen;}
    QBrush brush(){return m_brush;}
    void setPen(QPen pen) { m_pen = pen;}
    void setBrush(QBrush brush){ m_brush = brush;}


private:
    QPen m_pen;
    QBrush m_brush;
};

class GuiBaseStyle
{
public:


private:
    static std::unique_ptr<GGraphicsStyle> m_defaultStyle;
};
#endif // GGRAPHICSSTYLE_H
