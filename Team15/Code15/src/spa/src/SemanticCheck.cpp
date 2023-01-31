#include "SemanticCheck.h"

SemanticCheck::SemanticCheck() {}

SemanticCheck::~SemanticCheck() {}

bool SemanticCheck::checkSemantics(PreProcessedResults preProcessedResults) {
	/*A synonym name can only be declared once.
		All the synonyms used in clauses must be declared exactly once.
		syn - assign must be declared as a synonym of an assignment(design entity assign).
		The first argument for Modifies and Uses cannot be _, as it is unclear whether _ refers to a statement or procedure.
		Synonyms of design entities can appear as relationship arguments, and should match the design entity defined for the relationship.
		E.g.For Parent(arg1, arg2), if arg1 is a synonym, then arg1 must be a statement synonym, or a subtype of a statement synonym(read, print, assign, if, while, call).
		E.g.For Modifies(arg1, arg2), if arg2 is a synonym, then arg2 must be a variable synonym.*/

	std::multimap<std::string, std::string> varTable = preProcessedResults.getVarTable();
	SelectClause selectClause = preProcessedResults.getSelectClause();
	PatternClause patternClause = preProcessedResults.getPatternClause();
	SuchThatClause suchThatClause = preProcessedResults.getSuchThatClause();

	PQLConstants::RelRefType suchThatType = suchThatClause->relRefType;

	for (auto iter = varTable.begin(); iter != varTable.end(); iter++) {
		if (varTable.count(iter->first) > 1) {
			return false;
		}
	}

	if (varTable.count(selectClause.getVarEntityPair().first) != 1) {
		return false;
	}

	if (varTable.count(suchThatClause.getLeftPair().second) != 1 || varTable.count(suchThatClause.getRightPair().second) != 1) {
		return false;
	}

	if (varTable.count(patternClause.getLeftPair().second) != 1 || varTable.count(patternClause.getRightPair().second) != 1) {
		return false;
	}

	if ((suchThatType == MODIFIES || (suchThatClause->relRefType) == USES) && (suchThatClause->leftHandArg) == UNDERSCORE) {
		return false;
	}

	if ((suchThatClause->relRefType) == MODIFIES && check_synonym(suchThatClause->rightHandArg)) {
		if (suchThatClause->rightHandType != VARIABLE) {
			return false;
		}
	}

	if () {
	}
}