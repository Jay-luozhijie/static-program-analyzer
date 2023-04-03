#include "pkb/include/PKB.h"

PKB::PKB() {
	procTable = EntityTable<std::string>();
	varTable = EntityTable<std::string>();
	constTable = EntityTable<std::string>();
	lineTable = EntityTable<Line>();
	stmtTable = StatementTable();
	followsTable = RelationshipTable<int, int>();
	followsStarTable = RelationshipTable<int, int>();
	parentTable = RelationshipTable<int, int>();
	parentStarTable = RelationshipTable<int, int>();
	usesStmtTable = RelationshipTable<int, std::string>();
	usesProcTable = RelationshipTable<std::string, std::string>();
	modifiesStmtTable = RelationshipTable<int, std::string>();
	modifiesProcTable = RelationshipTable<std::string, std::string>();
	callsTable = RelationshipTable<std::string, std::string>();
	callsStarTable = RelationshipTable<std::string, std::string>();
	nextTable = RelationshipTable<int, int>();
	nextStarTable = RelationshipTable<int, int>();
	affectsTable = RelationshipTable<int, int>();
	affectsStarTable = RelationshipTable<int, int>();
	withReadTable = RelationshipTable<int, std::string>();
	withPrintTable = RelationshipTable<int, std::string>();
	withCallTable = RelationshipTable<int, std::string>();
	assignPatternTable = PatternTable();
	whilePatternTable = PatternTable();
	ifPatternTable = PatternTable();
}

//ADD
//add procedure
void PKB::addAllProcs(std::set<std::string> procNames) {
	procTable.addAllEntities(procNames);
}

//add variable
void PKB::addAllVars(std::set<std::string> varNames) {
	varTable.addAllEntities(varNames);
}

//add constant
void PKB::addAllConsts(std::set<std::string> constVals) {
	constTable.addAllEntities(constVals);
}

//add line
void PKB::addAllLines(std::set<Line> allLines) {
	lineTable.addAllEntities(allLines);
}

//add statement
void PKB::addAllStmts(std::unordered_map<KeywordsEnum, std::set<int>> stmtNums) {
	stmtTable.addAllStatementNumbers(stmtNums);
	stmtTable.addAllStatementNumbersByType(stmtNums);
}

//add follows
void PKB::addAllFollows(std::unordered_map<int, int> allLeaderToFollower) {
	followsTable.addAllOneToOneRelationships(allLeaderToFollower);
}

//add follows*
void PKB::addAllFollowsStar(std::unordered_map<int, std::set<int>> allLeaderToFollowers) {
	followsStarTable.addAllManyToManyRelationships(allLeaderToFollowers);
}

//add parent
void PKB::addAllParent(std::unordered_map<int, std::set<int>> allParentToChildren) {
	parentTable.addAllOnetoManyRelationships(allParentToChildren);
}

//add parent*
void PKB::addAllParentStar(std::unordered_map<int, std::set<int>> allParentToChildren) {
	parentStarTable.addAllManyToManyRelationships(allParentToChildren);
}

//add uses statement-variable
void PKB::addAllUsesStmt(std::unordered_map<int, std::set<std::string>> allStmtToVars) {
	usesStmtTable.addAllManyToManyRelationships(allStmtToVars);
}

//add uses procedure-variable
void PKB::addAllUsesProc(std::unordered_map<std::string, std::set<std::string>> allProcToVars) {
	usesProcTable.addAllManyToManyRelationships(allProcToVars);
}

//add modifies statement-variable
void PKB::addAllModifiesStmt(std::unordered_map<int, std::set<std::string>> allStmtToVars) {
	modifiesStmtTable.addAllManyToManyRelationships(allStmtToVars);
}

//SP modifies procedure-variable
void PKB::addAllModifiesProc(std::unordered_map<std::string, std::set<std::string>> allProcToVars) {
	modifiesProcTable.addAllManyToManyRelationships(allProcToVars);
}

//add calls
void PKB::addAllCalls(std::unordered_map<std::string, std::set<std::string>> allCallertoCallees) {
	callsTable.addAllManyToManyRelationships(allCallertoCallees);
}

//add calls*
void PKB::addAllCallsStar(std::unordered_map<std::string, std::set<std::string>> allCallertoCallees) {
	callsStarTable.addAllManyToManyRelationships(allCallertoCallees);
}

//add next
void PKB::addAllNext(std::unordered_map<int, std::set<int>> allPreviousToNexts) {
	nextTable.addAllManyToManyRelationships(allPreviousToNexts);
}

//add next*
void PKB::addAllNextStar(std::unordered_map<int, std::set<int>> allPreviousToNexts) {
	nextStarTable.addAllManyToManyRelationships(allPreviousToNexts);
	nextStarTable.setToReady();
}

//add affects
void PKB::addAllAffects(std::unordered_map<int, std::set<int>> allModifierToUsers) {
	affectsTable.addAllManyToManyRelationships(allModifierToUsers);
	affectsTable.setToReady();
}

//add affects*
void PKB::addAllAffectsStar(std::unordered_map<int, std::set<int>> allModifierToUsers) {
	affectsStarTable.addAllManyToManyRelationships(allModifierToUsers);
	affectsStarTable.setToReady();
}

//add with (read)
void PKB::addAllWithRead(unordered_map<int, std::string> readLineNumToVarName) {
	withReadTable.addAllOneToOneRelationships(readLineNumToVarName);
}

//add with (print)
void PKB::addAllWithPrint(unordered_map<int, std::string> printLineNumToVarName) {
	withPrintTable.addAllOneToOneRelationships(printLineNumToVarName);
}

//add with (call)
void PKB::addAllWithCall(unordered_map<int, std::string> callLineNumToProcName) {
	withCallTable.addAllOneToOneRelationships(callLineNumToProcName);
}

//add assign pattern
void PKB::addAllAssignPatterns(std::unordered_map<std::string, std::set<Line>> lhsVarToRhsLine) {
	assignPatternTable.addAllAssignPatterns(lhsVarToRhsLine);
}

//add while pattern
void PKB::addAllWhilePatterns(std::unordered_map<std::string, std::set<Line>> controlVarToWhileLine) {
	whilePatternTable.addAllWhileOrIfPatterns(controlVarToWhileLine);
}

//add if pattern
void PKB::addAllIfPatterns(std::unordered_map<std::string, std::set<Line>> controlVarToIfLine) {
	ifPatternTable.addAllWhileOrIfPatterns(controlVarToIfLine);
}

//GET
//get procedure
std::set<std::string> PKB::getAllProcNames() {
	return procTable.getAllEntities();
}

//get variable
std::set<std::string> PKB::getAllVarNames() {
	return varTable.getAllEntities();
}

//get constant
std::set<std::string> PKB::getAllConstVals() {
	return constTable.getAllEntities();
}

//get line
std::set<Line> PKB::getAllLines() {
	return lineTable.getAllEntities();
}

//get statement
std::set<int> PKB::getAllStmtNums() {
	return stmtTable.getAllStatementNumbers();
}

std::set<int> PKB::getAllStmtNumsByType(KeywordsEnum stmtType) {
	return stmtTable.getAllStatementNumbersByType(stmtType);
}

//get follows
int PKB::getFollowsLeaderNum(int followerNum, int invalidLeaderNum) {
	return followsTable.getLeft(followerNum, invalidLeaderNum);
}

int PKB::getFollowsFollowerNum(int leaderNum, int invalidFollowerNum) {
	return followsTable.getRight(leaderNum, invalidFollowerNum);
}

bool PKB::areInFollowsRelationship(int leaderNum, int followerNum) {
	return followsTable.inOneToOneRelationship(leaderNum, followerNum);
}

bool PKB::isFollowsEmpty() {
	return followsTable.isEmpty();
}

bool PKB::isFollowsLeaderEmpty() {
	return followsTable.isRightToLeftMapEmpty();
}

bool PKB::isFollowsFollowerEmpty() {
	return followsTable.isLeftToRightMapEmpty();
}

//get follows*
std::set<int> PKB::getFollowsStarLeaderNums(int followerNum) {
	return followsStarTable.getAllLefts(followerNum);
}

std::set<int> PKB::getFollowsStarFollowerNums(int leaderNum) {
	return followsStarTable.getAllRights(leaderNum);
}

bool PKB::areInFollowsStarRelationship(int leaderNum, int followerNum) {
	return followsStarTable.inManyToManyRelationship(leaderNum, followerNum);
}

bool PKB::isFollowsStarEmpty() {
	return followsStarTable.isEmpty();
}

bool PKB::isFollowsStarLeaderEmpty() {
	return followsStarTable.isRightToAllLeftsMapEmpty();
}

bool PKB::isFollowsStarFollowerEmpty() {
	return followsStarTable.isLeftToAllRightsMapEmpty();
}

//get parent
int PKB::getParentParentNum(int childNum, int invalidParentNum) {
	return parentTable.getLeft(childNum, invalidParentNum);
}

std::set<int> PKB::getParentChildNums(int parentNum) {
	return parentTable.getAllRights(parentNum);
}

bool PKB::areInParentRelationship(int parentNum, int childNum) {
	return parentTable.inOneToOneRelationship(parentNum, childNum);
}

bool PKB::isParentEmpty() {
	return parentTable.isEmpty();
}

bool PKB::isParentParentEmpty() {
	return parentTable.isRightToLeftMapEmpty();
}

bool PKB::isParentChildEmpty() {
	return parentTable.isLeftToAllRightsMapEmpty();
}

//get parent*
std::set<int> PKB::getParentStarParentNums(int childNum) {
	return parentStarTable.getAllLefts(childNum);
}

std::set<int> PKB::getParentStarChildNums(int parentNum) {
	return parentStarTable.getAllRights(parentNum);
}

bool PKB::areInParentStarRelationship(int parentNum, int childNum) {
	return parentStarTable.inManyToManyRelationship(parentNum, childNum);
}

bool PKB::isParentStarEmpty() {
	return parentStarTable.isEmpty();
}

bool PKB::isParentStarParentEmpty() {
	return parentStarTable.isRightToAllLeftsMapEmpty();
}

bool PKB::isParentStarChildEmpty() {
	return parentStarTable.isLeftToAllRightsMapEmpty();
}

//get uses statement-variable
std::unordered_map<int, std::set<std::string>> PKB::getStmtUsesVarsMap() {
	return usesStmtTable.getLeftToAllRightsMap();
}

std::set<std::string> PKB::getUsesVarsFromStmt(int stmtNum) {
	return usesStmtTable.getAllRights(stmtNum);
}

std::set<int> PKB::getUsesStmtsFromVar(std::string varName) {
	return usesStmtTable.getAllLefts(varName);
}

bool PKB::areInUsesStmtRelationship(int stmtNum, std::string varName) {
	return usesStmtTable.inManyToManyRelationship(stmtNum, varName);
}

//get uses procedure-variable
std::set<std::string> PKB::getUsesVarsFromProc(std::string procName) {
	return usesProcTable.getAllRights(procName);
}

std::set<std::string> PKB::getUsesProcsFromVar(std::string varName) {
	return usesProcTable.getAllLefts(varName);
}

bool PKB::areInUsesProcRelationship(std::string procName, std::string varName) {
	return usesProcTable.inManyToManyRelationship(procName, varName);
}

//get modifies statement-variable
std::unordered_map<int, std::set<std::string>> PKB::getStmtModifiesVarsMap() {
	return modifiesStmtTable.getLeftToAllRightsMap();
}

std::set<std::string> PKB::getModifiesVarsFromStmt(int stmtNum) {
	return modifiesStmtTable.getAllRights(stmtNum);
}

std::set<int> PKB::getModifiesStmtsFromVar(std::string varName) {
	return modifiesStmtTable.getAllLefts(varName);
}

bool PKB::areInModifiesStmtRelationship(int stmtNum, std::string varName) {
	return modifiesStmtTable.inManyToManyRelationship(stmtNum, varName);
}

//get modifies procedure-variable
std::set<std::string> PKB::getModifiesVarsFromProc(std::string procName) {
	return modifiesProcTable.getAllRights(procName);
}

std::set<std::string> PKB::getModifiesProcsFromVar(std::string varName) {
	return modifiesProcTable.getAllLefts(varName);
}

bool PKB::areInModifiesProcRelationship(std::string procName, std::string varName) {
	return modifiesProcTable.inManyToManyRelationship(procName, varName);
}

//get calls
std::set<std::string> PKB::getCallsCallerNames(std::string calleeName) {
	return callsTable.getAllLefts(calleeName);
}

std::set<std::string> PKB::getCallsCalleeNames(std::string callerName) {
	return callsTable.getAllRights(callerName);
}

bool PKB::areInCallsRelationship(std::string callerName, std::string calleeName) {
	return callsTable.inManyToManyRelationship(callerName, calleeName);
}

bool PKB::isCallsEmpty() {
	return callsTable.isEmpty();
}

bool PKB::isCallsCallerEmpty() {
	return callsTable.isRightToAllLeftsMapEmpty();
}

bool PKB::isCallsCalleeEmpty() {
	return callsTable.isLeftToAllRightsMapEmpty();
}

//get calls*
std::set<std::string> PKB::getCallsStarCallerNames(std::string calleeName) {
	return callsStarTable.getAllLefts(calleeName);
}

std::set<std::string> PKB::getCallsStarCalleeNames(std::string callerName) {
	return callsStarTable.getAllRights(callerName);
}

bool PKB::areInCallsStarRelationship(std::string callerName, std::string calleeName) {
	return callsStarTable.inManyToManyRelationship(callerName, calleeName);
}

bool PKB::isCallsStarEmpty() {
	return callsStarTable.isEmpty();
}

bool PKB::isCallsStarCallerEmpty() {
	return callsStarTable.isRightToAllLeftsMapEmpty();
}

bool PKB::isCallsStarCalleeEmpty() {
	return callsStarTable.isLeftToAllRightsMapEmpty();
}

//get next
std::unordered_map<int, std::set<int>> PKB::getPreviousToNextStmtsMap() {
	return nextTable.getLeftToAllRightsMap();
}

std::set<int> PKB::getPreviousStmtNums(int nextStmtNum) {
	return nextTable.getAllLefts(nextStmtNum);
}

std::set<int> PKB::getNextStmtNums(int previousStmtNum) {
	return nextTable.getAllRights(previousStmtNum);
}

bool PKB::areInNextRelationship(int previousStmtNum, int nextStmtNum) {
	return nextTable.inManyToManyRelationship(previousStmtNum, nextStmtNum);
}

bool PKB::isNextEmpty() {
	return nextTable.isEmpty();
}

bool PKB::isPreviousStmtEmpty() {
	return nextTable.isRightToAllLeftsMapEmpty();
}

bool PKB::isNextStmtEmpty() {
	return nextTable.isLeftToAllRightsMapEmpty();
}

//get next*
std::set<int> PKB::getStarPreviousStmtNums(int nextStmtNum) {
	if (nextStarTable.checkReadiness()) {
		return nextStarTable.getAllLefts(nextStmtNum);
	}
	return nextStarTable.getAllLefts(nextStmtNum);//TODO
}

std::set<int> PKB::getStarNextStmtNums(int previousStmtNum) {
	if (nextStarTable.checkReadiness()) {
		return nextStarTable.getAllRights(previousStmtNum);
	}
	return nextStarTable.getAllRights(previousStmtNum);//TODO
}

bool PKB::areInNextStarRelationship(int previousStmtNum, int nextStmtNum) {
	if (nextStarTable.checkReadiness()) {
		return nextStarTable.inManyToManyRelationship(previousStmtNum, nextStmtNum);
	}
	return nextStarTable.inManyToManyRelationship(previousStmtNum, nextStmtNum);//TODO
}

bool PKB::isNextStarEmpty() {
	return nextStarTable.isEmpty();
}

bool PKB::isStarPreviousStmtEmpty() {
	return nextStarTable.isRightToAllLeftsMapEmpty();
}

bool PKB::isStarNextStmtEmpty() {
	return nextStarTable.isLeftToAllRightsMapEmpty();
}

void PKB::clearNextStar() {
	nextStarTable.clearMaps();
	nextStarTable.setToUnready();
}

//get affects
std::set<int> PKB::getAffectsModifierStmtNums(int userStmtNum) {
	if (affectsTable.checkReadiness()) {
		return affectsTable.getAllLefts(userStmtNum);
	}
	return affectsTable.getAllLefts(userStmtNum);//TODO
}

std::set<int> PKB::getAffectsUserStmtNums(int modifierStmtNum) {
	if (affectsTable.checkReadiness()) {
		return affectsTable.getAllRights(modifierStmtNum);
	}
	return affectsTable.getAllRights(modifierStmtNum);//TODO
}

bool PKB::areInAffectsRelationship(int modifierStmtNum, int userStmtNum) {
	if (affectsTable.checkReadiness()) {
		return affectsTable.inManyToManyRelationship(modifierStmtNum, userStmtNum);
	}
	return affectsTable.inManyToManyRelationship(modifierStmtNum, userStmtNum);//TODO
}

bool PKB::isAffectsEmpty() {
	return affectsTable.isEmpty();
}

bool PKB::isAffectsModifierStmtEmpty() {
	return affectsTable.isRightToAllLeftsMapEmpty();
}

bool PKB::isAffectsUserStmtEmpty() {
	return affectsTable.isLeftToAllRightsMapEmpty();
}

void PKB::clearAffects() {
	affectsTable.clearMaps();
	affectsTable.setToUnready();
}

//get affects*
std::set<int> PKB::getAffectsStarModifierStmtNums(int userStmtNum) {
	if (affectsStarTable.checkReadiness()) {
		return affectsStarTable.getAllLefts(userStmtNum);
	}
	return affectsStarTable.getAllLefts(userStmtNum);//TODO
}

std::set<int> PKB::getAffectsStarUserStmtNums(int modifierStmtNum) {
	if (affectsStarTable.checkReadiness()) {
		return affectsStarTable.getAllRights(modifierStmtNum);
	}
	return affectsStarTable.getAllRights(modifierStmtNum);//TODO
}

bool PKB::areInAffectsStarRelationship(int modifierStmtNum, int userStmtNum) {
	if (affectsStarTable.checkReadiness()) {
		return affectsStarTable.inManyToManyRelationship(modifierStmtNum, userStmtNum);
	}
	return affectsStarTable.inManyToManyRelationship(modifierStmtNum, userStmtNum);//TODO
}

bool PKB::isAffectsStarEmpty() {
	return affectsStarTable.isEmpty();
}

bool PKB::isAffectsStarModifierStmtEmpty() {
	return affectsStarTable.isRightToAllLeftsMapEmpty();
}

bool PKB::isAffectsStarUserStmtEmpty() {
	return affectsStarTable.isLeftToAllRightsMapEmpty();
}

void PKB::clearAffectsStar() {
	affectsStarTable.clearMaps();
	affectsStarTable.setToUnready();
}

//get with (read)
std::string PKB::getWithReadVarName(int readLineNum, std::string invalidVarName) {
	return withReadTable.getRight(readLineNum, invalidVarName);
}

//get with (print)
std::string PKB::getWithPrintVarName(int printLineNum, std::string invalidVarName) {
	return withPrintTable.getRight(printLineNum, invalidVarName);
}

//get with (call)
std::string PKB::getWithCallProcName(int callLineNum, std::string invalidProcName) {
	return withCallTable.getRight(callLineNum, invalidProcName);
}

//get assign pattern
std::string PKB::getAssignVarFromStmt(int assignStmtNum) {
	return assignPatternTable.getVarFromStmt(assignStmtNum);
}

std::set<int> PKB::getAssignStmtsFromVar(std::string lhsVarName) {
	return assignPatternTable.getStmtsFromVar(lhsVarName);
}

std::set<std::vector<std::string>> PKB::getAssignExprsFromStmt(int assignStmtNum) {
	return assignPatternTable.getExprsFromStmt(assignStmtNum);
}

std::set<int> PKB::getAssignStmtsFromExpr(std::vector<std::string> rhsExpr) {
	return assignPatternTable.getStmtsFromExpr(rhsExpr);
}

std::set<std::vector<std::string>> PKB::getAssignExprsFromVar(std::string lhsVarName) {
	return assignPatternTable.getExprsFromVar(lhsVarName);
}

std::set<std::string> PKB::getAssignVarsFromExpr(std::vector<std::string> rhsExpr) {
	return assignPatternTable.getVarsFromExpr(rhsExpr);
}

//get while pattern
std::set<int> PKB::getWhileStmtsWithVars() {
	return whilePatternTable.getAllStmts();
}

std::set<int> PKB::getWhileStmtsFromVar(std::string controlVarName) {
	return whilePatternTable.getStmtsFromVar(controlVarName);
}

std::set<std::string> PKB::getWhileVarsFromStmt(int whileStmtNum) {
	return whilePatternTable.getVarsFromStmt(whileStmtNum);
}

//get if pattern
std::set<int> PKB::getIfStmtsWithVars() {
	return ifPatternTable.getAllStmts();
}

std::set<int> PKB::getIfStmtsFromVar(std::string controlVarName) {
	return ifPatternTable.getStmtsFromVar(controlVarName);
}

std::set<std::string> PKB::getIfVarsFromStmt(int ifStmtNum) {
	return ifPatternTable.getVarsFromStmt(ifStmtNum);
}
