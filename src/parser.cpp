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
    std::vector<Token> tokens;
    size_t currentPosition;

    private:
        bool not_eof(){
            tokens[0].type = TokenType::END_OF_FILE;
        }

        Token at(){
            return tokens[0];
        }

        std::unique_ptr<statement> parseStatement(){
            return parseExpression();
        }

        std::unique_ptr<expr> parseExpression(){
            
        }

        //parse primary expressions first
        //i.e numberic literals and identifiers;

        std::unique_ptr<expr> parsePrimaryExpression(){
            //determine wether numeric literal or identifier first
            const auto tk = at().type;
            
            switch(tk){
                case TokenType::IDENTIFIER:
                return std::make_unique<expr>(IDENTIFIER, at().tokenValue);
            //implement further
        }
    }

public:

    std::unique_ptr<program> produceAST (const std::string& sourceCode){
            lexer Lexer(sourceCode);
            std::vector<Token>tokens;
            tokens = Lexer.tokenize();

            auto Program = std::make_unique<program>();
            while(not_eof()){
                Program -> programBody.push_back(parseStatement());
            }
        }
};