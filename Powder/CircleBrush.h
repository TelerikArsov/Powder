#pragma once
#include "Brush.h"
class CircleBrush :
	public Brush
{
public:
	void change_size(int direction) override;
	// Create the circle spawn area
	// Bresenhams circle algorithm is used for the creation of the outline of the circle
	void create_area() override;
	CircleBrush();
	~CircleBrush();
private:
	enum Sizes {
		Radius
	};
};

