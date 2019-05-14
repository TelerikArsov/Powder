#pragma once
#include <vector>
#include <string>
#include "SimObject.h"

class Brush :
	public SimObject
{
	using points = std::pair<int, int>;
public:
	virtual void change_size(int direction) = 0;
	virtual void create_area() = 0;
	std::vector<points> get_area() const
	{
		return spawn_area;
	}
	std::vector<points> get_outline() const
	{
		return spawn_outline;
	}
	~Brush();
protected:
	//used to determine sizes of the area of the brush
	std::vector<int> sizes;
	// spawn arrea consists of offests and not grid cordinates
	// the offsets are used against the position of the mouse
	// E.G (1, -1)
	std::vector<points> spawn_area;
	// The outline of the spawn area
	// Used mainly in the rendering
	std::vector<points> spawn_outline;
	// Used in the spawn area creation
	void eight_fold_push(int x, int y, std::vector<points> &container);
	void four_fold_push(int x, int y, std::vector<points> &c);
	void sym_x_equal_y(int x, int y, std::vector<points> &c);
};

