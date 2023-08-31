# Team 15

## Target Environment

Item | Version
-|-
OS | Windows 10
Toolchain | Microsoft Visual Studio Enterprise 2019 Version 16.11.0
C++ Standard | C++17

A Static Program Analyzer (SPA) is an interactive tool that automatically answers queries about programs.

## How It Works
SPA works by:

* Analyzing a source program and extract relevant program design entities, program design abstractions, Abstract Syntax Tree (AST), and program Control Flow Graph (CFG)
Storing the information in a PKB
* Providing the user with the means to ask queries written in a formal Program Query Language (PQL)
* Processing the PQL queries based on the information found in the PKB
* Returning the results to the user

This figure shows the SPA's main components:
![alt text](https://nus-cs3203.github.io/course-website/images/fig1.png)

* The User Interface (UI) allows users to enter a source program written in SIMPLE.
* The Source Processor parses the source program. It extracts information and stores the information in the PKB.
* The UI also allows users to input PQL queries.
* The Query Processing Subsystem validates and evaluates the queries by making use of the information stored in the PKB.
* The UI then display the query results to the user.


## Design Abstraction
Program design abstractions are relationships among program design entities.
Design Abstraction	 | Relationship between
-|-
Follows/Follows* | Statements 
Parent / Parent* | Statements 
Uses / Uses* | Statement/Procedure and Variable 
Modifies / Modifies* | Statement/Procedure and Variable 
Next | Statements 
## Program Query Language
### Grammar rules:  
declaration* 'Select' synonym [ suchthat-clause ]* [ pattern-clause ]* [with-clause]* (* means 0 or more instance of the object)
### Example query: 
assign a; while w; read r1, r2; if i; const c;<br>
Select <a, r1, r2> such that <br>
Parent* (w, a) and Follows*(r1, a) and Uses(a, c) and read(r1, c) pattern a ("count", _) with a.stmt# > 5
