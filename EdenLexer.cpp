#include <iostream>
#include <vector>
#include <string>
#include <map>

//let int x = 45 + 16;
enum TokenType {
	// Single-character tokens
	LEFT_PAREN, RIGHT_PAREN, PLUS, MINUS, STAR, SLASH, EQUAL, COMMA,
	// Keywords
	IF, ELSE, WHILE, FOR, RETURN, TRUE, FALSE,
	// Multi-character tokens
	EQUAL_EQUAL, NOT_EQUAL, LESS_EQUAL, GREATER_EQUAL,
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

std::map<std::string, TokenType> TokenPairs{
	{"let", TokenType::KEYWORD},
	{"if", TokenType::IF},
	{"(", TokenType::LEFT_PAREN},
	{")", TokenType::RIGHT_PAREN}
	//continue implementation
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
	
	Token tokenize() {
		std::vector<Token> tokenList;
		while (currentPosition < inputCode.size()) {
			currentChar = inputCode[currentPosition];

			//Handling WhiteSpace
			if (isspace(static_cast<unsigned char>(currentChar))) {
				advance();
				continue;
			}

			//Handling keywords. Rest of keywords to be implemented later on. 
			if (isalpha(currentChar)) {
				std::string identifierString = "";
				while (isalnum) {
					identifierString.push_back(currentChar);
					advance();
					currentChar = inputCode[currentPosition];
				}
				/*
				  if identifier_string is in keywords_map:
				tokens.add(Token)
				  else:
					tokens.add(new Token(IDENTIFIER, identifier_string))
				*/
				if (TokenPairs.find(identifierString) != TokenPairs.end()) {
					tokenList.push_back(Token(TokenPairs[identifierString], identifierString));
				}
				else {
					tokenList.push_back(Token(IDENTIFIER, identifierString));
				}
			}
			//handling numbers and floats. 
			if (isdigit(currentChar)) {
				std::string digitString = "";
				while (isdigit(currentChar) || currentChar == '.') {
					digitString.push_back(currentChar);
					currentPosition++;
					currentChar = inputCode[currentPosition];
				}
				if (TokenPairs.find(digitString) != TokenPairs.end()) {
					tokenList.push_back(Token(TokenPairs[digitString], digitString));
				}
			}
		}
	}
};
int main(){
    std::cout<<"yeo"<<std::endl;
}
