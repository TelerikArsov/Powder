#include "BaseUI.h"
#include "Simulation.h"
#include <string>

void BaseUI::draw(Simulation* sim)
{
	if (show_em) show_element_menu(sim);
	if (show_so) show_simulation_overlay(sim);
	show_simulation_settings(sim);
	int id = 0;
	for (auto ed = el_editor_queue.begin(); ed != el_editor_queue.end();)
	{
		if (!(*ed)->draw(id, sim))
		{
			delete (*ed);
			ed = el_editor_queue.erase(ed);
		}
		else
			++ed;
		id++;
	}
}

BaseUI::BaseUI() :
	show_em(true),
	show_so(true)
{
}


BaseUI::~BaseUI()
{
}


void BaseUI::show_simulation_settings(Simulation* sim)
{
	ImGui::SetNextWindowPos(ImVec2(562, 11));
	ImGui::SetNextWindowSize(ImVec2(430, 295), ImGuiCond_FirstUseEver);
	if (ImGui::Begin("Simulation settings", NULL))
	{
		ImGui::PushItemWidth(200);
		if (ImGui::CollapsingHeader("Simulation specific"))
		{
			ImGui::InputFloat("Scale", &(sim->scale), 0.01f, 1.0f);
			ImGui::Checkbox("Show element_menu", &show_em);
			ImGui::Checkbox("Show simulation overlay", &show_so);
			ImGui::RadioButton("No grid", &(sim->drav_grid), 0); ImGui::SameLine();
			ImGui::RadioButton("Draw grav grid", &(sim->drav_grid), 1); ImGui::SameLine();
			ImGui::RadioButton("Draw air grid", &(sim->drav_grid), 2);
			if (ImGui::Button("New element editor"))
			{
				el_editor_queue.push_back(new ElementEditor());
			}
		}
		if (ImGui::CollapsingHeader("Gravity"))
		{
			ImGui::Checkbox("Neutownian gravity", &(sim->neut_grav));
			ImGui::InputFloat("G", &(sim->gravity->G), 0.01f, 1.0f);
			ImGui::InputFloat("Mass threshold", &(sim->gravity->mass_th), 1.0f, 100.0f);
			if(ImGui::InputInt("Cell size", &(sim->gravity->cell_size), 1, 10))
			{
				sim->gravity->resize();
			}
			if (ImGui::InputFloat("Base gravity", &(sim->gravity->base_g), 0.01f, 0.1f))
			{
				sim->gravity->set_baseG();
			}
		}
		if (ImGui::CollapsingHeader("Air"))
		{
			ImGui::Combo("Air mode", &(sim->air->air_mode), "No update\0Pressure off\0Velocity off\0Off\0On\0\0");
			ImGui::Checkbox("Ambient heat", &(sim->air->ambient_heat));
			ImGui::InputFloat("Ambient air temperature", &(sim->air->amb_air_temp), 0.1f, 1.0f, "%.2f");
			ImGui::InputFloat("Pressure time step", &(sim->air->air_tstepp), 0.01f, 0.1f);
			ImGui::InputFloat("Velocity time step", &(sim->air->air_tstepv), 0.01f, 0.1f);
			ImGui::InputFloat("Air advection coef", &(sim->air->air_vadv), 0.01f, 0.1f);
			ImGui::InputFloat("Velocity loss", &(sim->air->air_vloss), 0.001f, 0.1f);
			ImGui::InputFloat("Pressure loss", &(sim->air->air_ploss), 0.001f, 0.1f);
		}
		ImGui::PopItemWidth();
	}
	ImGui::End();
}

void BaseUI::show_simulation_overlay(Simulation* sim)
{
	const float dist = 10.0f;

	ImGui::SetNextWindowPos(ImVec2(dist, dist), ImGuiCond_Always, ImVec2(0.0f, 0.0f));
	ImGui::SetNextWindowBgAlpha(0.8f);
	Element* hovered_el;
	if (ImGui::Begin("Overlay", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav))
	{
		hovered_el = sim->get_from_grid(sim->mouse_cell_x, sim->mouse_cell_y);
		ImGui::Text("Mouse Position: (%d, %d), ", sim->mouse_cell_x,
			sim->mouse_cell_y); ImGui::SameLine();
		ImGui::Text("%s, ", sim->paused ? "Paused" : "Running"); ImGui::SameLine();
		ImGui::Text("FPS: %.1f, ", sim->fps); ImGui::SameLine();
		ImGui::Text("Element count: %d", sim->elements_count);
		float temperature;
		float pressure;
		Vector air_velocity;
		const char* name;
		if(hovered_el != EL_NONE)
		{
			temperature = hovered_el->temperature;
			name = hovered_el->name.c_str();
			pressure = sim->air->get_pressure(hovered_el->x, hovered_el->y);
			air_velocity = sim->air->get_force(hovered_el->x, hovered_el->y);
		}
		else 
		{
			temperature = sim->air->amb_air_temp;
			name = "None";
			pressure = sim->air->get_pressure(sim->mouse_cell_x,
				sim->mouse_cell_y);
			air_velocity = sim->air->get_force(sim->mouse_cell_x,
				sim->mouse_cell_y);
		}
		ImGui::Text("%s ", name); ImGui::SameLine();
		ImGui::Text("Temperature: %.2f K, %.2f C;",
			temperature, temperature - 273.15f); ImGui::SameLine();
		ImGui::Text("Pressure: %.2f", pressure); ImGui::SameLine();
		ImGui::Text("Air V: (%.1f, %.1f)", air_velocity.x, air_velocity.y); ImGui::SameLine();
	}
	ImGui::End();
}

void BaseUI::show_element_menu(Simulation* sim)
{
	ImGui::SetNextWindowPos(ImVec2(10, 58));
	ImGui::SetNextWindowSize(ImVec2(210, 200), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSizeConstraints(ImVec2(-1, 0), ImVec2(-1, FLT_MAX));
	//ImGui::SetNextWindowContentSize(ImVec2(400, 0.0f));
	if (ImGui::Begin("Element Menu", &show_em, ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar))
	{
		ImGui::Columns(2, 0, false);
		ImGui::Text("Brushes"); ImGui::NextColumn();
		ImGui::Text("Elements"); ImGui::NextColumn();
		int i = 0;
		ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.31f, 0.31f, 0.31f, 1));
		// should be redone with templating and some other method 
		// (gotta learn that stuff)
		ImGui::BeginChildFrame(ImGui::GetID("brushes"), ImVec2(70, -1));
		for (auto br : sim->brushes)
		{
			bool is_selected = (selected_br == i);
			if (ImGui::Selectable(br->name.c_str(), is_selected))
			{
				selected_br = i;
				sim->select_brush(i);
			}
			if (is_selected)
				ImGui::SetItemDefaultFocus();
			i++;
		}
		ImGui::EndChildFrame();
		//ImGui::SameLine();
		ImGui::NextColumn();
		i = 0;

		ImGui::BeginChildFrame(ImGui::GetID("elements"), ImVec2(80, -1));
		if (ImGui::CollapsingHeader("Elems##header"))
		{
			for (auto el : sim->available_elements)
			{
				bool is_selected = (selected_el == i);
				ImGui::PushStyleColor(ImGuiCol_Text, el->color);
				if (ImGui::Selectable(el->name.c_str(), is_selected))
				{
					selected_tl = -1;
					selected_el = i;
					sim->select_element(el->identifier);
				}
				if (is_selected)
					ImGui::SetItemDefaultFocus();
				i++;
				ImGui::PopStyleColor();
			}
		}
		i = 0;
		if (ImGui::CollapsingHeader("Tools##header"))
		{
			for (auto el : sim->tools)
			{
				bool is_selected = (selected_tl == i);
				if (el->identifier != TL_SPWN)
				{
					ImGui::PushStyleColor(ImGuiCol_Text, el->color);
					if (ImGui::Selectable(el->name.c_str(), is_selected))
					{
						selected_el = -1;
						selected_tl = i;
						sim->select_tool(el->identifier);
					}
					if (is_selected)
						ImGui::SetItemDefaultFocus();
					i++;
					ImGui::PopStyleColor();
				}
			}
		}
		ImGui::EndChildFrame();
		
		ImGui::PopStyleColor();
		ImGui::NextColumn();
		ImGui::Columns(1);
	}
	ImGui::End();
}
/*template <class T>
void BaseUI::DrawSelectableList(std::vector<T> container, bool& selected)
{
	ImGui::BeginChildFrame(ImGui::GetID("brushes"), ImVec2(70, -1));
	for (auto br : container)
	{
		bool is_selected = (selected == i);
		if (ImGui::Selectable(br->name.c_str(), is_selected))
		{
			selected_br = i;
			sim->select_brush(i);
		}
		if (is_selected)
			ImGui::SetItemDefaultFocus();
		i++;
	}
	ImGui::EndChildFrame();
}*/