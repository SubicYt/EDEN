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


bool Parser::notEOF(){
    return tokenlist[0].type != TokenType::END_OF_FILE;
}

Token Parser::at(){
    return tokenlist[0];
}

Token Parser::advance(){
    if(tokenlist.empty()){
        throw std::out_of_range("no tokens to parse");
    }
    auto prev = tokenlist.front();
    tokenlist.erase(tokenlist.begin());
    return prev;
}

std::unique_ptr<statement> Parser::parse_statement(){
    //will handle more later
    return parse_expr();
}

std::unique_ptr<expr> Parser::parse_expr(){
    return parse_primaryExpr();
}

std::unique_ptr<expr> Parser::parse_primaryExpr(){
    //parsing through a primary expression
    auto tk = at().type; // token so use type
    switch(tk){
        
        case IDENTIFIER:
        return std::make_unique<expr>(IDENTIFIER_EXPR, std::to_string(tk));
        std::cout<<"sucess"<<std::endl;

        case NUMBER:
        return std::make_unique<expr>(NUMERIC_LITERAL, std::to_string(tk));
        std::cout<<"succes num"<< std::endl;

        default:
        throw std::runtime_error("NONVALID TOKEN");
        std::cout<<"wrong"<<std::endl;
        std::cout<<tk<<std::endl;
    }
}

Parser::Parser(std::vector<Token> srcTokens){
    tokenlist = srcTokens;
}

std::unique_ptr<program> Parser::produceAST(){
    auto Program = std::make_unique<program>();
    while(notEOF()){
        Program -> programBody.push_back(parse_statement());
    }
    return Program;
}
