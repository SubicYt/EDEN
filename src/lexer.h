#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <cctype>

//PROPER DATA TYPE TOKENS ARE TO BE IMPLEMENTED.


enum TokenType {
    // Single-character tokens
    LEFT_PAREN, LEFT_BRACKET, RIGHT_BRACKET, RIGHT_PAREN, 
    PLUS, MINUS, STAR, SLASH, EQUAL, L_THAN, G_THAN,
    COMMA,
    SEMI_COLON, 
    // Keywords
    IF, ELSE, WHILE, FOR, RETURN, TRUE, FALSE,
    // Multi-character tokens
    EQUAL_EQUAL, NOT_EQUAL, LESS_EQUAL, GREATER_EQUAL, SLASH_SLASH,
    PLUS_PLUS, MINUS_MINUS, 
    // Literals
    ASSIGNMENT, IDENTIFIER, STRING, NUMBER, KEYWORD,
    // End of line and file
    NULL_TERMINATOR, END_OF_FILE
};

struct Token {
    TokenType type;
    std::string tokenValue;

    Token(TokenType tk, std::string val);
};

std::string tokenTypeToString(TokenType type);
extern std::map<std::string, TokenType> TokenPairs;//implementation for global var in lexer.cpp

class lexer {
private:
    std::string sourceCode;
    size_t currentPosition;
    char currentChar;

public:
    lexer(std::string input);
    void advance();
    void handleWhiteSpace();
    std::vector<Token> tokenize();

    Token handleIdentifierOrKeyword();
    Token handleString();
    Token handleNumber();
    Token handleSingleDoubleChars();
    Token handleNullTerminator();
};

#endif // LEXER_H