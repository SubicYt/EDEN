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

class Parser{
private:
    //takes tokens from lexer. 
    std::vector<Token> tokens;

    bool not_eof(){
        //evals to true. we are out of tokens to parse.
        return tokens[0].type != TokenType::END_OF_FILE;
    }
    //keeps track of index 0;
    Token at(){
        return tokens[0];
    }

    //return previous token and increment
    Token advance(){
        //first check empty
        if(tokens.empty()){
            throw std::out_of_range("tokens are empty");
        }
        auto prev = tokens.front();
        tokens.erase(tokens.begin());
        return prev;
    }

    //entry point for parser.
    std::unique_ptr<statement> parse_statement(){
        //already delt with program which is only statment - only expressions to parse
        //in the future will implement funclaration declaration, variable dec, while loops, etc.
        return parse_expr();
    }

    std::unique_ptr<expr> parse_expr(){
        return parse_primary();
    }

    std::unique_ptr<expr> parse_primary(){
        auto tk = at().type;
        switch(tk){
            case TokenType::IDENTIFIER:
            return std::make_unique<expr>(IDENTIFIER, advance().tokenValue);

            case TokenType::NUMBER:
            return std::make_unique<expr>(NUMERIC_LITERAL, 
                //parse to float
                std::stof(advance().tokenValue));

            default: 
            return 0;
        }

    }

public:
    std::unique_ptr<program> produceAST(std::string sourceCode){
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