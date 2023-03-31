#include "QPS/include/model/Query.h"
#include "pkb/include/PKB.h"
#include "QPS/include/model/Result.h"
#include "QPS/include/model/ResultTable.h"
#include "SelectHandler.h"
#include "QPS/include/evaluator/WithHandler.h"
#include "QPS/include/evaluator/PatternHandler.h"
#include "QPS/include/evaluator/SuchThatHandler.h"
#include "Utility.h"
#include "../model/ClauseEvalGroup.h"
#include <numeric>
#include <string>
#include <set>
#include <unordered_map>
#ifndef SPA_PQLEVALUATOR_H
#define SPA_PQLEVALUATOR_H


class PQLEvaluator {
public:
    PQLEvaluator(PKB& pkb);
    std::set<std::string> evaluate(Query query);

private:
    PKB pkb;
    // helper function
    bool isArgUsedLater(std::vector<std::string> selectedSyn, std::vector<std::string> argList, int currArgPos);
    std::vector<ClauseEvalGroup> separateEvalGroup(ClauseEvalGroup group);
    ResultTable evalGroup(ClauseEvalGroup group, bool& isEarlyExit,
    std::multimap<std::string, std::string>synonymTable, std::vector<std::string>selectedElemName);
};


#endif //SPA_PQLEVALUATOR_H
