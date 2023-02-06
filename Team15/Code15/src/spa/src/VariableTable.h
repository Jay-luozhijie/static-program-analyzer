#pragma once

#include <string>
#include <set>

using namespace std;

class VariableTable {
public:
	VariableTable();

	void addVariableName(std::string variableName);

	std::set<std::string> getAllVariableNames();

private:
	std::set<std::string> variableTable;
};