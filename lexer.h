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


enum TokenType {
    // Single-character tokens
    LEFT_PAREN, RIGHT_PAREN, PLUS, MINUS, STAR, SLASH, EQUAL, COMMA,
    SEMI_COLON,
    // Keywords
    IF, ELSE, WHILE, FOR, RETURN, TRUE, FALSE,
    // Multi-character tokens
    EQUAL_EQUAL, NOT_EQUAL, LESS_EQUAL, GREATER_EQUAL, SLASH_SLASH,
    // Literals
    ASSIGNMENT, IDENTIFIER, STRING, NUMBER, KEYWORD,
    // End of file
    END_OF_FILE
};

struct Token {
    TokenType type;
    std::string tokenValue;

    Token(TokenType tk, std::string val) {
        type = tk;
        tokenValue = val;
    }
};

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

std::map<std::string, TokenType> TokenPairs{
    {"let", TokenType::KEYWORD},
    {"var", TokenType::KEYWORD},
    {"if", TokenType::IF},
    {"(", TokenType::LEFT_PAREN},
    {";", TokenType::SEMI_COLON},
    {")", TokenType::RIGHT_PAREN},
    {"+", TokenType::PLUS}, {"-", TokenType::MINUS}
};

class lexer {
private:
    //input as users source code
    std::string inputCode;
    size_t currentPosition;
    char currentChar;

public:

    lexer(std::string input) {
        inputCode = input;
        currentPosition = 0;
        if (!inputCode.empty()) {
            currentChar = inputCode[currentPosition];
        }
        else {
            currentChar = '\0';
        }
    }

    void advance() {
        currentPosition++;
        if (currentPosition < inputCode.size()) {
            currentChar = inputCode[currentPosition];
        }
        else {
            currentChar = '\0';
        }
    }

    void handleWhiteSpace() {
        while (currentPosition < inputCode.size() && isspace(static_cast<unsigned char>(currentChar))) {
            advance();
        }
    }

    std::vector<Token> tokenize() {
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

    //implement methods here

    Token handleIdentifierOrKeyword() {
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

    Token handleString() {
        std::string stringLiteral = "";
        advance(); // skip the white space;
        while (isalnum(static_cast<unsigned char>(currentChar)) && currentChar != '"' && currentChar != '\0') {
            stringLiteral.push_back(currentChar);
            advance();
        }
        if (currentChar != '"') {
            std::runtime_error("String literal not closed ---- >  ");
        }
        advance(); // moves one past closing quote
        return Token(STRING, "stringLiteral");
    }

    Token handleNumber() { 
        std::string digitString = "";
        while (isdigit(static_cast<unsigned char>(currentChar))) {
            digitString.push_back(currentChar);
            advance();
        }
        return Token(NUMBER, digitString);
    }

    Token handleSingleDoubleChars() {
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
};


#endif LEXER_H
