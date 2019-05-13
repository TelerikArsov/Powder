#pragma once
#include <list>
#include <imgui.h>
#include <imgui-SFML.h>
#include "ElementEditor.h"

class Simulation;

class BaseUI
{
public:
	bool show_em;
	bool show_so;
	void draw(Simulation* sim);
	BaseUI();
	~BaseUI();
private:
	int selected_el = -1;
	int selected_br = -1;
	int selected_tl = -1;
	std::list<ElementEditor*> el_editor_queue;
	void show_simulation_settings(Simulation* sim);
	void show_simulation_overlay(Simulation* sim);
	void show_element_menu(Simulation* sim);
	void fill_scrollable_list();
};

