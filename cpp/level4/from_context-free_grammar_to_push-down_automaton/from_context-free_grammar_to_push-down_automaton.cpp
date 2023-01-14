#include <iostream>
#include <fstream>

#include "header_files/Grammar.hpp"
#include "header_files/PushDownAutomaton.hpp"
#include "header_files/TransformGNFintoPDA.hpp"

int main(){
	Grammar grammar = Grammar::createGrammar();
	std::cout << grammar;
	std::cout << "\n\n";

	grammar.transformToGreibachNormalForm();
	std::cout << grammar;
}
