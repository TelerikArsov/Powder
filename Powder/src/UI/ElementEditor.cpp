#include "ElementEditor.h"
#include "Element/Element.h"
#include <imgui_stdlib.h>
#include "Simulation.h"

bool ElementEditor::draw(int id, Simulation* sim)
{
	bool open = true;
	std::string title = "Element editor##" + std::to_string(id);
	if (ImGui::Begin(title.c_str(), &open, ImGuiWindowFlags_NoSavedSettings))
	{
		if (s_el != EL_NONE)
		{
			ImGui::Text("Selected %s element", s_el->name.c_str()); ImGui::SameLine();
			ImGui::Text("Description %s ", s_el->description.c_str());
			ImGui::Text("Velocity (%f, %f) ", s_el->velocity.x, s_el->velocity.y);
			ImGui::Text("Pos (%d, %d), Real pos(%f, %f)", s_el->x, s_el->y,
				s_el->pos.x, s_el->pos.y);
			ImGui::Separator();
			s_el->draw_ui();
		}
		else
		{
			ImGui::Text("Select an element (using right click): "); ImGui::SameLine();
			if(!selecting_el)
				selecting_el = ImGui::Button("NONE");
			else
			{
				Element* hovered = sim->get_from_grid(sim->mouse_cell_x, sim->mouse_cell_y);
				ImGui::Text("%s", hovered ? hovered->name.c_str() : "None");
				if (ImGui::IsMouseClicked(1))
				{
					attach(hovered);
				}

			}
		}
	}
	ImGui::End();
	prop_count = 0;
	plot_count = 0;
	return open;
}

void ElementEditor::string_prop(std::string* prop, const char* l, ElementEditorFlags flags)
{
	flags &= StringType;
	label = l;
	process_flags_b(flags);
	if ((flags & NoEditText) == NoEditText)
	{
		ImGui::Text("%s", prop);
	}
	else
	{
		if ((flags & MultilineText) == MultilineText)
			ImGui::InputTextMultiline(label, prop);
		else
			ImGui::InputText(label, prop);
	}
	process_flags_a(flags);
}

void ElementEditor::float_prop(float* prop, const char* l, float step, float step_fast, ElementEditorFlags flags)
{
	flags &= NumericType;
	label = l;
	process_flags_b(flags);
	if ((flags & DragNumeric) == DragNumeric)
		ImGui::DragFloat(label, prop, step, step_fast);
	else
		ImGui::InputFloat(label, prop, step, step_fast);
	process_flags_a(flags);
	draw_plot(*prop, flags, -20, 20);
}

void ElementEditor::int_prop(int* prop, const char* l, int step, int step_fast, ElementEditorFlags flags)
{
	flags &= NumericType;
	label = l;
	process_flags_b(flags);
	if ((flags & DragNumeric) == DragNumeric)
		ImGui::DragInt(label, prop, static_cast<float>(step));
	else
		ImGui::InputInt(label, prop, step, step_fast);
	process_flags_a(flags);
	draw_plot(static_cast<float>(*prop), flags);
}

void ElementEditor::bool_prop(bool* prop, const char* l, ElementEditorFlags flags)
{
	flags &= BoolType;
	label = l;
	process_flags_b(flags);
	ImGui::Checkbox(label, prop);
	process_flags_a(flags);
}

void ElementEditor::element_prop(Element* el, const char* label, ElementEditorFlags flags)
{
}

bool ElementEditor::attach(Element* attacheble)
{
	bool status = false;
	if (attacheble && s_el == EL_NONE && attacheble->editor == nullptr)
	{
		selecting_el = false;
		s_el = attacheble;
		s_el->editor = this;
		status = true;
	}
	return status;
}

bool ElementEditor::detach()
{
	bool status = false;
	if (s_el != EL_NONE)
	{
		s_el->editor = nullptr;
		s_el = EL_NONE;
		status = true;
	}
	return status;
}

ElementEditor::ElementEditor() :
	prop_count(0),
	plot_count(0),
	max_plot_count(0),
	selecting_el(false),
	s_el(nullptr)
{
}


ElementEditor::~ElementEditor()
{
	detach();
}

void ElementEditor::process_flags_b(ElementEditorFlags flags)
{
	if ((flags & SameLineBefore) == SameLineBefore &&
		!(flags & LabelAbove))
		ImGui::SameLine();
	if ((flags & LabelAbove) == LabelAbove)
		ImGui::Text("%s", label);

	if ((flags & LabelAbove) == LabelAbove ||
		(flags & NoLabel) == NoLabel)
	{
		label = "";
		ImGui::PushItemWidth(0);
	}
	ImGui::PushID(prop_count);
}

void ElementEditor::process_flags_a(ElementEditorFlags flags)
{
	ImGui::PopID();
	if(label == "")
		ImGui::PopItemWidth();
	prop_count++;
	if ((flags & SameLineAfter) == SameLineAfter && 
		!(flags & DrawLineGraph))
		ImGui::SameLine();
}

void ElementEditor::draw_plot(float value, ElementEditorFlags flags, float scale_min, float scale_max, size_t buffer_size)
{
	if ((flags & DrawLineGraph) == DrawLineGraph)
	{
		if (max_plot_count < plot_count + 1)
		{
			plot_values.push_back(PlotData());
			max_plot_count++;
		}
		PlotData& pd = plot_values[plot_count];
		if (pd.data.capacity() != buffer_size)
		{
			pd.data.resize(buffer_size);
			memset(&pd.data[0], 0, sizeof(float) * buffer_size);
			pd.data_insertIdx = 0;
			pd.last_frame = -1;
		}
		if (pd.data_insertIdx == buffer_size)
			pd.data_insertIdx = 0;
		int display_idx = pd.data_insertIdx;
		if (value != FLT_MAX)
			pd.data[pd.data_insertIdx++] = value;
		
		int current_frame = ImGui::GetFrameCount();
		if (current_frame != pd.last_frame)
		{
			ImGui::PushID(plot_count);
			ImGui::PlotLines("##plot", pd.data.data(), buffer_size, pd.data_insertIdx, 
				NULL, scale_min, scale_max, ImVec2(0, 70));
			pd.last_frame = current_frame;
			ImGui::PopID();
		}
		plot_count++;
	}
}
