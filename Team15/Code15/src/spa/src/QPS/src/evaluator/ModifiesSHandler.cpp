#include "QPS/include/evaluator/ModifiesSHandler.h"


ModifiesSHandler::ModifiesSHandler(PKB& pkb) : ClauseHandler(pkb) {}

std::string trim_double_quotes(std::string s) {
	if (s.length() >= 2 && s[0] == '"' && s[s.length() - 1] == '"') {
		return s.substr(1, s.length() - 2);
	}
	return s;
}

Result ModifiesSHandler::evalModifiesS(SuchThatClause suchThatClause, ResultTable& resultTable, std::multimap<std::string, std::string>& synonymTable) {
	std::string leftArg = suchThatClause.getLeftArg();
	std::string rightArg = suchThatClause.getRightArg();
	std::string leftType = Utility::getReferenceType(leftArg);
	std::string rightType = Utility::getReferenceType(rightArg);
	Result result;
	//std::set<std::string> getModifiesVarsFromStmt(int stmtNum);

	//std::set<int> getModifiesStmtsFromVar(std::string varName);

	//std::set<std::string> getModifiesVarsFromProc(std::string procName);

	//std::set<std::string> getModifiesProcsFromVar(std::string varName);

	//bool areInModifiesStmtRelationship(int stmtNum, std::string varName);

	// bool areInModifiesProcRelationship(std::string procName, std::string varName);
	
	// Find everything defined in source modified by a statement line defined in source.
	if (leftType == Utility::INTEGER && rightType == Utility::UNDERSCORE) {
		//input statement line number, return all vars modified in statement line.
		std::set<std::string> modifiesSet = pkb.getModifiesVarsFromStmt(stoi(leftArg));
		if (modifiesSet.empty()) {
			result.setResultTrue(false);
			return result;
		}
	}
	// Find ident string in source program which is modified by a statement line defined in source.
	else if (leftType == Utility::INTEGER && rightType == Utility::QUOTED_IDENT) {
		// identString of format \"x\"
		bool isModifies = pkb.areInModifiesStmtRelationship(stoi(leftArg), trim_double_quotes(rightArg));
		if (!isModifies) {
			result.setResultTrue(false);
			return result;
		}
	}
	//Find variable v defined in QPS which is modified by given statement line defined in source. 
	else if (leftType == Utility::INTEGER) {
		string synonDeType = synonymTable.find(rightArg)->second;
		resultTableCheckAndAdd(rightArg, resultTable, synonDeType);
		std::set<string> currSynonValues = resultTable.getValueFromKey(rightArg);

		std::set<string> resultSynonValues;
	
		for (string currSynonVal : currSynonValues) {
			// check whether given statement line modifies historical variables in source.
			bool isModifies = pkb.areInModifiesStmtRelationship(stoi(leftArg), currSynonVal);
			if (isModifies) {
				resultSynonValues.insert(currSynonVal);
			}
		}
	
		if (resultSynonValues.empty()) {
			result.setResultTrue(false);
			return result;
		}
		result.setSecondArg(rightArg, resultSynonValues);
	}
	//Left type is a statement defined in QPS, find whether given statement has some modifications to some variables in source
	else if (rightType == Utility::UNDERSCORE) {
		string synonDeType = synonymTable.find(leftArg)->second;
		resultTableCheckAndAdd(leftArg, resultTable, synonDeType);
		// currSynonValues here are statement line numbers in string format.
		std::set<string> currSynonValues = resultTable.getValueFromKey(leftArg);

		std::set<string> resultSynonValues;

		for (string currSynonVal : currSynonValues) {

			std::set<std::string> modifiesSet = pkb.getModifiesVarsFromStmt(stoi(currSynonVal));
			
			if (!modifiesSet.empty()) {
				resultSynonValues.insert(currSynonVal);
			}
		}
	
		if (resultSynonValues.empty()) {
			result.setResultTrue(false);
			return result;
		}
		result.setFirstArg(leftArg, resultSynonValues);
	}
	//Left type is a statement defined in QPS, find whether given statement modifies given variable in source.
	else if (rightType == Utility::QUOTED_IDENT) {
		string synonDeType = synonymTable.find(leftArg)->second;
		resultTableCheckAndAdd(leftArg, resultTable, synonDeType);
		// currSynonValues here are statement line numbers in string format.
		std::set<string> currSynonValues = resultTable.getValueFromKey(leftArg);

		std::set<string> resultSynonValues;

		for (string currSynonVal : currSynonValues) {
			// check whether given statement line modifies historical variables in source.
			bool isModifies = pkb.areInModifiesStmtRelationship(stoi(currSynonVal), trim_double_quotes(rightArg));
			if (isModifies) {
				resultSynonValues.insert(currSynonVal);
			}
		}

		if (resultSynonValues.empty()) {
			result.setResultTrue(false);
			return result;
		}
		result.setFirstArg(leftArg, resultSynonValues);
	}
	//Left type is a statement defined in QPS, right type is a varible defined in QPS, find all pairs of statement s defined in source and varible v 
	// defined in source such that s modifies v. 
	else {
		string leftDeType = synonymTable.find(leftArg)->second;
		string rightDeType = synonymTable.find(rightArg)->second;
		resultTableCheckAndAdd(leftArg, resultTable, leftDeType);
		resultTableCheckAndAdd(rightArg, resultTable, rightDeType);
		std::set<string> currLeftValues = resultTable.getValueFromKey(leftArg);
		std::set<string> currRightValues = resultTable.getValueFromKey(rightArg);

		std::set<string> leftResultValues;
		std::set<string> rightResultValues;

		for (string currLeftVal : currLeftValues) {
			for (string currRightVal : currRightValues) {
				bool isRightModifiesLeft = pkb.areInModifiesStmtRelationship(stoi(currLeftVal), currRightVal); 
				if (isRightModifiesLeft) {
					leftResultValues.insert(currLeftVal);
					rightResultValues.insert(currRightVal);
				}
			}
		}

		if (leftResultValues.empty() || rightResultValues.empty()) {
			result.setResultTrue(false);
			return result;
		}

		result.setFirstArg(leftArg, leftResultValues);
		result.setSecondArg(rightArg, rightResultValues);
	}
	//Do we need to throw exception if type doesn't match? As all semantics are checked already.
	return result;
}
