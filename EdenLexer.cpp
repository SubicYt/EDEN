#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <stdexcept>


enum TokenType {
    // Single-character tokens //bro why isnt the commit updatting
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

    std::vector<Token> tokenize() {
        std::vector<Token> tokenList;
        while (currentChar != '\0') {

            //Handling WhiteSpace
            if (isspace(static_cast<unsigned char>(currentChar))) {
                advance();
                continue;
            }

            /*
            Fundamental logic for adding stuff to tokenList.
                    if identifier_string is in keywords_map:
                    tokens.add(Token)
                    else:
                    tokens.add(new Token(IDENTIFIER, identifier_string))
            */

            //Handling keywords. Rest of keywords to be implemented later on. 
            if (isalpha(currentChar)) {
                std::string identifierString = "";
               
                while (isalnum(static_cast<unsigned char> (currentChar))) {
                    identifierString.push_back(currentChar);
                    advance();
                }

                if (TokenPairs.find(identifierString) != TokenPairs.end()) {
                    tokenList.push_back(Token(TokenPairs[identifierString], identifierString));
                }
                else {
                    tokenList.push_back(Token(IDENTIFIER, identifierString));
                }
            }

            //handling numbers and floats. 
            else if (isdigit(currentChar)) {
                std::string digitString = "";
                while (isdigit(currentChar) || currentChar == '.') {
                    digitString.push_back(currentChar);
                    advance();
                }
                if (TokenPairs.find(digitString) != TokenPairs.end()) {
                    tokenList.push_back(Token(NUMBER, digitString));
                }
            }

            //Handle single char math operations + - = / * etc
            //Finish IMPLEMENTATION OF SINGLE CHAR OPERATIONS AND DOUBLE CHAR
            else if (currentChar == '+') {
                tokenList.push_back(Token(PLUS, "+"));
                advance();
            }
            else if (currentChar == '-') {
                tokenList.push_back(Token(MINUS, "-"));
                advance();
            }
            else if (currentChar == '*') {
                tokenList.push_back(Token(STAR, "*"));
                advance();
            }
            else if (currentChar == '/') {
                tokenList.push_back(Token(SLASH, "/"));
                advance();
                //Handling
            }
            else if (currentChar == '=') {
                if (currentPosition + 1 < inputCode.size() && inputCode[currentPosition + 1] == '=') {
                    tokenList.push_back(Token(EQUAL_EQUAL, "=="));
                    advance();
                    advance();
                }
                else {
                    tokenList.push_back(Token(EQUAL, "="));
                    advance();
                }
            }

            // Handle string literals
            else if (currentChar == '"') {
                advance(); // Move past opening quote
                std::string stringLiteral = "";
                while (currentChar != '"' && currentChar != '\0') {
                    stringLiteral.push_back(currentChar);
                    advance();
                }
                if (currentChar != '"') {
                    throw std::runtime_error("Error: String literal not closed.");
                }
                tokenList.push_back(Token(STRING, stringLiteral));
                advance(); // Move past closing quote
            }

            // Handle other single characters
            else if (currentChar == '(') {
                tokenList.push_back(Token(LEFT_PAREN, "("));
                advance();
            }
            else if (currentChar == ')') {
                tokenList.push_back(Token(RIGHT_PAREN, ")"));
                advance();
            }
            else {
                std::cerr << "Error: Unrecognized character '" << currentChar << "'" << std::endl;
                advance();
            }

            if (currentChar == ';') {
                tokenList.push_back(Token(SEMI_COLON, ";"));
                advance();
            }

        }
        currentChar = inputCode[currentPosition]; // handles ending whitespace
        if (currentChar != ';') {
            std::cerr << "Error: expected token ;" << std::endl;
        }
        tokenList.push_back(Token(END_OF_FILE, ""));
        return tokenList;
    }
};

int main() {
    std::string sourceCode;
    std::cout << "Enter Source Code Formal: " << std::endl;
    std::getline(std::cin, sourceCode);

    std::ofstream tokenOut("TokensOutput.txt");

    lexer Lexer = lexer(sourceCode);
    std::vector<Token>TokenList = Lexer.tokenize();

    for (int i = 0; i < TokenList.size(); i++) {
        tokenOut << "{" << tokenTypeToString(TokenList[i].type)
            << ", " << TokenList[i].tokenValue << "}" << ", ";
    }

    tokenOut.close();
    return 0;
}

int main() {
	//implement later. 
}
