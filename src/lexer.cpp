#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <cctype>
#include "lexer.h"

std::map<std::string, TokenType> TokenPairs{
    {"let", TokenType::KEYWORD},
    {"var", TokenType::KEYWORD},
    {"if", TokenType::IF},
    {"(", TokenType::LEFT_PAREN},
    {";", TokenType::SEMI_COLON},
    {")", TokenType::RIGHT_PAREN},
    {"+", TokenType::PLUS},
    {"-", TokenType::MINUS}
};

Token::Token(TokenType tk, std::string val) {
    type = tk;
    tokenValue = val;
}

std::string tokenTypeToString(TokenType type) {
    switch (type) {
    case KEYWORD:      return "KEYWORD";
    case IDENTIFIER:   return "IDENTIFIER";
    case IF:           return "IF";
    case LEFT_PAREN:   return "LEFT_PAREN";
    case RIGHT_PAREN:  return "RIGHT_PAREN";
    case EQUAL:        return "EQUAL";
    case STRING:       return "STRING";
    case SEMI_COLON:   return "SEMI_COLON";
    default:           return "UNKNOWN";
    }
}

lexer::lexer(std::string stringInput) {
    sourceCode = stringInput;
    currentPosition = 0;
    if (!sourceCode.empty()) {
        currentChar = sourceCode[currentPosition];
    }
    else {
        currentChar = '\0';
    }
}

void lexer::advance() {
    currentPosition++;
    if (currentPosition < sourceCode.size()) {
        currentChar = sourceCode[currentPosition];
    }
    else {
        currentChar = '\0';
    }
}

void lexer::handleWhiteSpace() {
    while (currentPosition < sourceCode.size() && isspace(static_cast<unsigned char>(currentChar))) {
        advance();
    }
}

std::vector<Token>  lexer::tokenize() {
    std::vector<Token> tokenList; // append tokens here for abs tree.
    while (currentChar != '\0') {
        handleWhiteSpace();

        if (currentChar == '\0') {
            break;
        }
        //handle single char math operators
        if (currentChar == '+' || currentChar == '-' || currentChar == '*' || currentChar == '/'
            || currentChar == '=' || currentChar == '++' || currentChar == '--' || currentChar == '=='
            || currentChar == '(' || currentChar == ')' || currentChar == '//') {
            tokenList.push_back(handleSingleDoubleChars());
            continue;
        }
        if (isalpha(static_cast<unsigned char>(currentChar))) {
            tokenList.push_back(handleIdentifierOrKeyword());
        }
        else if (isdigit(static_cast<unsigned char>(currentChar))) {
            tokenList.push_back(handleNumber());
        }
        else if (currentChar == '"') {
            tokenList.push_back(handleString());
        }
        else {
            std::cerr << "Error: Unrecognized character '" << currentChar << "' at position " << currentPosition << std::endl;
            // For now, we'll just advance to the next character. A real compiler would probably exit or record the error.
            advance();
        }
    }
    tokenList.push_back(Token(END_OF_FILE, ""));
    return tokenList;
}

Token lexer::handleIdentifierOrKeyword() {
    std::string identifierString = "";
    while (isalnum(static_cast<unsigned char> (currentChar))) {
        identifierString.push_back(currentChar);
        advance();
    }
    if (TokenPairs.find(identifierString) != TokenPairs.end()) {
        return Token(KEYWORD, identifierString);
    }
    else {
        return Token(IDENTIFIER, identifierString);
    }

}

Token lexer::handleString() {
    std::string stringLiteral = "";
    advance(); // skip the white space;
    while (isalnum(static_cast<unsigned char>(currentChar)) && currentChar != '"' && currentChar != '\0') {
        stringLiteral.push_back(currentChar);
        advance();
    }
    if (currentChar != '"') {
       throw std::runtime_error("String literal not closed ---- >  ");
    }
    advance(); // moves one past closing quote
    return Token(STRING, "stringLiteral");
}

Token lexer::handleNumber() {
    std::string digitString = "";
    while (isdigit(static_cast<unsigned char>(currentChar))) {
        digitString.push_back(currentChar);
        advance();
    }
    return Token(NUMBER, digitString);
}

Token lexer::handleSingleDoubleChars() {
    char firstChar = currentChar;
    advance();
    switch (firstChar) {
    case '+': return Token(PLUS, "+");
    case '-': return Token(MINUS, "-");
    case '*': return Token(STAR, "*");
    case '/':
        if (currentChar == '/') {
            advance();
            while (currentChar != '\0' && currentChar != '\n') {
                advance();
            }
            //// Recurse to handle the next token after the comment
            return handleSingleDoubleChars();
        }
        return Token(SLASH, "/");
    case '=':
        if (currentChar == '=') {
            advance();
            return Token(EQUAL_EQUAL, "==");
        }
        return Token(EQUAL, "=");

    case '(': return Token(LEFT_PAREN, "(");
    case ')': return Token(RIGHT_PAREN, ")");
    case ';': return Token(SEMI_COLON, ";");
    default:
        throw std::runtime_error("unkown single character token");
    }
}



