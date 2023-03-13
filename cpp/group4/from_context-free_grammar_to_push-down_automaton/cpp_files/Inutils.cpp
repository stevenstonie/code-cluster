#include "../header_files/Inutils.hpp"

int randomIntFrom0untilN(int n) {
	std::random_device random;
	std::default_random_engine randomer{random()};
	std::uniform_int_distribution<int> range(0, n - 1);
	return range(randomer);
}

std::vector<std::string> convertStringToVectorOfStrings(std::string string){
	std::vector<std::string> vectorOfStrings;
	for(const auto& chr : string)
		vectorOfStrings.push_back(std::string(1, chr));

	return vectorOfStrings;
}

int getIndexOfStringInVector(const std::string& string, const  std::vector<std::string>& vector){
	for(int i = 0; i < vector.size(); i++){
		if(vector[i] == string)
			return i;
	}
	return -1;
}

bool checkIfFirstStringIsSmallerThanSecond(const std::string& string1, const std::string& string2){
	if(string1[0] == string2[0]){
		return string1[1] < string2[1];
	}
	else{
		return string1[0] < string2[0];
	}
}

void printThreeDots(){
	Sleep(700);
	std::cout << ".";
	Sleep(700);
	std::cout << ".";
	Sleep(700);
	std::cout << ".";
	Sleep(700);
}

void printMainMenu(){
	std::cout << "the currently accepted inputs are: \n";
	std::cout << "1 - for printing the grammar \n";
	std::cout << "2 - for generating a word in the grammar \n";
	std::cout << "3 - to print the \"simplified\" grammar \n";
	std::cout << "4 - to print the grammar in Greibach normal form \n";
	std::cout << "5 - for generating a word in the grammar and verifying if it is accepted by the PDA \n";
	std::cout << "6 - to verify if a word read from keyboard is accepted by the PDA \n";
	std::cout << "7 - for printing the resulted automaton \n";
}
