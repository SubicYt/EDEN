#include <iostream>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <vector>

#include "lexer.h"
#include "AST.h"
//vscode is for soyboys.

//supporting commandline agruments idk how ts works bro. 
int main(int argc, char* argv[]) {
	if (argc != 2) {
		std::cerr << "incorrect usage. expected usage ---->" << std::endl;
		std::cerr << "Eden <input.eden>?" << std::endl; //subject to change
		return EXIT_FAILURE; 
	}
	
	std::fstream inputCode(argv[1], std::ios::in); //specified usage. just read in;
    if(!inputCode.is_open()){
        std::cerr<<"Could not open source code file";
        return EXIT_FAILURE;
    }
    
	std::stringstream contentsStream;
	contentsStream << inputCode.rdbuf();
	inputCode.close();
	
	std::string sourceCode = contentsStream.str(); // Convert stringstream to a string
	std::ofstream output("TokensOut.txt");

	lexer Lexer(sourceCode);
	
	std::vector<Token> sourceTokens;
	sourceTokens = Lexer.tokenize();

	

	for (size_t i = 0; i < sourceTokens.size(); i++) {
		output << "{" << tokenTypeToString(sourceTokens[i].type)
			<< ", " << sourceTokens[i].tokenValue << "}" << ", ";
	}
	output.close();
	return EXIT_SUCCESS;
} 
