#include <iostream>
#include <vector>
#include <string>
#include <regex>

enum TokenType{
    KEYWORD, IDENTIFIER, LITERAL,
    OPERATOR, PUNCTUATION, ASSIGNMENT,
    END_OF_FILE, ERROR
};

struct Token{
    TokenType type;
    std::string value; //used for identifiers and numbers
};

struct TokenSpec{
    std::string pattern;
    TokenType type;
};

std::string tokenTypeToString(TokenType type) {
    switch (type) {
        case KEYWORD:      return "KEYWORD";
        case IDENTIFIER:   return "IDENTIFIER";
        case LITERAL:      return "LITERAL";
        case OPERATOR:     return "OPERATOR";
        case PUNCTUATION:  return "PUNCTUATION";
        case ASSIGNMENT:   return "ASSIGNMENT";
        case END_OF_FILE:  return "END_OF_FILE";
        case ERROR:        return "ERROR";
        default:           return "UNKNOWN";
    }
}

class Lexer{
private:
    std::string text;
    size_t currentPosition = 0;
    char currentChar; //cached copy of the character at text[pos] or '\0'
public:
    Lexer(std::string& input){
        text = input;
        currentPosition = 0;
    }
    void advance(){
        currentPosition++;
        if(currentPosition < text.size()){
            currentChar = text[currentPosition];
        }
        else{
            currentChar = '\0'; //null terminator, end of line. 
        }
    }
    Token tokenize(){
        std::vector<Token> tokenList;
        while(currentPosition < text.size()){

            currentChar = text[currentPosition];
            if(isspace(static_cast<unsigned char>(currentChar))){
                advance();
                continue;
            }
            
            Token token = nextToken();
            if(token != null){ // how to null? 
                tokenList.push_back(token);
            }else{
                std::cout<<"Unidentified character " << currentChar << std::endl;
            }
        }
    } 

    Token nextToken(){
        if (currentPosition >= text.length()){
            return {END_OF_FILE, ""};
        }
        while(currentPosition< text.length() && isspace(text[currentPosition])){
            advance();
        }

        //list of token patterns and their types
        std::vector<TokenSpec> tokenSpecs = {
        { "if|else|while|for", TokenType::KEYWORD },
        { "let",               TokenType::ASSIGNMENT },
        { "[a-zA-Z_][a-zA-Z0-9_]*", TokenType::IDENTIFIER },
        { "\\d+",              TokenType::LITERAL },
        { "[+-/*=<>!]",        TokenType::OPERATOR },
        { "[.,;(){}]",         TokenType::PUNCTUATION }
    };

    //Match the token descriptors to the token type. 
    //implement later 
    }
};

int main(){
    std::cout<<"yeo"<<std::endl;
}
