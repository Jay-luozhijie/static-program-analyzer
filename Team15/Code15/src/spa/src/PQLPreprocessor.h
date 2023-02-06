#include<utility>
#include<string>
#include"Query.h"
#include"QueryTokenizer.h"
#include"SelectClause.h"
#include"SuchThatClause.h"
#include"PatternClause.h"
#include "PQLSemanticCheck.h"
#include "exceptions/PQLSemanticError.h"

#pragma once

class PQLPreprocessor {
public:
	PQLPreprocessor();
	Query preprocess(std::string input);
private:
    QueryTokenizer tokenizer;
    PQLSemanticCheck semanticChecker;
};