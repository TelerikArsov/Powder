#include "SimObject.h"
#include <imgui.h>
#include <imgui-SFML.h>


int SimObject::scrollable_display(bool selected)
{
	int id = -1;
	ImGui::PushStyleColor(ImGuiCol_Text, color);
	if (ImGui::Selectable(name.c_str(), selected))
	{
		id = 0;
	}
	ImGui::PopStyleColor();
	if (ImGui::IsItemHovered())
	{
		if (ImGui::IsMouseReleased(1))
		{
			id = 1;
		}
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 15.0f);
		ImGui::TextUnformatted(description.c_str());
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
	if (selected)
		ImGui::SetItemDefaultFocus();
	return id;
}

SimObject::~SimObject()
{}
