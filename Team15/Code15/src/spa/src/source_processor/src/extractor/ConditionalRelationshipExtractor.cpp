#include "source_processor/include/extractor/ConditionalRelationshipExtractor.h"

vector<string> getCondition(const string& conditionType, const vector<string>& tokens) {
    auto* brackets = new stack<string>();
    auto* condition = new vector<string>();
    for(const auto& token : tokens) {
        if(token == "(") {
            brackets->push(token);
        } else if (token == ")") {
            brackets->pop();
        }
        if(!brackets->empty()) {
            condition->push_back(token);
        } else if (token != conditionType) {
            condition->push_back(token);
            break;
        }
    }
    condition->erase(condition->begin());
    condition->erase(condition->end() - 1);
    return *condition;
}

void getLineVariables(const set<string>& variables, const vector<string>& tokens, unordered_map<string, set<Line>>* conditionalRS, Line newLine) {
    set<string> lineVariables;
    for(const auto& token : tokens) {
        if(variables.find(token) != variables.end()) {
            if (conditionalRS->count(token) == 0) {
                conditionalRS->emplace(token, set<Line>({newLine}));
            } else {
                conditionalRS->at(token).insert(newLine);
            }
        }
    }
}

unordered_map<string, set<Line>> extractConditionalRS(const string& conditionType, const vector<Line>& program, const set<string>& variables) {
    unordered_map<string, set<Line>> conditionalRS;
    for(auto line : program) {
        int lineNumber = line.getLineNumber();
        string type = line.getType();
        vector<string> tokens = line.getTokens();
        if(type != conditionType) continue;
        vector<string> condition = getCondition(conditionType, tokens);
        vector<string> postfixCondition = convertToPostfix(condition, variables);
        Line newLine = Line(lineNumber, postfixCondition);
        getLineVariables(variables, tokens, &conditionalRS, newLine);
    }
    return conditionalRS;
}
