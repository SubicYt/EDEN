#include "AST.h"
#include "lexer.h"

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <cctype>

//implement binary expressions.


class Parser{
private:
    //takes tokens from lexer. 
    std::vector<Token> tokens;


    bool Parser::not_eof(){
        //evals to true. we are out of tokens to parse.
        return tokens[0].type != TokenType::END_OF_FILE;
    }
    //keeps track of index 0;
    Token at(){
        return tokens[0];
    }

    //return previous token and increment
    Token Parser::advance(){
        //first check empty
        if(tokens.empty()){
            throw std::out_of_range("tokens are empty");
        }
        auto prev = tokens.front();
        tokens.erase(tokens.begin());
        return prev;
    }

    //entry point for parser.
    std::unique_ptr<statement> Parser::parse_statement(){
        //already delt with program which is only statment - only expressions to parse
        //in the future will implement funclaration declaration, variable dec, while loops, etc.
        return parse_expr();
    }

    std::unique_ptr<expr> Parser::parse_expr(){
        return parse_primary();
    }

    std::unique_ptr<expr> Parser::parse_primary(){
        //fix switch statement

        auto tk = at().type;
        switch(tk){
            case IDENTIFIER:
            return std::make_unique<expr>(IDENTIFIER_EXPR);
            
            case NUMBER:
            return std::make_unique<expr>(NUMERIC_LITERAL);
            
            default: 
            throw std::runtime_error("Unexpected token during parsing - >");
            std::cout<<at().tokenValue;
        }
    }

public:

    Parser::Parser(std::string);
    
    std::unique_ptr<program> Parser::produceAST(std::string sourceCode){
        //able to produce an AST of type program 
        //where each element in the program body is an array of statements. 
        auto Program = std::make_unique<program>();
        lexer Lexer(sourceCode);
        tokens = Lexer.tokenize();

        //parse until end of file
        while(not_eof()){
            Program -> programBody.push_back(parse_statement());
        }
        return Program;
    }
};

