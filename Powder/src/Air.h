#pragma once
#include <vector>
#include "Vector.h"

#define AIR_TSTEPP 0.3f
#define AIR_TSTEPV 0.4f
#define AIR_VADV 0.3f
#define AIR_VLOSS 0.999f
#define AIR_PLOSS 0.9999f

class Simulation;

// The main algorithm and idea are adapted from
// the powder toys source code
// https://github.com/ThePowderToy/The-Powder-Toy/blob/master/src/simulation/Air.cpp


class Air
{
public:
	Simulation* sim;
	int air_mode;
	double amb_air_temp;
	std::vector<Vector> velocity;
	std::vector<double> pv;
	std::vector<double> hv;
	void update_air();
	void clear(std::vector<double>& data);
	void clear(std::vector<Vector>& data);
	int grid_width, grid_height, cell_size;
	void add_pressure(int x, int y, double pressure);
	void add_velocity(int x, int y, Vector vel);
	Vector get_vel(int x, int y);
	double get_pressure(int x, int y);
	Vector get_force(int x, int y);
	Air(Simulation* sim, int air_mode, double ambient_air_temp, int cell_size);
	~Air();
private:
	double kernel[9];
	std::vector<Vector> ovelocity;
	std::vector<double> opv;
	std::vector<double> ohv;
	//gaussian blur kernel
	void make_kernel();
	void update_airh();
};

