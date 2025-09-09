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
    auto tk = advance(); //return the first token
    switch(tk.type){
        case IDENTIFIER: {
            return std::make_unique<identifier>(tk.tokenValue);
        }
        case NUMBER: {
            double val = std::stod(tk.tokenValue);
            return std::make_unique<numericLiteral>(val);
        }

        default: {
            throw std::runtime_error("Unexpected node to parse");
            std::cout<<tk.tokenValue<<std::endl;
            return nullptr;
        }
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
