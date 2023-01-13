#include <iostream>
#include <fstream>

#include "header_files/Grammar.hpp"

Grammar createGrammar(){
	Grammar grammar;

	std::ifstream file1("text_files/readGrammar.in");
	if(not file1.is_open()){
		std::cout << "the file wasnt opened correctly. \n";
		std::cout << "either choose to insert the data by hand or exit: \n";
		std::cout << "0 - insert data from keyboard \n1 - exit the program \n";
		char insertOrExit;
		std::cin >> insertOrExit;
		if(insertOrExit == '0')
			grammar.readGrammar();
		// else continue, close the file and skip the menu
	}
	else
		file1 >> grammar;
	file1.close();

	return grammar;
}

int main(){
	Grammar g = createGrammar();
	g.printGrammar();
	std::cout << "\n\n";

	g.transformToGreibachNormalForm();
	g.printGrammar();
}
