#include "SquareBrush.h"

#define Side 0

void SquareBrush::change_size(int d)
{
	if (d > 0)
	{
		sizes[Side] += 2;
		create_area();
	}
	else if (d < 0)
	{
		sizes[Side] > 0 ? sizes[Side] -= 2 : 0;
		create_area();
	}
}

void SquareBrush::create_area()
{
	spawn_area.clear();
	spawn_outline.clear();
	int h_s = sizes[Side] / 2;
	sizes[Side] > 0 
		? four_fold_push(0, h_s, spawn_outline) 
		: spawn_outline.push_back(std::make_pair(0, 0));
	for (int i = h_s; i > 0; i--)
	{
		four_fold_push(0, i, spawn_area);
	}
	for (int i = 1; i <= h_s; i++)
	{
		for (int j = h_s; j > 0; j--)
		{
			if (i == h_s)
			{
				sym_x_equal_y(i, j, spawn_outline);
			}
			else if (j == h_s) 
			{
				sym_x_equal_y(i, j, spawn_outline);
			}
			sym_x_equal_y(i, j, spawn_area);
		}
	}
	spawn_area.push_back(std::make_pair(0, 0));
}

SquareBrush::SquareBrush()
{
	name = "Square";
	description = "Squared";
	sizes.push_back(0);
	create_area();
}


SquareBrush::~SquareBrush()
{
}
