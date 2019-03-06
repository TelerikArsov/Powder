#include "CircleBrush.h"

#define Radius 0

void CircleBrush::change_size(int d)
{
	if (d > 0)
	{
		sizes[Radius]++;
		create_area();
	}
	else if (d < 0)
	{
		sizes[Radius] > 0 ? sizes[Radius]-- : 0;
		create_area();
	}
}

void CircleBrush::create_area()
{
	spawn_area.clear();
	spawn_outline.clear();
	int x = 0;
	int y = sizes[Radius];
	int dx = 0;
	int dy = -2 * sizes[Radius];
	int i = y;
	int err = 1 - sizes[Radius];
	sizes[Radius] > 0 
		? four_fold_push(x, y, spawn_outline) 
		: spawn_outline.push_back(std::make_pair(0, 0));
	for (i = y; i > 0; i--)
	{
		four_fold_push(0, i, spawn_area);
	}
	while (x < y)
	{
		x++;
		if (err >= 0)
		{
			y--;
			err += 2 * (x - y) + 1;
		}
		else 
		{
			err += 2 * x + 1;
		}
		if (x < y)
		{
			eight_fold_push(x, y, spawn_outline);
			eight_fold_push(x, y, spawn_area);
		}
		else if (x == y)
		{
			sym_x_equal_y(x, y, spawn_outline);
			sym_x_equal_y(x, y, spawn_area);
		}
		// The insides of the circle is filled
		for (i = y - 1; i > x; i--) {
			eight_fold_push(x, i, spawn_area);
		}
		// The diagonals
		if (i == x)
		{
			sym_x_equal_y(x, i, spawn_area);
		}
	}
	spawn_area.push_back(std::make_pair(0, 0));

}

CircleBrush::CircleBrush()
{
	name = "Circle";
	description = "Brush in the shape of a circle";
	//circle has only one size radius
	sizes.push_back(0);
	create_area();
}


CircleBrush::~CircleBrush()
{
}
