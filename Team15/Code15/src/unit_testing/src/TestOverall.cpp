#include "pkb/include/PKB.h"
#include "QPS/include/evaluator/PQLEvaluator.h"
#include "QPS/include/model/Result.h"
#include "QPS/include/model/ResultTable.h"
#include "QPS/include/evaluator/FollowsHandler.h"
#include "QPS/include/PQLDriver.h"
#include "source_processor/include/SourceProcessor.h"

#include "catch.hpp"
using namespace std;

set<string> testDriver(std::string filename, std::string queryStr) {
    SourceProcessor sourceProcessor = SourceProcessor();
    PKB pkb = PKB();
    sourceProcessor.parseProgram(filename);
    sourceProcessor.storeDataInPKB(&pkb);

    PQLDriver pqlDriver = PQLDriver(pkb);
    set<string> result = pqlDriver.processPQL(queryStr);
    return result;
}

TEST_CASE("Overall test : Sample_source2.txt 0") {
    // Enter source of SIMPLE code
    string filename = "../../../../../../Tests15/Sample_source2.txt"; /*"../../../../Tests15/Sample_source2.txt";*/
    string queryStr = "constant c; Select c";

    set<string> result = testDriver(filename, queryStr);
    
    set<string> expectedResult = { "2", "3", "5" };
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : container_source.txt 1") {
    // Enter source of SIMPLE code
    string filename = "../../../../../../Tests15/container_source.txt"; /*"../../../../Tests15/Sample_source2.txt";*/
    string queryStr = "procedure p; Select p";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "proc1", "proc2" };
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : container_source.txt 2") {
    // Enter source of SIMPLE code
    string filename = "../../../../../../Tests15/container_source.txt"; /*"../../../../Tests15/Sample_source2.txt";*/
    string queryStr = "call cl; Select cl such that Follows(19, cl)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "21" };
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : container_source.txt 3") {
    // Enter source of SIMPLE code
    string filename = "../../../../../../Tests15/container_source.txt"; /*"../../../../Tests15/Sample_source2.txt";*/
    string queryStr = "call cl; Select cl such that Follows * (2, cl)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "21" };
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : container_source.txt 4") {
    // Enter source of SIMPLE code
    string filename = "../../../../../../Tests15/container_source.txt"; /*"../../../../Tests15/Sample_source2.txt";*/
    string queryStr = "if i; Select i such that Follows(12, i)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "13" };
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : container_source.txt 5") {
    // Enter source of SIMPLE code
    string filename = "../../../../../../Tests15/container_source.txt"; /*"../../../../Tests15/Sample_source2.txt";*/
    string queryStr = "while w; Select w such that Follows(19, w)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "18" };
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : container_source.txt 6") {
    // Enter source of SIMPLE code
    string filename = "../../../../../../Tests15/container_source.txt"; /*"../../../../Tests15/Sample_source2.txt";*/
    string queryStr = "constant c; Select c";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : container_source.txt 7") {
    // Enter source of SIMPLE code
    string filename = "../../../../../../Tests15/container_source.txt"; /*"../../../../Tests15/Sample_source2.txt";*/
    string queryStr = "assign a; Select a pattern a(\"w\", _\"b + c\"_)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "14", "22" };
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : container_source.txt 8") {
    // Enter source of SIMPLE code
    string filename = "../../../../../../Tests15/container_source.txt"; /*"../../../../Tests15/Sample_source2.txt";*/
    string queryStr = "assign a; Select a pattern a(_, _\"a * b\"_)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "15" };
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : container_source.txt 9") {
    // Enter source of SIMPLE code
    string filename = "../../../../../../Tests15/container_source.txt"; /*"../../../../Tests15/Sample_source2.txt";*/
    string queryStr = "assign a; Select a pattern a(_, _\"c * d\"_)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "none" };
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : container_source.txt 10") {
    // Enter source of SIMPLE code
    string filename = "../../../../../../Tests15/container_source.txt"; /*"../../../../Tests15/Sample_source2.txt";*/
    string queryStr = "assign a; Select a pattern a(\"count\", \"count\")";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "20" };
    REQUIRE(result == expectedResult);
}






TEST_CASE("Overall test : more_nested_container_source.txt 1") {
    // Enter source of SIMPLE code
    string filename = "../../../../../../Tests15/more_nested_container_source.txt"; /*"../../../../Tests15/Sample_source2.txt";*/
    string queryStr = "stmt s; Select s such that Parent * (5, s)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "6", "7", "8", "9", "10", "12", "13", "15", "19", "22"};
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : more_nested_container_source.txt 2") {
    // Enter source of SIMPLE code
    string filename = "../../../../../../Tests15/more_nested_container_source.txt"; /*"../../../../Tests15/Sample_source2.txt";*/
    string queryStr = "stmt s; Select s such that Parent * (s, 15)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "5", "6", "7", "8", "12" };
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : more_nested_container_source.txt 3") {
    // Enter source of SIMPLE code
    string filename = "../../../../../../Tests15/more_nested_container_source.txt"; /*"../../../../Tests15/Sample_source2.txt";*/
    string queryStr = "stmt s; Select s such that Parent * (6, s)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "7", "8", "9", "10", "12", "13", "15", "19" };
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : more_nested_container_source.txt 4") {
    // Enter source of SIMPLE code
    string filename = "../../../../../../Tests15/more_nested_container_source.txt"; /*"../../../../Tests15/Sample_source2.txt";*/
    string queryStr = "stmt s; Select s such that Parent * (s, 12)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "5", "6", "7", "8" };
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : more_nested_container_source.txt 5") {
    // Enter source of SIMPLE code
    string filename = "../../../../../../Tests15/more_nested_container_source.txt"; /*"../../../../Tests15/Sample_source2.txt";*/
    string queryStr = "stmt s; Select s such that Parent * (7, s)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "8", "9", "10", "12", "13", "15", "19"};
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : more_nested_container_source.txt 6") {
    // Enter source of SIMPLE code
    string filename = "../../../../../../Tests15/more_nested_container_source.txt"; /*"../../../../Tests15/Sample_source2.txt";*/
    string queryStr = "stmt s; Select s such that Parent * (s, 9)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "5", "6", "7", "8" };
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : more_nested_container_source.txt 7") {
    // Enter source of SIMPLE code
    string filename = "../../../../../../Tests15/more_nested_container_source.txt"; /*"../../../../Tests15/Sample_source2.txt";*/
    string queryStr = "stmt s; Select s such that Parent * (8, s)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "9", "10", "12", "13", "15" };
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : more_nested_container_source.txt 8") {
    // Enter source of SIMPLE code
    string filename = "../../../../../../Tests15/more_nested_container_source.txt"; /*"../../../../Tests15/Sample_source2.txt";*/
    string queryStr = "stmt s; Select s such that Parent * (s, 8)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "5", "6", "7" };
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : more_nested_container_source.txt 9") {
    // Enter source of SIMPLE code
    string filename = "../../../../../../Tests15/more_nested_container_source.txt"; /*"../../../../Tests15/Sample_source2.txt";*/
    string queryStr = "stmt s; Select s such that Parent * (12, s)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "13", "15" };
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : more_nested_container_source.txt 10") {
    // Enter source of SIMPLE code
    string filename = "../../../../../../Tests15/more_nested_container_source.txt"; /*"../../../../Tests15/Sample_source2.txt";*/
    string queryStr = "stmt s; Select s such that Parent * (s, 7)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "5", "6" };
    REQUIRE(result == expectedResult);
}




TEST_CASE("Overall test : nested_container_source.txt 1") {
    // Enter source of SIMPLE code
    string filename = "../../../../../../Tests15/nested_container_source.txt"; /*"../../../../Tests15/Sample_source2.txt";*/
    string queryStr = "stmt s; Select s such that Follows * (10, s)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "11", "12", "21" };
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : nested_container_source.txt 2") {
    // Enter source of SIMPLE code
    string filename = "../../../../../../Tests15/nested_container_source.txt"; /*"../../../../Tests15/Sample_source2.txt";*/
    string queryStr = "stmt s; Select s such that Follows * (s, 16)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "14", "15" };
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : nested_container_source.txt 3") {
    // Enter source of SIMPLE code
    string filename = "../../../../../../Tests15/nested_container_source.txt"; /*"../../../../Tests15/Sample_source2.txt";*/
    string queryStr = "stmt s; Select s such that Parent(12, s)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "13" };
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : nested_container_source.txt 4") {
    // Enter source of SIMPLE code
    string filename = "../../../../../../Tests15/nested_container_source.txt"; /*"../../../../Tests15/Sample_source2.txt";*/
    string queryStr = "stmt s; Select s such that Parent(13, s)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "14" };
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : nested_container_source.txt 5") {
    // Enter source of SIMPLE code
    string filename = "../../../../../../Tests15/nested_container_source.txt"; /*"../../../../Tests15/Sample_source2.txt";*/
    string queryStr = "stmt s; Select s such that Parent(s, 14)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "13" };
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : nested_container_source.txt 6") {
    // Enter source of SIMPLE code
    string filename = "../../../../../../Tests15/nested_container_source.txt"; /*"../../../../Tests15/Sample_source2.txt";*/
    string queryStr = "stmt s; Select s such that Parent(s, 13)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "12" };
    REQUIRE(result == expectedResult);
}








TEST_CASE("Overall test : no_container_source.txt, 1") {
    // Enter source of SIMPLE code
    string filename = "../../../../../../Tests15/no_container_source.txt"; /*"../../../../Tests15/Sample_source2.txt";*/
    string queryStr = "variable v; Select v";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "v", "w", "x", "y", "z", "a", "b", "c", "d", "e", "f", "g" };
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : no_container_source.txt, 2") {
    // Enter source of SIMPLE code
    string filename = "../../../../../../Tests15/no_container_source.txt"; /*"../../../../Tests15/Sample_source2.txt";*/
    string queryStr = "variable v; Select v such that Modifies(15, v)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "w" };
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : no_container_source.txt, 3") {
    // Enter source of SIMPLE code
    string filename = "../../../../../../Tests15/no_container_source.txt"; /*"../../../../Tests15/Sample_source2.txt";*/
    string queryStr = "read re; Select re such that Modifies(re, \"g\")";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "13" };
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : no_container_source.txt, 4") {
    // Enter source of SIMPLE code
    string filename = "../../../../../../Tests15/no_container_source.txt"; /*"../../../../Tests15/Sample_source2.txt";*/
    string queryStr = "variable v; Select v such that Uses(14, v)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "a", "b", "c" };
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : no_container_source.txt, 5") {
    // Enter source of SIMPLE code
    string filename = "../../../../../../Tests15/no_container_source.txt"; /*"../../../../Tests15/Sample_source2.txt";*/
    string queryStr = "stmt s; Select s such that Modifies(s, \"y\")";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "17" };
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : no_container_source.txt, 6") {
    // Enter source of SIMPLE code
    string filename = "../../../../../../Tests15/no_container_source.txt"; /*"../../../../Tests15/Sample_source2.txt";*/
    string queryStr = "stmt s; Select s such that Uses(s, \"e\")";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "18" };
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : no_container_source.txt, 7") {
    // Enter source of SIMPLE code
    string filename = "../../../../../../Tests15/no_container_source.txt"; /*"../../../../Tests15/Sample_source2.txt";*/
    string queryStr = "print pr; Select pr such that Uses(pr, \"x\")";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "19" };
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : no_container_source.txt, 8") {
    // Enter source of SIMPLE code
    string filename = "../../../../../../Tests15/no_container_source.txt"; /*"../../../../Tests15/Sample_source2.txt";*/
    string queryStr = "stmt s; Select s such that Follows(16, s)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "17" };
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : no_container_source.txt, 9") {
    // Enter source of SIMPLE code
    string filename = "../../../../../../Tests15/no_container_source.txt"; /*"../../../../Tests15/Sample_source2.txt";*/
    string queryStr = "stmt s; Select s such that Follows(s, 15)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "14" };
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : no_container_source.txt, 10") {
    // Enter source of SIMPLE code
    string filename = "../../../../../../Tests15/no_container_source.txt"; /*"../../../../Tests15/Sample_source2.txt";*/
    string queryStr = "read re; variable v; Select v such that Modifies(re, v)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "g" };
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : no_container_source.txt, 11") {
    // Enter source of SIMPLE code
    string filename = "../../../../../../Tests15/no_container_source.txt"; /*"../../../../Tests15/Sample_source2.txt";*/
    string queryStr = "print pr; variable v; Select v such that Uses(pr, v)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "x" };
    REQUIRE(result == expectedResult);
}