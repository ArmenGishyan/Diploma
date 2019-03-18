#pragma once

#include "shape.h"

class Point : public IShape
{
public:
	T square() const override;
	int getX() const;
	int getY() const;

private:
	int x_coor;
	int y_coor;
};

