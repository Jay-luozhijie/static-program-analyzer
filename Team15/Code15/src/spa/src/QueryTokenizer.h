#include <map>
#include <memory>
#include <regex>
#include <string>
#include <utility>
#include "SuchThatClause.h"
#include "SelectClause.h"
#include "PatternClause.h"
#include "PQLSyntaxChecker.h"
#include "exceptions/PQLSyntaxError.h"

#pragma once


class QueryTokenizer {
public:
	std::pair<std::string, std::string> tokenizeQuery(std::string input);
	void tokenizeClauses(std::string input,
		SelectClause& selectClause,
		std::vector<SuchThatClause>& suchThatClauses,
		std::vector<PatternClause>& patternClauses);
	std::multimap<std::string, std::string> tokenizeDeclaration(std::string declaration);
	void tokenizeSelectClause(std::string& input, SelectClause& selectClause);
	void tokenizeSuchThatClause(std::string& input, std::vector<SuchThatClause>& suchThatClauses);
	void tokenizePatternClause(std::string& input, std::vector<PatternClause>& patternClauses);

private:
    PQLSyntaxChecker syntaxChecker = PQLSyntaxChecker();
	std::string trim(std::string input);
	// std::multimap<std::string, std::string> tokenizeDeclaration(std::string input);

	std::string extractKeyword(std::string &input);
	std::string getType(std::string &input);
    std::vector<std::string> tokenizeCsv(std::string);

};