#include "Brushes/Brush.h"


void Brush::eight_fold_push(int x, int y, std::vector<points> &c)
{
	c.push_back(std::make_pair(x, y));
	c.push_back(std::make_pair(-x, y));
	c.push_back(std::make_pair(x, -y));
	c.push_back(std::make_pair(-x, -y));
	c.push_back(std::make_pair(y, x));
	c.push_back(std::make_pair(-y, x));
	c.push_back(std::make_pair(y, -x));
	c.push_back(std::make_pair(-y, -x));
}

void Brush::four_fold_push(int x, int y, std::vector<points> &c)
{
	c.push_back(std::make_pair(x, y));
	c.push_back(std::make_pair(x, -y));
	c.push_back(std::make_pair(y, x));
	c.push_back(std::make_pair(-y, x));
}

void Brush::sym_x_equal_y(int x, int y, std::vector<points> &c)
{
	c.push_back(std::make_pair(x, y));
	c.push_back(std::make_pair(x, -y));
	c.push_back(std::make_pair(-x, -y));
	c.push_back(std::make_pair(-x, y));
}


Brush::~Brush()
{
}
