#include "Air.h"
#include "Simulation.h"


void Air::update_air()
{
	double dp = 0.0;
	Vector t = Vector();
	const double adv_dist_mult = 0.7;

	//airMode 4 is no air/pressure update
	if (air_mode != 4)
	{
		//reduces pressure/velocity on the edges every frame
		for (int i = 0; i < grid_height; i++) 
		{
			int idx = i * grid_width;
			pv[idx] *= 0.8f;
			pv[idx + 1] *= 0.8f;
			//pv[i][2] = pv[i][2] * 0.8f;
			pv[idx + grid_width - 2] *= 0.8f;
			pv[idx + grid_width - 1] *= 0.8f;

			velocity[idx] *= 0.9f;
			velocity[idx + 1] *= 0.9f;
			velocity[idx + grid_width - 2] *= 0.9f;
			velocity[idx + grid_width - 1] *= 0.9f;
		}
		//reduces pressure/velocity on the edges every frame
		for (int i = 0; i < grid_width; i++) 
		{
			pv[i] *= 0.8f;
			pv[grid_width + i] *= 0.8f;
			//pv[2][i] = pv[2][i] * 0.8f;
			pv[(grid_height - 2) * grid_width + i] *= 0.8f;
			pv[(grid_height - 1) * grid_width + i] *= 0.8f;

			velocity[i] *= 0.9f;
			velocity[grid_width + i] *= 0.9f;
			velocity[(grid_height - 2) * grid_width + i] *= 0.9f;
			velocity[(grid_height - 1) * grid_width + i] *= 0.9f;
		}
		//pressure adjustments from velocity
		for (int y = 1; y < grid_height; y++) 
		{
			for (int x = 1; x < grid_width; x++)
			{
				int idx = y * grid_width + x;
				dp = 0.0f;
				dp += velocity[idx - 1].x - velocity[idx].x;
				dp += velocity[(y - 1) * grid_width + x].y - velocity[idx].y;
				pv[idx] *= AIR_PLOSS;
				pv[idx] += dp * AIR_TSTEPP;
			}
		}
		double dx = 0.0, dy = 0.0;
		for (int y = 0; y < grid_height - 1; y++) //velocity adjustments from pressure
		{
			for (int x = 0; x < grid_width - 1; x++)
			{
				int idx = y * grid_width + x;
				dx = dy = 0.0;
				dx += pv[idx] - pv[idx + 1];
				dy += pv[idx] - pv[(y + 1) * grid_width + x];
				velocity[idx] *= AIR_VLOSS;
				velocity[idx].x += dx * AIR_TSTEPV;
				velocity[idx].y += dy * AIR_TSTEPV;
			}
		}
		double f = 0.0;
		//update velocity and pressure
		for (int y = 0; y < grid_height; y++) 
		{
			for (int x = 0; x < grid_width; x++)
			{
				Vector d = Vector();
				dp = 0.0f;
				for (int j = -1; j < 2; j++)
				{
					for (int i = -1; i < 2; i++)
					{
						if (y + j > 0 && y + j < grid_height - 1 &&
							x + i > 0 && x + i < grid_width - 1)
						{
							f = kernel[i + 1 + (j + 1) * 3];
							d += velocity[(y + j) * grid_width + x + i] * f;
							dp += pv[(y + j) * grid_width + x + i] * f;
						}
						else
						{
							f = kernel[i + 1 + (j + 1) * 3];
							d += velocity[y * grid_width + x] * f;
							dp += pv[y * grid_width + x] * f;
						}
					}
				}
				t = Vector(x, y) - d * adv_dist_mult;
				int i = static_cast<int>(t.x);
				int j = static_cast<int>(t.y);
				t -= Vector(i, j);
				if (i >= 2 && i < grid_width - 2 &&
					j >= 2 && j < grid_height - 2)
				{
					d *= 1.0f - AIR_VADV;

					d += AIR_VADV * (1.0f - t.x) * (1.0f - t.y) * velocity[j * grid_width + i];

					d += AIR_VADV * t.x * (1.0f - t.y) * velocity[j * grid_width + i];

					d += AIR_VADV * (1.0f - t.x) * t.y * velocity[(j + 1) * grid_width + i];

					d += AIR_VADV * t.x * t.y * velocity[(j + 1) * grid_width + i + 1];
				}

				// pressure/velocity caps
				std::clamp(dp, -256.0, 256.0);
				std::clamp(d.x, -256.0, 256.0);
				std::clamp(d.y, -256.0, 256.0);

				switch (air_mode)
				{
				default:
				case 0:  //Default
					break;
				case 1:  //0 Pressure
					dp = 0.0f;
					break;
				case 2:  //0 Velocity
					d.Zero();
					break;
				case 3: //0 Air
					d.Zero();
					dp = 0.0f;
					break;
				case 4: //No Update
					break;
				}

				ovelocity[y * grid_width + x] = d;
				opv[y * grid_width + x] = dp;
			}
		}
		velocity = ovelocity;
		pv = opv;
	}
}

void Air::update_airh()
{
	double dh, f;

	for (int i = 0; i < grid_height; i++) //reduces pressure/velocity on the edges every frame
	{
		int idx = i * grid_width;
		hv[idx] = amb_air_temp;
		hv[idx + 1] = amb_air_temp;
		hv[idx + grid_width - 2] = amb_air_temp;
		hv[idx + grid_width - 2] = amb_air_temp;
	}
	for (int i = 0; i < grid_width; i++) //reduces pressure/velocity on the edges every frame
	{
		hv[i] = amb_air_temp;
		hv[grid_width + i] = amb_air_temp;
		hv[(grid_height - 2) * grid_width + i] = amb_air_temp;
		hv[(grid_height - 1) * grid_width + i] = amb_air_temp;
	}
	for (int y = 0; y < grid_height; y++) //update velocity and pressure
	{
		for (int x = 0; x < grid_width; x++)
		{
			dh = 0.0f;
			Vector d = Vector();
			for (int j = -1; j < 2; j++)
			{
				for (int i = -1; i < 2; i++)
				{
					if (y + j > 0 && y + j < grid_height - 1 &&
						x + i>0 && x + i < grid_width - 1)
					{
						f = kernel[i + 1 + (j + 1) * 3];
						d += velocity[(y + j) * grid_width + x + i] * f;
						dh += hv[(y + j) * grid_width + x + i] * f;
					}
					else
					{
						f = kernel[i + 1 + (j + 1) * 3];
						d += velocity[y * grid_width + x] * f;
						dh += hv[y * grid_width + x] * f;
					}
				}
			}
			Vector t = Vector(x, y) - d * 0.7;
			int i = static_cast<int>(t.x);
			int j = static_cast<int>(t.y);
			t -= Vector(i, j);
			if (i >= 2 && i < grid_width - 2 && 
				j >= 2 && j < grid_height - 2)
			{
				dh *= 1.0f - AIR_VADV;
				dh += AIR_VADV * (1.0f - t.x) * (1.0f - t.y) * hv[j * grid_width + i];
				dh += AIR_VADV * t.x * (1.0f - t.y) * hv[j * grid_width + i + 1];
				dh += AIR_VADV * (1.0f - t.x) * t.y * hv[(j + 1) * grid_width + i];
				dh += AIR_VADV * t.x * t.y * hv[(j + 1) * grid_width + i + 1];
			}
			ohv[y * grid_width + x] = dh;
		}
	}
	hv = ohv;
}

void Air::clear(std::vector<double>& data)
{
	std::fill(data.begin(), data.end(), 0);
}

void Air::clear(std::vector<Vector>& data)
{
	for (auto& el : data)
	{
		el.Zero();
	}
}

void Air::add_pressure(int x, int y, double pressure)
{
	pv[x / cell_size + grid_width * (y / cell_size)] += pressure;
}

void Air::add_velocity(int x, int y, Vector vel)
{
	velocity[x / cell_size + grid_width * (y / cell_size)] += vel;
}

Vector Air::get_vel(int x, int y)
{
	return velocity[x / cell_size + grid_width * (y / cell_size)];
}

double Air::get_pressure(int x, int y)
{
	return pv[x / cell_size + grid_width * (y / cell_size)];
}

Vector Air::get_force(int x, int y)
{
	return velocity[x / cell_size + grid_width * (y / cell_size)];
}

Air::Air(Simulation* sim, int air_mode, double ambient_air_temp, int cell_size) :
	sim(sim),
	air_mode(air_mode),
	amb_air_temp(ambient_air_temp),
	cell_size(cell_size),
	grid_width(std::ceil(static_cast<double>(sim->cells_x_count) / cell_size)),
	grid_height(std::ceil(static_cast<double>(sim->cells_y_count) / cell_size))
{
	make_kernel();
	for (int i = 0; i < grid_height; i++)
	{
		for (int j = 0; j < grid_width; j++)
		{
			velocity.emplace_back(Vector());
			ovelocity.emplace_back(Vector());
			hv.push_back(0.0);
			ohv.push_back(0.0);
			pv.push_back(0.0);
			opv.push_back(0.0);
		}
	}
}


Air::~Air()
{
}

void Air::make_kernel()
{
	int i, j;
	double s = 0.0f;
	for (j = -1; j < 2; j++)
		for (i = -1; i < 2; i++)
		{
			kernel[(i + 1) + 3 * (j + 1)] = expf(-2.0f * (i * i + j * j));
			s += kernel[(i + 1) + 3 * (j + 1)];
		}
	s = 1.0f / s;
	for (j = -1; j < 2; j++)
		for (i = -1; i < 2; i++)
			kernel[(i + 1) + 3 * (j + 1)] *= s;
}