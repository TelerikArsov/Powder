#include "Element.h"
#include "Simulation.h"
//TODO implement an element to test this function properly
bool Element::move(int xD, int yD)
{
	bool status = true;
	if (x == xD && y == yD)
		return status;
	int xstep, ystep;
	int xO = x, yO = y;
	int dx = xD - xO;
	int dy = yD - yO;
	int e, eprev;
	if (dy < 0)
	{
		ystep = -1;
		dy = -dy;
	}
	else
	{
		ystep = 1;
	}
	if (dx < 0)
	{
		xstep = -1;
		dx = -dx;
	}
	int ddx = 2 * dx; // double for more precision
	int ddy = 2 * dy;
	// we check if the slope is in the 1st 4th 5th and 8th octant
	if (ddx >= ddy) 
	{  
		eprev = dx;
		e = dx;
		for (int i = 0; i < dx; i++) 
		{
			xO += xstep;
			e += ddy;
			if (e > ddx) 
			{
				yO += ystep;
				e -= ddx;
				if (e + eprev < ddx)  // bottom square also
				{
					// if there is no collision we update the elements real coordinates
					if (sim->elements_grid[xO][yO - ystep]->identifier == -1)
					{
						status = false;
						break;
					}
					else 
					{
						x = xO;
						y = yO - ystep;
					}
				}
				else if (e + eprev > ddx) // left corner
				{
					if (sim->elements_grid[xO - xstep][yO]->identifier == -1)
					{
						status = false;
						break;
					}
					else
					{
						x = xO - xstep;
						y = yO;
					}
				}
				else //the corner case
				{  
					// TODO
				}
			}
			if (sim->elements_grid[xO][yO]->identifier == -1)
			{
				status = false;
				break;
			}
			else 
			{
				y = yO;
				x = xO;
			}
			eprev = e;
		}
	}
	else // if its in the other 4 octants
	{  
		eprev = dy;
		e = dy;
		for (int i = 0; i < dy; i++) 
		{
			y += ystep;
			e += ddx;
			if (e > ddy)
			{
				x += xstep;
				e -= ddy;
				if (e + eprev < ddy)
				{
					if (sim->elements_grid[xO - xstep][yO]->identifier == -1)
					{
						status = false;
						break;
					}
					else
					{
						x = xO - xstep;
						y = yO;
					}
				}
				else if (e + eprev > ddy)
				{
					if (sim->elements_grid[xO][yO - ystep]->identifier == -1)
					{
						status = false;
						break;
					}
					else
					{
						x = xO;
						y = yO - ystep;
					}
				}
				else 
				{
				}
			}
			if (sim->elements_grid[xO][yO]->identifier == -1)
			{
				status = false;
				break;
			}
			else
			{
				y = yO;
				x = xO;
			}
			eprev = e;
		}
	}
	return status;
}