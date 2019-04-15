#include <cmath>
#include <iostream>
#include <string>
#include <cassert>
#include "polygons.h"

namespace Helpers{
	template<class T>
	T maxOrMin(T a, T b, T c, T d, std::function<bool(T, T)> obj)
	{
		T maxOrMin1;
		T maxOrMin2;

		if (obj(a, b)) {
			maxOrMin1 = a;
		}
		else
			maxOrMin1 = b;

		if (obj(c, d)) {
			maxOrMin2 = c;
		}
		else
			maxOrMin2 = d;

		return obj(maxOrMin1, maxOrMin2) ? maxOrMin1 : maxOrMin2;
	}
}

T Polygon::squareOfOverlap(const Polygon* pol) const
{
    assert(false && "don't complete");
	return 0;
}

bool Polygon::isIntersect(const Polygon* pol) const
{
    assert(false && "don't complete");
	return 0;
}

Rectangle::Rectangle(Point leftTop, Point bottomRight): Polygon (), m_leftTop(leftTop), m_rightBottom(bottomRight)
{}
bool Rectangle::isIntersect(const Polygon* pol) const
{
    assert(false && "don't complete");
	return true;
}

T Rectangle::square() const
{
    return std::abs(m_leftTop.getX()-m_rightBottom.getX()) * std::abs(m_leftTop.getY()- m_rightBottom.getY());
}
T Rectangle::squareOfOverlap(const Polygon* pol) const
{
    const Rectangle* rect = dynamic_cast<const Rectangle*>(pol);
	if (rect) {
        Point topLeft = rect->leftTop();
        Point rightBottom = rect->rightBottom();
		auto max = [](T a, T b) {return a > b; };
		auto min = [](T a, T b) {return a < b; };

        T maxX = Helpers::maxOrMin<T>(m_leftTop.getX(), m_rightBottom.getX(),
            topLeft.getX(), rightBottom.getX(), max);
        T minX = Helpers::maxOrMin<T>(m_leftTop.getX(), m_rightBottom.getX(),
            topLeft.getX(), rightBottom.getX(), min);

        T maxY = Helpers::maxOrMin<T>(m_leftTop.getY(), m_rightBottom.getY(),
            topLeft.getY(), rightBottom.getY(), max);
        T minY = Helpers::maxOrMin<T>(m_leftTop.getY(), m_rightBottom.getY(),
            topLeft.getY(), rightBottom.getY(), min);

        T xSize = abs(m_rightBottom.getX() - m_leftTop.getX()) + abs(rightBottom.getX() - topLeft.getX());
        T ySize = abs(m_rightBottom.getY() - m_leftTop.getY()) + abs(rightBottom.getY() - topLeft.getY());

		return xSize * ySize;
	}
	return -1;
}

QRectF Rectangle::squareOfOverlapTest(const Polygon* pol) const
{
    const Rectangle* rect = dynamic_cast<const Rectangle*>(pol);
    if (rect) {
        QPoint topLeftThis(m_leftTop.getX(),m_leftTop.getY());
        QPoint bottomRightThis(m_rightBottom.getX(), m_rightBottom.getY());
        QPoint topLeftOther(rect->leftTop().getX(), rect->leftTop().getY());
        QPoint bottomRightOther(rect->rightBottom().getX(), rect->rightBottom().getY());

        QRectF  rectThis(topLeftThis, bottomRightThis);
        QRectF  rectOther(topLeftOther, bottomRightOther);

        return rectThis.intersected(rectOther);
    }

    return QRectF();
}

Point Rectangle::leftTop() const
{
	return m_leftTop;
}

Point Rectangle::rightBottom() const
{
	return m_rightBottom;
}



Point::Point(int x, int y): x_coor(x), y_coor(y)
{}

T Point::square() const
{
    return 0;
}

int Point::getX() const
{
    return x_coor;
}

int Point::getY() const
{
    return y_coor;
}
