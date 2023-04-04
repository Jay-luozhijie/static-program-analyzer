#include <string>
#include <regex>
#include <unordered_set>
#include <algorithm>
#include <iterator>
#include <set>
#include "exceptions/PQLSyntaxError.h"
#include "pkb/include/PKB.h"

#pragma once
enum Relationship
{
    MODIFIES,
    USES,
    CALLS,
    CALLS_STAR,
    AFFECTS,
    AFFECTS_STAR,
    NEXT,
    NEXT_STAR,
    PARENT,
    PARENT_STAR,
    FOLLOWS,
    FOLLOWS_STAR,
    USES_S,
    USES_P,
    MODIFIES_S,
    MODIFIES_P,
    INVALID_RELATIONSHIP
};

enum ReferenceType
{
    SYNONYM,
    INTEGER,
    UNDERSCORE,
    EXPR,
    QUOTED_IDENT,
    INVALID,
    UNDERSCORED_EXPR,
};

enum DesignEntity
{
    PROCEDURE_ENTITY,
    STMT_ENTITY,
    READ_ENTITY,
    PRINT_ENTITY,
    ASSIGN_ENTITY,
    CALL_ENTITY,
    WHILE_ENTITY,
    IF_ENTITY,
    VARIABLE_ENTITY,
    CONSTANT_ENTITY,
    INVALID_ENTITY
};

enum ClauseType
{
    WITH,
    SUCH_THAT,
    SELECT,
    PATTERN
};

class Utility
{
public:
    inline static const std::string assign = "assign";
    inline static const std::string variable = "variable";
    inline static const std::string procedure = "procedure";
    inline static const std::string print = "print";
    inline static const std::string read = "read";
    inline static const std::string constant = "constant";
    inline static const std::string whileStmt = "while";
    inline static const std::string ifStmt = "if";
    inline static const std::string call = "call";
    inline static const std::string stmt = "stmt";

    inline static const std::unordered_set<std::string> designEntitySet = {procedure, stmt, read, print,
                                                                           assign, call, whileStmt, ifStmt, variable, constant};
    inline static const std::unordered_set<std::string> attrNameSet = {"procName", "varName", "value", "stmt#"};
    inline static const std::string synonymFormat = "[a-zA-Z][a-zA-Z0-9]*";
    inline static const std::string integerFormat = "[1-9][0-9]*";
    inline static const std::string quotedIdentFormat = "\"[a-zA-Z][a-zA-Z0-9]*\"";
    inline static const std::string underscoredExprFormat = "_\"[\\s\\S]*\"_";
    inline static const std::string exprFormat = "\"[\\s\\S]*\"";

    inline static const std::string whiteSpaces = " \t\n";
    inline static const std::string ending = ".";
    inline static const std::string quote = "\"";
    inline static const std::string underscore = "_";
    inline static const std::string expr = "expr";
    inline static const std::string underscored_expr = "underscored_expr";
    inline static const std::string quoted_ident = "quoted_ident";
    inline static const std::string integer = "integer";
    inline static const std::string synonym = "synonym";
    inline static const std::string invalid = "Invalid";

    inline static const std::string parent = "Parent";
    inline static const std::string parentStar = "Parent*";
    inline static const std::string follows = "Follows";
    inline static const std::string followsStar = "Follows*";
    inline static const std::string modifiesS = "ModifiesS";
    inline static const std::string modifiesP = "ModifiesP";
    inline static const std::string modifies = "Modifies";
    inline static const std::string usesS = "UsesS";
    inline static const std::string usesP = "UsesP";
    inline static const std::string uses = "Uses";
    inline static const std::string calls = "Calls";
    inline static const std::string callsStar = "Calls*";
    inline static const std::string next = "Next";
    inline static const std::string nextStar = "Next*";
    inline static const std::string affects = "Affects";
    inline static const std::string affectsStar = "Affects*";

    inline static const std::string procName = "procName";
    inline static const std::string varName = "varName";
    inline static const std::string stmtNum = "stmt#";
    inline static const std::string value = "value";

    inline static const Keywords keywords = Keywords();

    inline static const ReferenceType getEnumReferenceType(std::string input)
    {
        if (std::regex_match(input, std::regex(synonymFormat)))
        {
            return SYNONYM;
        }
        else if (std::regex_match(input, std::regex(integerFormat)))
        {
            return INTEGER;
        }
        else if (std::regex_match(input, std::regex(quotedIdentFormat)))
        {
            return QUOTED_IDENT;
        }
        else if (std::regex_match(input, std::regex(underscoredExprFormat)))
        {
            return UNDERSCORED_EXPR;
        }
        else if (std::regex_match(input, std::regex(exprFormat)))
        {
            return EXPR;
        }
        else if (std::regex_match(input, std::regex(underscore)))
        {
            return UNDERSCORE;
        }
        else
        {
            return INVALID;
        }
    };

    inline static const std::string getReferenceType(std::string input)
    {
        if (std::regex_match(input, std::regex(synonymFormat)))
        {
            return synonym;
        }
        else if (std::regex_match(input, std::regex(integerFormat)))
        {
            return integer;
        }
        else if (std::regex_match(input, std::regex(quotedIdentFormat)))
        {
            return quoted_ident;
        }
        else if (std::regex_match(input, std::regex(underscoredExprFormat)))
        {
            return underscored_expr;
        }
        else if (std::regex_match(input, std::regex(exprFormat)))
        {
            return expr;
        }
        else if (std::regex_match(input, std::regex(underscore)))
        {
            return underscore;
        }
        else
        {
            return invalid;
        }
    };

    // remove exprToTrim in the front and end
    inline static const std::string trim(std::string input, std::string exprToTrim)
    {
        std::string trimmed = input;
        std::size_t firstPos = trimmed.find_first_not_of(exprToTrim);
        // trim left
        if (firstPos != std::string::npos)
        {
            trimmed = trimmed.substr(firstPos);
        }
        // trim right
        std::size_t lastPos = trimmed.find_last_not_of(exprToTrim);
        if (lastPos != std::string::npos)
        {
            trimmed = trimmed.substr(0, lastPos + 1);
        }
        return trimmed;
    };

    inline static const std::string trim_double_quotes(std::string s)
    {
        if (s.length() >= 2 && s[0] == '"' && s[s.length() - 1] == '"')
        {
            return s.substr(1, s.length() - 2);
        }
        return s;
    }


    inline static const std::set<std::string> getResultFromPKB(PKB &pkb, std::string DeType)
    {
        std::set<std::string> ret;
        if (DeType == constant)
        {
            ret = pkb.getAllConstVals();
        }
        else if (DeType == procedure)
        {
            ret = pkb.getAllProcNames();
        }
        else if (DeType == variable)
        {
            ret = pkb.getAllVarNames();
        }
        else
        {
            std::set<int> allStmtIntSet;

            if (DeType == stmt)
            {
                allStmtIntSet = pkb.getAllStmtNums();
            }
            else if (DeType == assign)
            {
                allStmtIntSet = pkb.getAllStmtNumsByType(ASSIGN);
            }
            else
            {
                allStmtIntSet = pkb.getAllStmtNumsByType(getKeyWordsFromEntity(DeType));
            }

            for (int stmtNum : allStmtIntSet)
            {
                ret.insert(to_string(stmtNum));
            }
        }
        return ret;
    }
    inline static const DesignEntity getDesignEntityFromString(std::string designEntity)
    {
        if (designEntity == procedure)
        {
            return PROCEDURE_ENTITY;
        }
        else if (designEntity == stmt)
        {
            return STMT_ENTITY;
        }
        else if (designEntity == constant)
        {
            return CONSTANT_ENTITY;
        }
        else if (designEntity == variable)
        {
            return VARIABLE_ENTITY;
        }
        else if (designEntity == read)
        {
            return READ_ENTITY;
        }
        else if (designEntity == print)
        {
            return PRINT_ENTITY;
        }
        else if (designEntity == ifStmt)
        {
            return IF_ENTITY;
        }
        else if (designEntity == whileStmt)
        {
            return WHILE_ENTITY;
        }
        else if (designEntity == call)
        {
            return CALL_ENTITY;
        }
        else if (designEntity == assign)
        {
            return ASSIGN_ENTITY;
        }
        else
        {
            return INVALID_ENTITY;
        }
    }

    inline static const Relationship getRelationshipFromString(std::string relationship)
    {
        if (relationship == modifies)
        {
            return MODIFIES;
        }
        else if (relationship == uses)
        {
            return USES;
        }
        else if (relationship == calls)
        {
            return CALLS;
        }
        else if (relationship == callsStar)
        {
            return CALLS_STAR;
        }
        else if (relationship == follows)
        {
            return FOLLOWS;
        }
        else if (relationship == followsStar)
        {
            return FOLLOWS_STAR;
        }
        else if (relationship == parent)
        {
            return PARENT;
        }
        else if (relationship == parentStar)
        {
            return PARENT_STAR;
        }
        else if (relationship == affects)
        {
            return AFFECTS;
        }
        else if (relationship == affectsStar)
        {
            return AFFECTS_STAR;
        }
        else if (relationship == nextStar)
        {
            return NEXT_STAR;
        }
        else if (relationship == next)
        {
            return NEXT;
        }
        else
        {
            return INVALID_RELATIONSHIP;
        }
    }

    inline static const KeywordsEnum getKeyWordsFromEntity(std::string designEntity) {
        if (designEntity == procedure)
        {
            return PROCEDURE;
        }
        else if (designEntity == stmt)
        {
            return STMT;
        }
        else if (designEntity == constant)
        {
            return CONSTANT;
        }
        else if (designEntity == variable)
        {
            return VARIABLE;
        }
        else if (designEntity == read)
        {
            return READ;
        }
        else if (designEntity == print)
        {
            return PRINT;
        }
        else if (designEntity == ifStmt)
        {
            return IF;
        }
        else if (designEntity == whileStmt)
        {
            return WHILE;
        }
        else if (designEntity == call)
        {
            return CALL;
        }
        else if (designEntity == assign)
        {
            return ASSIGN_STMT;
        }
        else
        {
            return NONE;
        }
    }
};
