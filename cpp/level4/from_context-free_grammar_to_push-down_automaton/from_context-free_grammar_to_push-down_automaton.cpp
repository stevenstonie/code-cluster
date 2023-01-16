#include <iostream>
#include <fstream>

#include "header_files/Grammar.hpp"
#include "header_files/PushDownAutomaton.hpp"
#include "header_files/TransformGNFintoPDA.hpp"

void menu(PushDownAutomaton automaton){
	char option;
}

int main(){
	Grammar grammar = Grammar::createGrammar();

	if(grammar.isContextFree() == false){
		std::cout << "unfortunately the grammar is not context-free..";
		exit(1);
	}
	else{
		grammar.transformToGreibachNormalForm();
		PushDownAutomaton automaton = transformGNFintoPDA(grammar);

		menu(automaton);
	}
}
