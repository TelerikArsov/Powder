#pragma once
#include "Brush.h"
class SquareBrush :
	public Brush
{
public:
	void change_size(int direction) override;
	// Create the square spawn area
	void create_area() override;
	SquareBrush();
	~SquareBrush();
private:
	enum Sizes {
		Side
	};
};

