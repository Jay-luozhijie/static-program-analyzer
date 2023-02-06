//
// Created by Jinxin Zhao on 3/2/23.
//

#include "ClauseHandler.h"
#include "Result.h"
#include "ResultTable.h"
#include "SuchThatClause.h"
#include <string>
#include <set>
#ifndef SPA_FOLLOWSHANDLER_H
#define SPA_FOLLOWSHANDLER_H


class FollowsHandler : public ClauseHandler {

public:
    FollowsHandler(PKB& pkb);
    Result evalFollows(SuchThatClause suchThatClause, ResultTable& resultTable);
};


#endif //SPA_FOLLOWSHANDLER_H