#include <iostream>
#include <fstream>

#include "header_files/Inutils.hpp"
#include "header_files/Grammar.hpp"
#include "header_files/PushDownAutomaton.hpp"
#include "header_files/TransformGNFintoPDA.hpp"

void menu(Grammar grammar){
	std::cout << "~~~~~ welcome ~~~~~\n\n";
	Grammar simplifiedGrammar = grammar;
	simplifiedGrammar.removeAllUnreachableProductionsAndAllRenamings();

	Grammar grammarInGNF = grammar;
	grammarInGNF.transformToGreibachNormalForm();

	PushDownAutomaton automaton = transformGNFintoPDA(grammarInGNF);

	//bool exit = false;
	//while(true){
	//	printThreeDots();
	//	std::cout << "\n\n";
	//	printMainMenu();
	//	char letter;
	//	std::cin >> letter;
	//	std::cin.ignore(256, '\n');
	//	std::cout << "\n";
	//	switch(letter){
	//		// cases
	//		default:{
	//			exit = true;
	//			break;
	//		}
	//	}
	//	if(exit == true)
	//		break;
	//}
	std::cout << "exiting the menu";
	printThreeDots();
}

int main(){
	Grammar grammar = Grammar::createGrammar();

	std::vector<std::string> randomWord = grammar.generateWord();

	for(const auto& wordElem : randomWord){
		std::cout << wordElem;
	}
	///!!!!!!!!! works!!!!!!!!!!!!!!!!!!!

	/*if(grammar.isContextFree() == true){
		menu(grammar);
	}
	else{
		std::cout << "unfortunately the grammar is not context-free..";
		exit(1);
	}*/
}
