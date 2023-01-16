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

	bool exit = false;
	while(true){
		printThreeDots();
		std::cout << "\n\n";
		printMainMenu();
		char letter;
		std::cin >> letter;
		std::cin.ignore(256, '\n');
		std::cout << "\n";
		switch(letter){
			case '1':{
				// print orig grammar
				std::cout << "the original grammar is: \n";
				grammar.printGrammar();

				break;
			}
			case '2':{
				// generate word in orig grammar
				std::vector<std::string> randomWordInGrammar = grammar.generateWord();
				std::cout << "the resulted word is: ";
				for(const auto& wordElem : randomWordInGrammar)
					std::cout << wordElem;

				std::cout << std::endl;
				break;
			}
			case '3':{
				// print "simplified" grammar (not actually simplified)
				std::cout << "the simplified grammar is: \n";
				simplifiedGrammar.printGrammar();

				break;
			}
			case '4':{
				// print grammar in gnf
				std::cout << "the grammar in GNF is: \n";
				grammarInGNF.printGrammar();

				break;
			}
			case '5':{
				// generate word in orig grammar and check if it is accepted by the pda
				std::vector<std::string> randomWordInGrammar = grammar.generateWord();
				std::string str_randomWordInGrammar = "";
				for(const auto& wordElem : randomWordInGrammar)
					str_randomWordInGrammar += wordElem;

				bool isWordAcceptedByAutomaton = automaton.checkWord(str_randomWordInGrammar);

				std::cout << "the resulted word \"" << str_randomWordInGrammar << "\" ";
				if(isWordAcceptedByAutomaton == true){
					std::cout << "is accepted by the automaton. \n";
				}
				else{
					std::cout << "is not accepted by the automaton.. \n";
				}

				break;
			}
			case '6':{
				// insert word from keyboard and check if it is accepted by the pda
				std::cout << "insert the word from keyboard: ";
				std::string wordInputFromKeyboard;
				std::cin >> wordInputFromKeyboard;

				bool isWordAcceptedByAutomaton = automaton.checkWord(wordInputFromKeyboard);

				std::cout << "the inserted word \"" << wordInputFromKeyboard << "\" ";
				if(isWordAcceptedByAutomaton == true){
					std::cout << "is accepted by the automaton. \n";
				}
				else{
					std::cout << "is not accepted by the automaton.. \n";
				}

				break;
			}
			case '7':{
				// print resulted pda
				automaton.printAutomaton();

				break;
			}

			default:{
				exit = true;
				break;
			}
		}
		if(exit == true)
			break;
	}
	std::cout << "exiting the menu";
	printThreeDots();
}

int main(){
	Grammar grammar = Grammar::addGrammarFromTextFile();

	if(grammar.isContextFree() == true){
		menu(grammar);
	}
	else{
		std::cout << "unfortunately the grammar is not context-free";
		printThreeDots();
		exit(1);
	}
}
/// left recursion not done!
