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
    {"for", TokenType::KEYWORD},
    {"while", TokenType::KEYWORD},
    {"if", TokenType::IF},
    {"(", TokenType::LEFT_PAREN},
    {";", TokenType::SEMI_COLON},
    {")", TokenType::RIGHT_PAREN},
    {"++", TokenType::PLUS_PLUS},
    {"+", TokenType::PLUS},
    {"-", TokenType::MINUS},
    {"<", TokenType::L_THAN},
    {">", TokenType::G_THAN},
    {"{", TokenType::LEFT_BRACKET},
    {"}", TokenType::RIGHT_BRACKET},
    {"\0", TokenType::NULL_TERMINATOR}
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
    case LEFT_BRACKET:   return "LEFT_BRACKET";
    case RIGHT_BRACKET: return "RIGHT_BRACKET";

    case EQUAL:        return "EQUAL";
    case PLUS_PLUS:    return "PLUS_PLUS";
    case L_THAN:       return "L_THAN";
    case G_THAN:       return "G_THAN";
    
    case NUMBER:       return "NUMBER";
    case STRING:       return "STRING";
    case SEMI_COLON:   return "SEMI_COLON";
    case NULL_TERMINATOR: return "NULL_TERMINATOR";

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

Token lexer::handleNullTerminator(){
    return Token(NULL_TERMINATOR, "\0");
}

std::vector<Token>  lexer::tokenize() {
    std::vector<Token> tokenList; // append tokens here for abs tree.
    while (currentChar != '\0') {
        handleWhiteSpace();

        if (currentChar == '\0') {
            tokenList.push_back(handleNullTerminator());
            break;
        }
        //handle single char math operators
        if (currentChar == '+' || currentChar == '-' || currentChar == '*' || currentChar == '/'
            || currentChar == '=' || currentChar == '<' || currentChar == '>'
            || currentChar == ';' || currentChar == '(' || currentChar == ')'
            || currentChar == '{' || currentChar == '}') {
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
        else if (currentChar == ';'){
            tokenList.push_back(Token(SEMI_COLON, ";"));
            break;
        }
        else {
            std::cerr << "Error: Unrecognized character '" << currentChar << "' at position " << currentPosition << std::endl;
            // For now just advance to next char
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
    while (isalnum(static_cast<unsigned char>(currentChar)) && currentChar != '"') {
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
    case '-': return Token(MINUS, "-");
    case '*': return Token(STAR, "*");
    case '<': return Token(L_THAN, "<");
    case '>': return Token(G_THAN, ">");
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
    
    case '+':
        if (currentChar == '+'){
            advance();
            return Token(PLUS_PLUS, "++");
        }
        return Token(PLUS, "+");
    
    case '(': return Token(LEFT_PAREN, "(");
    case ')': return Token(RIGHT_PAREN, ")");
    case '}': return Token(RIGHT_BRACKET, "}");
    case '{': return Token(RIGHT_PAREN, "{");
    case ';': return Token(SEMI_COLON, ";");

    default:
        throw std::runtime_error("unkown single character token");
    }
}