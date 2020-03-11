#include <cstring>
#include "circuit.hpp"

#include <iostream>

using std::string;

const char* Circuit::getName() {
	return name->c_str();
}

const char* Circuit::getLabel() {
	return label->c_str();
}

Circuit::Side Circuit::getLabelUp() {
	return labelup;
}

const char* Circuit::getLabelFont() {
	return labelfont->c_str();
}

Circuit::Circuit(const char* _name, const char* _label, Circuit::Side _labelup, const char* _labelfont) {
	name = new string(_name);
	label = new string(_label);
	labelup = _labelup;
	labelfont = new string(_labelfont);
}

Circuit::~Circuit() {

}

bool _CircuitCmp::cmp::operator()(Part *a, Part *b) const
{
	return a->getUID() > b->getUID();
}
