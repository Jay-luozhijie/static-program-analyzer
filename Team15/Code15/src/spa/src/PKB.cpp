#include "PKB.h"

PKB::PKB() {
	procTable = ProcedureTable();
	stmtTable = StatementTable();
	varTable = VariableTable();
	constTable = ConstantTable();
	followsTable = FollowsTable();
	followsStarTable = FollowsStarTable();
	//parentTable = AbstractionTable<int, int>();
	//parentStarTable = AbstractionTable<int, int>();
}

void PKB::addProc(std::string procName) {
	procTable.addProcedureName(procName);
}

void PKB::addStmt(string stmtType, int stmtNum) { // TODO: @Galen please review
	stmtTable.addStatementNumber(stmtNum);
	stmtTable.addStatementNumberByType(stmtNum, stmtType);
}

void PKB::addVar(std::string varName) {
	varTable.addVariableName(varName);
}

void PKB::addConst(std::string constVal) {
	constTable.addConstantValue(constVal);
}

void PKB::addFollows(int leaderNum, int followerNum) {
	followsTable.addFollows(leaderNum, followerNum);
}

void PKB::addFollowsStar(int leaderNum, std::set<int> followerNums) {
	followsStarTable.addFollowsStar(leaderNum, followerNums);
}

std::set<std::string> PKB::getAllProcNames() {
	return procTable.getAllProcedureNames();
}

std::set<int> PKB::getAllStmtNums() {
	return stmtTable.getAllStatementNumbers();
}

std::set<int> PKB::getAllStmtNumsByType(string stmtType) { // TODO: @Galen please review
	return stmtTable.getAllStatementNumbersByType(stmtType);
}

std::set<std::string> PKB::getAllVarNames() {
	return varTable.getAllVariableNames();
}

std::set<std::string> PKB::getAllConstVals() {
	return constTable.getAllConstantValues();
}

int PKB::getFollowsLeaderNum(int followerNum) {
	return followsTable.getLeader(followerNum);
}

int PKB::getFollowsFollowerNum(int leaderNum) {
	return followsTable.getFollower(leaderNum);
}

std::set<int> PKB::getFollowsStarLeaderNums(int followerNum) {
	return followsStarTable.getLeaders(followerNum);
}

std::set<int> PKB::getFollowsStarFollowerNums(int leaderNum) {
	return followsStarTable.getFollowers(leaderNum);
}

bool PKB::areInFollowsRelationship(int leaderNum, int followerNum) {
	return followsTable.inRelationship(leaderNum, followerNum);
}

bool PKB::areInFollowsStarRelationship(int leaderNum, int followerNum) {
	return followsStarTable.inRelationship(leaderNum, followerNum);
}

bool PKB::isFollowsEmpty() {
	return followsTable.isEmpty();
}
