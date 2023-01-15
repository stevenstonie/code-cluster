#define twice once
#include <iostream>
#include <fstream>

#include "header_files/Grammar.hpp"
#include "header_files/PushDownAutomaton.hpp"
#include "header_files/TransformGNFintoPDA.hpp"

void menu(){

}

int main(){
	Grammar grammar = Grammar::createGrammar();
	std::cout << grammar;
	std::cout << "\n\n";

	// check if grammar is idc

	grammar.transformToGreibachNormalForm();
	std::cout << grammar;

	transformGNFintoPDA(grammar);

	// menu with the automaton
}
