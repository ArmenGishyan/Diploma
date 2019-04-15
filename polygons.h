#pragma once
#include <functional>
#include <QRectF>

using T = int;


class IShape
{
public:
    IShape(){}
    virtual T square() const = 0;
    void setName(std::string name)
    {
        m_name = name;
    }
    std::string name() const
    {
        return m_name;
    }

private:
    std::string m_name;
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
    Polygon(): IShape() { setName("");}
    virtual ~Polygon() {}
    virtual T squareOfOverlap(const Polygon* pol) const;
    virtual bool isIntersect(const Polygon* pol) const;

};

class Rectangle : public Polygon
{
public:
    Rectangle(Point leftTop, Point bottomRight);
    ~Rectangle() override {}
	T square() const override;
    T squareOfOverlap(const Polygon* pol) const override;
    QRectF squareOfOverlapTest(const Polygon* pol) const;
    bool isIntersect(const Polygon* pol) const override ;
    Point leftTop() const;
    Point rightBottom() const;

private:
    Point  m_leftTop;
    Point  m_rightBottom;
};
