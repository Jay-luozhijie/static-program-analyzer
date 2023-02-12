#include "QPS/include/tokenizer/PQLOneSynonymCheck.h"

PQLOneSynonymCheck::PQLOneSynonymCheck() {

}

PQLOneSynonymCheck::~PQLOneSynonymCheck() {

}

bool PQLOneSynonymCheck::checkPQLOneSynonym(Query query) {
	std::multimap<std::string, std::string> varTable = query.getSynonymTable();
	SelectClause selectClause = query.getSelectClause();
    std::vector<PatternClause> patternClauseVec = query.getPatternClauseVec();
	std::vector<SuchThatClause> suchThatClauseVec = query.getSuchThatClauseVec();


	//PQLConstants::RelRefType suchThatType = suchThatClause->relRefType;
	// A synonym name can only be declared once.
	for (auto iter = varTable.begin(); iter != varTable.end(); iter++) {
		// Only can be greater than 1.
		if (varTable.count(iter->first) != 1) {
			return false;
		}
	}
	// All the synonyms used in clauses must be declared exactly once.

	// Select Clause
	// toDo remove type attribute in selectClause
	// Check if haven't been defined after checking all synonyms declared once.
	if (varTable.count(selectClause.getVarName()) != 1) {
		return false;
	}

    // to do check whether integer or underscore(non synonym)
    // SuchThat Clause
    for (SuchThatClause suchThatClause: suchThatClauseVec) {
        std::string suchThatLeftArg = suchThatClause.getLeftArg();
        std::string suchThatRightArg = suchThatClause.getRightArg();
        std::string suchThatLeftType = Utility::getReferenceType(suchThatLeftArg);
        std::string suchThatRightType = Utility::getReferenceType(suchThatRightArg);
        if (suchThatLeftType == Utility::SYNONYM && varTable.count(suchThatLeftArg) != 1) {
            return false;
        }

        if (suchThatRightType == Utility::SYNONYM && varTable.count(suchThatRightArg) != 1) {
            return false;
        }

    }

    // Pattern Clause
    for (PatternClause patternClause: patternClauseVec) {
        std::string patternLeftArg = patternClause.getLeftArg();
        std::string patternRightArg = patternClause.getRightArg();
    	std::string patternLeftType = Utility::getReferenceType(patternClause.getLeftArg());
    	std::string patternRightType = Utility::getReferenceType(patternClause.getRightArg());
        if (patternLeftType == Utility::SYNONYM && varTable.count(patternLeftArg) != 1) {
            return false;
        }

        if (patternRightType == Utility::SYNONYM && varTable.count(patternRightArg) != 1) {
            return false;
        }
        // Further Check: syn - assign must be declared as a synonym of an assignment(design entity assign)
        if (patternRightType == Utility::SYNONYM && varTable.find(patternRightArg)->second != "assign") {
            return false;
        }
    }


	return true;
}