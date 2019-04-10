#pragma once
#include <functional>

#include "shape.h"
#include "point.h"

using T = int;


class IShape
{
public:
    IShape(){}
    virtual T square() const = 0;
};


class Point : public IShape
{
public:
    Point(int x, int y);
    int square() const override;
    int getX() const;
    int getY() const;

private:
    int x_coor;
    int y_coor;
};

class Polygon : public IShape
{
public:
    Polygon(): IShape() {}
    virtual ~Polygon() {}
	virtual T squareOfOverlap(Polygon* pol) const;
	virtual bool isIntersect(Polygon* pol) const;

};

class Rectangle : public Polygon
{
public:
    Rectangle(Point leftTop, Point bottomRight);
    ~Rectangle() override {}
	T square() const override;
	T squareOfOverlap(Polygon* pol) const override;
	bool isIntersect(Polygon* pol) const override ;
    Point getLeftTopPoint() const;
    Point getRightBottomPoint() const;

private:
    Point  m_leftTop;
    Point  m_rightBottom;
};
