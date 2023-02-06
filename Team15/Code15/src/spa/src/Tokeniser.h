#pragma once
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <stdio.h>
#include "Tokens.h"
#include "TokenMap.h"
#include <iostream>

using namespace std;

class Tokeniser {
public:
    void driver();
    map<int, vector<string>> processFile(std::ifstream &file);
    map<int, int> generateFollowsRS(map<int, int> nesting_level);
    map<int, set<int>> generateFollowsStarRS(map<int, int> nesting_level);
    map<int, int> generateNestingLevel(map<int, vector<string>>);
    map<string, vector<vector<string>>> generateAssignmentRS(map<int, vector<string>>);
    int precedence(std::string c);
    bool isOperator(std::string c);
    bool isNumeric(const std::string token);
    bool isStatement(std::string token);
    Tokens::Keyword getStatementType(std::string token);
    bool isNumber(std::string num);
    std::vector<std::string> convertToPostfix(std::vector<std::string> tokens, int startIndex);
    bool findToken(std::string s);
    bool emptyToken(std::string token);
    std::vector<std::string> pushToken(std::vector<std::string> tokens, std::string token);
    std::vector<std::string> tokenise(std::string line, int lineNumber);
    void extract(std::vector<std::string> tokens, int lineNumber);
    int main();

private:
    TokenMap tokenMap;

};
