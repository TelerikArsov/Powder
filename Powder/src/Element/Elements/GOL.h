#pragma once
#include "Element/Element.h"
class GOL :
	public Element
{
public:
	// Rulestring format is as follows
	// S, B, or D to specify which rule is listed and each rules might be seperated by / or \
	// example: s../b../d. (rules are not case sensetive, order of rules is irrelevant, as long
	// as the rules are started with the right letter )
	// if no rule letters are present the order is B>S>D as long as / or \ is present for rule separation
	// S is followed by digits corresponding to the amount of cells
	// E.G. S1234 means the cell will (S)urvive if surrounded by 1, 2, 3, or 4 alive cells
	// B is followed by digits corresponding to the amount of cells
	// E.G. B1234 means the cell will be (B)orn if surrounded by 1, 2, 3, or 4 alive cells
	// D is followed by one number
	// E.G. D12 means that when the cell is about to die, 
	// it instead lingers in a state that is not considered alive or dead for N generations
	// where n is the amount specified 
	std::string rule_string = "";
	bool rules[3][9] = { false };
	enum { B = 0, S = 1, D = 2 };
	// Processes the rule string and fills the rules array
	void process_rules();
	int update(float dt) override;
	void draw_ui() override;
	virtual ~GOL() = 0;
};

