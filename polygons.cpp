#include <cmath>
#include <iostream>
#include <string>
#include <cassert>
#include "polygons.h"
#include "point.h"

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

T Polygon::squareOfOverlap(Polygon* pol) const
{
    assert(false && "don't complete");
	return 0;
}

bool Polygon::isIntersect(Polygon* pol) const
{
    assert(false && "don't complete");
	return 0;
}

bool Rectangle::isIntersect(Polygon* pol) const
{
    assert(false && "don't complete");
	return true;
}

T Rectangle::squareOfOverlap(Polygon* pol) const
{
	Rectangle* rect = dynamic_cast<Rectangle*>(pol);
	if (rect) {
		Point* topLeft = rect->getLeftTopPoint();
		Point* rightBottom = rect->getRightBottomPoint();
		auto max = [](T a, T b) {return a > b; };
		auto min = [](T a, T b) {return a < b; };

		T maxX = Helpers::maxOrMin<T>(m_leftTop->getX(), m_rightBottom->getX(),
			topLeft->getX(), rightBottom->getX(), max);
		T minX = Helpers::maxOrMin<T>(m_leftTop->getX(), m_rightBottom->getX(), 
			topLeft->getX(), rightBottom->getX(), min);

		T maxY = Helpers::maxOrMin<T>(m_leftTop->getY(), m_rightBottom->getY(),
			topLeft->getY(), rightBottom->getY(), max);
		T minY = Helpers::maxOrMin<T>(m_leftTop->getY(), m_rightBottom->getY(),
			topLeft->getY(), rightBottom->getY(), min);

		T xSize = abs(m_rightBottom->getX() - m_leftTop->getX()) + abs(rightBottom->getX() - topLeft->getX());
		T ySize = abs(m_rightBottom->getY() - m_leftTop->getY()) + abs(rightBottom->getY() - topLeft->getY());

		return xSize * ySize;
	}
	return -1;
}

Point* Rectangle::getLeftTopPoint() const
{
	return m_leftTop;
}

Point* Rectangle::getRightBottomPoint() const
{
	return m_rightBottom;
}
