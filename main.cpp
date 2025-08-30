#include <iostream>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <vector>
#include "lexer.h"

//vscode is boy soyboys.


//supporting commandline agruments idk how ts works bro. 
int main(int argc, char* argv[]) {
	if (argc != 2) {
		std::cerr << "incorrect usage. expected usage ---->" << std::endl;
		std::cerr << "Eden <input.eden>?" << std::endl; //subject to change
		return EXIT_FAILURE; 
	}
	
	std::fstream inputCode(argv[1], std::ios::in);//specified usage. just read in;
	std::stringstream contentsStream;
	contentsStream << inputCode.rdbuf();
	inputCode.close();
	
	std::string sourceCode = contentsStream.str(); // Convert stringstream to a string
	
	lexer Lexer(sourceCode);
	std::vector<Token> sourceTokens;
	sourceTokens = Lexer.tokenize();

	for (int i = 0; i < sourceTokens.size(); i++) {
		sourceTokens << "{" << tokenTypeToString(TokenList[i].type)
			<< ", " << TokenList[i].tokenValue << "}" << ", ";
	}
	
	
	return EXIT_SUCCESS;
} 