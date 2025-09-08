#ifndef ASH_H
#define ASH_H

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "lexer.h"
#include <variant>

enum nodeType{
    PROGRAM,
    STATEMENT,
    IDENTIFIER_EXPR,
    BINARY_EXPR,
    NUMERIC_LITERAL
};

/*
everything is a statement
Program extends from a statement

Design practice would be to make an expression its own class extedning from base  class statement

Additionally an expression extends from a statement
An identifier and numeric literal extend from expression

hope and pray bro... hope and pray
*/

struct statement{
    nodeType statementKind;
    std::string value;

    statement(nodeType kind, std::string val){
        statementKind = kind;
        value = val;
    }
    ~statement() = default; // include virtual destructor
};

struct program : public statement{
    //a program is made up of a vector of unique pointers of statements
    //this is going to prevent object slicing.

    //potential usecase.
    std::variant<nodeType, std::string> progamValues;

    std::vector<std::unique_ptr<statement>> programBody;

    program() : statement(PROGRAM, ""){};
    /*
    Kinda like
    progarm(){
        statementKind = PROGRAM;
    }
    */
};

struct expr : public statement{
    //an expression is a statement
    //an expression can be an identifier, binary expression, or numeric literal

    //value of the expression
    //for binary expression this is operator
    std::string nodeValue; 
    //variant can hold either a nodeType (for operators) or a string (for identifiers)
    expr(nodeType kind, std::variant<nodeType, std::string> val = "") : 
    statement(kind, nodeValue) {
    };

    /*
    Just for my own understanding its kinda like this 

    expr(nodeType kind, std::variant<nodeType, std::string> val){
        statementKind = kind;
        nodeValue = val;
    }
    */
    ~expr() = default; // include virtual destructor
};

struct identifier : public expr{
    std::string symbol;

    identifier(std::string& sym) : expr(IDENTIFIER_EXPR){
        symbol = std::move(sym);
    }
    //no virtual destructor needed since expr already has one
};

struct binaryExpression : public expr{
    std::unique_ptr<expr> left;
    std::unique_ptr<expr> right;
    std::string operation;

    binaryExpression(std::unique_ptr<expr> l, std::unique_ptr<expr> r, 
    std::string& op) : expr(BINARY_EXPR){
        left = std::move(l);
        right = std::move(r);
        operation = std::move(op);
    }
};

struct numericLiteral : public expr{
    double value;
    numericLiteral(double val) : expr(NUMERIC_LITERAL){
        value = val;
    }
};

//parser class to be implemented.
class Parser{
private:
    //determines if end of file for while loop
    bool notEOF();
    //keeps track of index zero of tokens list
    Token at();
    //returns previous token and increments to the next
    Token advance();
    std::unique_ptr<statement> parse_statement();
    std::unique_ptr<expr> parse_expr();
    std::unique_ptr<expr> parse_primaryExpr();
    std::unique_ptr<expr> parse_binaryExpr();

public:
    std::vector<Token> tokenlist;
    //takes in vect of tokens to produce ast
    Parser(std::vector<Token> srcTokens);
    std::unique_ptr<program> produceAST();
};

#endif // ASH_H
