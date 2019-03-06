#pragma once
#include <vector>
#include "Vector.h"



class Simulation;

// The main algorithm and idea are adapted from
// the powder toys source code
// https://github.com/ThePowderToy/The-Powder-Toy/blob/master/src/simulation/Air.cpp


class Air
{
public:
	Simulation* sim;
	int grid_width, grid_height, cell_size;
	int air_mode;
	bool ambient_heat;
	float amb_air_temp;
	float air_tstepp = 0.3f;
	float air_tstepv = 0.4f;
	float air_vadv = 0.3f;
	float air_vloss = 0.999f;
	float air_ploss = 0.9999f;

	std::vector<Vector> velocity;
	std::vector<float> pv;
	std::vector<float> hv;

	void update_air();
	void clear(std::vector<float>& data);
	void clear(std::vector<Vector>& data);
	void add_pressure(int x, int y, float pressure);
	void add_velocity(int x, int y, Vector vel);
	Vector get_vel(int x, int y);
	float get_pressure(int x, int y);
	Vector get_force(int x, int y);
	Air(Simulation* sim, int air_mode, float ambient_air_temp, int cell_size);
	~Air();
private:
	float kernel[9];
	std::vector<Vector> ovelocity;
	std::vector<float> opv;
	std::vector<float> ohv;
	//gaussian blur kernel
	void make_kernel();
	void update_airh();
};

