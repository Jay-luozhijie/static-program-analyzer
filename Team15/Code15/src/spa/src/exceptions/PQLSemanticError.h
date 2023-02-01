//
// Created by Jinxin Zhao on 1/2/23.
//

#ifndef SPA_PQLSYNTAXERROR_H
#define SPA_PQLSYNTAXERROR_H

#include <iostream>
#include <string>

class PQLSemanticError : public std::exception {
private:
    std::string message;

public:
    PQLSemanticError(std::string msg) : message(msg) {}
    std::string what() {
        return message;
    }
};


#endif //SPA_PQLSYNTAXERROR_H
