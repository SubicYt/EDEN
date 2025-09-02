#ifndef AST_H
#define AST_H

#include <iostream>
#include <list>
#include <algorithm>
#include <memory>
#include <vector>

//var let x = 45; will not return a value
// x = 45, assignment, will return value

enum NodeType{
    PROGRAM,
    NUMERIC_LITERAL,
    IDENTIFIER,
    BINARY_EXPRESSION
};

struct statement{
    NodeType statementKind;

    statement(NodeType nodetype){
        statementKind = nodetype; 
    }

    //virtual deconstructor
    virtual ~statement() = default;
};

struct program : statement{
    //vector of unique statement objects
    //prevents object slicing
    // see notes doc for explanation
    std::vector<std::unique_ptr<statement>> programBody;
    
    //program constructors 
    program() : statement(NodeType::PROGRAM){}
};

struct expr : statement{
    expr(NodeType node_type) : statement(node_type){};
};

struct binaryExpression : expr{
    //left pointer, right pointer, operation
    std::unique_ptr<expr> left;
    std::unique_ptr<expr> right;
    std::string operation;

    binaryExpression(std::unique_ptr<expr>left_pointer, 
        std::unique_ptr<expr>right_pointer, std::string oper_str) : 
        expr(NodeType::BINARY_EXPRESSION){
            //std::move effectively moves resources from var to var
            left = std::move(left_pointer);
            right = std::move(right_pointer);
            operation = std::move(oper_str);
        }
};

struct identifier : expr{
    std::string symbol;
    identifier(std::string s) : expr(NodeType::IDENTIFIER){
        symbol = std::move(s);
    }
};

struct numericLiteral : expr{
    double value;
    numericLiteral(double val) : expr(NodeType::NUMERIC_LITERAL){
        value = val;
    }
};

#endif // AST_H