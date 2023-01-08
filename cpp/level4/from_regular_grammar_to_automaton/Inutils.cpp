#include <iostream>
#include <Windows.h>

static void printThreeDots(){
	Sleep(700);
	std::cout << ".";
	Sleep(700);
	std::cout << ".";
	Sleep(700);
	std::cout << ".";
	Sleep(700);
}

static void printMainMenu(){
	std::cout << "the currently accepted inputs are: \n";
	std::cout << "1) print the grammar \n";
	std::cout << "2) generate \"n words\" using the grammar \n";
	std::cout << "3) print the automaton resulted from the grammar \n";
	std::cout << "4) verify if a word is either accepted by the automaton or not \n";
	std::cout << "5) generate a word in grammar and verify if it is accepted by the automaton \n";
	std::cout << "anything else to exit the menu \n";
}
