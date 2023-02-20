#include "source_processor/include/extractor/ModifiesRelationshipExtractor.h"

/**
 * Goes through each line of the program and checks if the line is a read, assign or is a container where modifies holds
 */
unordered_map<int, set<string>> extractModifiesRS(const vector<Line>& program) {
    unordered_map<int, set<string>> modifiesRS;
    vector<int> stmtContainerStack;
    for (Line line: program) {
        int currLineNumber = line.getLineNumber();
        vector<string> tokens = line.getTokens();
        string lineType = line.getType();

        if (lineType == "call" || lineType == "else") {
            continue;
        } else if (lineType == "procedure") {
            stmtContainerStack.clear(); // new procedure failsafe
            continue;
        } else if (lineType == "if" || lineType == "while") { // keep track of stmt container line number
            stmtContainerStack.push_back(currLineNumber);
            continue;
        } else if (lineType == "}") {
            if (!stmtContainerStack.empty()) {
                stmtContainerStack.pop_back();
            }
            continue;
        }

        string varName;
        if (lineType == "=") {
            auto [LHS, RHS] = getLHSandRHSofAssignStatement(tokens);
            varName = LHS[0];
        } else if (lineType == "read") { // check if modifies(r, v)
            varName = getVarNameFromReadStatement(tokens);
        }
        if (currLineNumber) {
            modifiesRS[currLineNumber].insert(varName); // for current line
        }
        if (!stmtContainerStack.empty()) { // for stmtContainer: modifies(s, v)
            for (auto stmtContainerLine : stmtContainerStack) {
                modifiesRS[stmtContainerLine].insert(varName);
            }
        }
    }
    return modifiesRS;
}