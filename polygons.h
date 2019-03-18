#pragma once
#include <functional>

#include "shape.h"



class Point;

class Polygon : public IShape
{
public:
	virtual T squareOfOverlap(Polygon* pol) const;
	virtual bool isIntersect(Polygon* pol) const;

};

class Rectangle : public Polygon
{
public:
	T square() const override;
	T squareOfOverlap(Polygon* pol) const override;
	bool isIntersect(Polygon* pol) const override ;
	Point* getLeftTopPoint() const;
	Point* getRightBottomPoint() const;

private:
	Point * m_leftTop;
	Point * m_rightBottom;
};