#include "ggraphicsstyle.h"
#include <QDebug>

GGraphicsStyle::GGraphicsStyle(QPen pen, QBrush brush)
{
    m_pen = pen;
    m_brush = brush;

}

GGraphicsStyle::~GGraphicsStyle()
{
    qDebug()<<"GGraphicsStyle::~GGraphicsStyle";
}
