#include "Element.h"
#include "Simulation.h"
//TODO implement an element to test this function properly
bool Element::move(int xD, int yD)
{
	bool status = true;
	if (x == xD && y == yD)
		return status;
	if (!sim->bounds_check(xD, yD))
	{
		status = false;
		return status;
	}
	int xStep, yStep;
	int xO = x, yO = y;
	int dx = xD - xO;
	int dy = yD - yO;
	int e, eprev;
	if (dy < 0)
	{
		yStep = -1;
		dy = -dy;
	}
	else
	{
		yStep = 1;
	}
	if (dx < 0)
	{
		xStep = -1;
		dx = -dx;
	}
	else
	{
		xStep = 1;
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
			xO += xStep;
			e += ddy;
			if (e > ddx) 
			{
				yO += yStep;
				e -= ddx;
				if (e + eprev < ddx)  // bottom square also
				{
					// if there is no collision we update the elements real coordinates
					if (sim->elements_grid[yO - yStep][xO]->identifier != -1) //todo function that evals the collision
					{
						status = false;
						break;
					}
					else 
					{
						sim->swap_elements(x, y, xO, yO - yStep);
						x = xO;
						y = yO - yStep;
					}
				}
				else if (e + eprev > ddx) // left corner
				{
					if (sim->elements_grid[yO][xO - xStep]->identifier != -1)
					{
						status = false;
						break;
					}
					else
					{
						sim->swap_elements(x, y, xO - xStep, yO);
						x = xO - xStep;
						y = yO;
					}
				}
				else //the corner case
				{  
					// TODO
				}
			}
			if (sim->elements_grid[yO][xO]->identifier != -1)
			{
				status = false;
				break;
			}
			else 
			{
				sim->swap_elements(x, y, xO, yO);
				x = xO;
				y = yO;
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
			yO += yStep;
			e += ddx;
			if (e > ddy)
			{
				xO += xStep;
				e -= ddy;
				if (e + eprev < ddy)
				{
					if (sim->elements_grid[yO][xO - xStep]->identifier != -1)
					{
						status = false;
						break;
					}
					else
					{
						sim->swap_elements(x, y, xO - xStep, yO);
						x = xO - xStep;
						y = yO;
					}
				}
				else if (e + eprev > ddy)
				{
					if (sim->elements_grid[yO - yStep][xO]->identifier != -1)
					{
						status = false;
						break;
					}
					else
					{
						sim->swap_elements(x, y, xO, yO - yStep);
						x = xO;
						y = yO - yStep;
					}
				}
				else 
				{
				}
			}
			if (sim->elements_grid[yO][xO]->identifier != -1)
			{
				status = false;
				break;
			}
			else
			{
				sim->swap_elements(x, y, xO, yO);
				y = yO;
				x = xO;
			}
			eprev = e;
		}
	}
	return status;
}