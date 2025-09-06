//FIX AST AND PARSER STRUCTURE.

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
    IDENTIFIER_EXPR,
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
    program() : statement(PROGRAM){}
};

//Specialized expr base class derived from statement base class 
struct expr : statement{
    virtual ~expr() = default;
    expr(NodeType nodetype) : statement(nodetype){};

};

struct binaryExpression : expr{
    //left pointer, right pointer, operation
    std::unique_ptr<expr> left;
    std::unique_ptr<expr> right;
    std::string operation;

    binaryExpression(std::unique_ptr<expr>left_pointer, 
        std::unique_ptr<expr>right_pointer, std::string oper_str) : 
        expr(BINARY_EXPRESSION){
            //std::move effectively just moves resources from var to var
            left = std::move(left_pointer);
            right = std::move(right_pointer);
            operation = std::move(oper_str);
        }
};

struct identifier : expr{
    std::string symbol;
    identifier(const std::string& sym) : expr(IDENTIFIER_EXPR){
        symbol = std::move(sym);
    }
};

struct numericLiteral : expr{
    double value;
    numericLiteral(double val) : expr(NUMERIC_LITERAL){
        value = val;
    }
};

class Parser{
private:
    //stores tokens of program.
    std::vector<Token> tokens;

    bool not_eof();
    //keeps track of index 0;

    Token at();
    //return previous token and increment

    Token advance();
    //entry point for parser.

    std::unique_ptr<statement> parse_statement();
        //already delt with program which is only statement - only expressions to parse
        //in the future will implement funclaration declaration, variable dec, while loops, etc.
    std::unique_ptr<expr> parse_expr();
    std::unique_ptr<expr> parse_primary();
public:
    Parser(std::vector<Token> toks);

    std::unique_ptr<program> produceAsr(std::string sourceCode);
     //able to produce an AST of type program 
    //where each element in the program body is an array of statements. 
}
}

#endif // AST_H