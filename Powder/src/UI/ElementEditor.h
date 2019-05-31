#pragma once
#include <imgui.h>
#include <imgui-SFML.h>
#include <vector>
enum ElementEditorFlags : uint8_t
{
	NoFlags = 0,
	SameLineAfter = 1 << 0,
	SameLineBefore = 1 << 1,
	DragNumeric = 1 << 2,
	MultilineText = 1 << 3,
	NoLabel = 1 << 4,
	LabelAbove = 1 << 5,
	NoEditText = 1 << 6,
	DrawLineGraph = 1 << 7,

	StringType = SameLineAfter | SameLineBefore | NoEditText 
		| MultilineText | NoLabel | LabelAbove,
	
	NumericType = SameLineAfter | SameLineBefore | DragNumeric
		| NoLabel | LabelAbove | DrawLineGraph,

	BoolType = SameLineAfter | SameLineBefore | NoLabel | LabelAbove
};

constexpr ElementEditorFlags operator& (ElementEditorFlags x, ElementEditorFlags y)
{
	return static_cast<ElementEditorFlags>(
		static_cast<uint8_t>(x) & static_cast<uint8_t>(y));
}

constexpr ElementEditorFlags operator| (ElementEditorFlags x, ElementEditorFlags y)
{
	return static_cast<ElementEditorFlags>(
		static_cast<uint8_t>(x) | static_cast<uint8_t>(y));
}

constexpr ElementEditorFlags operator^ (ElementEditorFlags x, ElementEditorFlags y)
{
	return static_cast<ElementEditorFlags>(
		static_cast<uint8_t>(x) ^ static_cast<uint8_t>(y));
}

constexpr ElementEditorFlags operator~ (ElementEditorFlags x)
{
	return static_cast<ElementEditorFlags>(~static_cast<uint8_t>(x));
}

constexpr ElementEditorFlags& operator&= (ElementEditorFlags& x, ElementEditorFlags y)
{
	x = x & y; return x;
}

constexpr ElementEditorFlags& operator|= (ElementEditorFlags& x, ElementEditorFlags y)
{
	x = x | y; return x;
}

constexpr ElementEditorFlags& operator^= (ElementEditorFlags& x, ElementEditorFlags y)
{
	x = x ^ y; return x;
}

class Element;
class Simulation;

class ElementEditor
{
public:
	Element* s_el;
    bool draw(int id, Simulation* sim);
	bool string_prop(std::string* prop, const char* label, ElementEditorFlags flags = NoFlags);
	bool float_prop(float* prop, const char* label, float step, float step_fast, ElementEditorFlags flags = NoFlags);
	bool int_prop(int* prop, const char* label, int step, int step_fast, ElementEditorFlags flags = NoFlags);
	bool bool_prop(bool* prop, const char* labell, ElementEditorFlags flags = NoFlags);
	bool attach(Element* attacheble);
	bool detach();
	ElementEditor();
	~ElementEditor();
private:
	struct PlotData
	{
		std::vector<float> data;
		int data_insertIdx;
		int last_frame;

		PlotData() : data_insertIdx(0), last_frame(-1) {}
	};

	bool selecting_el;
	int prop_count;
	int plot_count;
	int max_plot_count;
	const char* label;
	std::vector <PlotData> plot_values;
	void process_flags_b(ElementEditorFlags flags);
	void process_flags_a(ElementEditorFlags flags);
	void draw_plot(float value, ElementEditorFlags flags, float scale_min = FLT_MAX, float scale_max = FLT_MAX, size_t buffer_size = 120);
};

