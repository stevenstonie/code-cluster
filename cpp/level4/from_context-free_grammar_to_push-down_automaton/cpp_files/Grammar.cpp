#include "../header_files/Grammar.h"

#include <iostream>

bool Grammar::verifyGrammar() {
	// each element has to be NOT null
	if (Vn.empty() || Vt.empty() || S == "")
		return false;
	for (const auto& u_v : P) {
		if (u_v.getLeft() == "" || u_v.getRight().empty())
			return false;
	}

	// Vt should not share elements with Vn
	for (const auto& vt_elem : Vt) {
		auto findIfElemIsShared = std::find(Vn.begin(), Vn.end(), vt_elem);
		if (findIfElemIsShared != Vn.end())
			return false;
	}

	// S has to be an element from Vn
	{
		auto find_if_S_is_in_Vn = std::find(Vn.begin(), Vn.end(), S);
		if (find_if_S_is_in_Vn == Vn.end())
			return false;
	}

	// every u of P has at least an element from Vn
	for (const auto& u_v : P) {
		bool atLeastOneChrOfuFoundInVn = false;
		for (const auto& chrOfu : u_v.getLeft()) {
			auto findChrInVn = std::find(Vn.begin(), Vn.end(), std::to_string(chrOfu));
			if (findChrInVn != Vn.end()) {
				atLeastOneChrOfuFoundInVn = true;
				break;
			}
		}
		if (atLeastOneChrOfuFoundInVn != true)
			return false;
	}
	
	// u and v need to have all elements from Vn OR Vt
	for (const auto& u_v : P) {
		// for every pair u and v of P check if every element of them is found in either Vn or Vt.
		for (const auto& chrOfu : u_v.getLeft()) {
			auto findChrInVn = std::find(Vn.begin(), Vn.end(), std::to_string(chrOfu));
			if (findChrInVn == Vn.end()) {
				auto findChrInVt = std::find(Vt.begin(), Vt.end(), std::to_string(chrOfu));
				if (findChrInVt == Vt.end())
					return false;
			}
		}
		for (const auto& v : u_v.getRight()) {
			for (const auto& chrOfv : v) {
				auto findChrInVn = std::find(Vn.begin(), Vn.end(), std::to_string(chrOfv));
				if (findChrInVn == Vn.end()) {
					auto findChrInVt = std::find(Vt.begin(), Vt.end(), std::to_string(chrOfv));
					if (findChrInVt == Vt.end())
						return false;
				}
			}
		}
	}
	return true;
}

// a grammar with productions (u->v) is context-free when it is of form A->w where A is a non-terminal and w is a set of terminals and/or non-terminals (at least one)
bool Grammar::isContextFree() {
	// for every u and v's
	for (const auto& u_v : P) {
		// u has to be of size 1
		if (u_v.getLeft().size() != 1)
			return false;

		// u has to be from Vn
		auto findUinVn = std::find(Vn.begin(), Vn.end(), u_v.getLeft());
		if (findUinVn == Vn.end())
			return false;

		// v has to be of size at least 1
		for (const auto& v : u_v.getRight()) {
			if (v.size() < 1)
				return false;
		}

		// check if each element of v is either part of Vn or Vt (also found in verifyGrammar())
		auto findElemsOfVinVnAndVt = std::find(Vn.begin(), Vt.begin(), u_v.getRight()[0]);
		for (const auto& v : u_v.getRight()) {
			for (const auto& elemOfV : v) {
				findElemsOfVinVnAndVt = std::find(Vn.begin(), Vn.end(), std::to_string(elemOfV));
				if (findElemsOfVinVnAndVt == Vn.end()) {
					findElemsOfVinVnAndVt = std::find(Vt.begin(), Vt.end(), std::to_string(elemOfV));
					if (findElemsOfVinVnAndVt == Vt.end())
						return false;
				}
			}
		}
	}
	return true;
}

// a grammar is in chomsky normal form when the productions (u->v) are of the form: S->null, A->x and A->BC
bool Grammar::checkIfCanTransformToChomskyNormalForm() {
	// for every u and v's
	for (const auto& u_v : P) {
		// u is of size 1 (also found in isContextFree())
		if (u_v.getLeft().size() != 1)
			return false;

		// u has to be part of Vn (also found in isContextFree())
		{
			auto findUinVn = std::find(Vn.begin(), Vn.end(), u_v.getLeft());
			if (findUinVn == Vn.end())
				return false;
		}

		// only start symbol can transform to null (lambda (epsilon (empty (etc. etc.))
		for (const auto& v : u_v.getRight())
			if (v == "" && u_v.getLeft() != S)
				return false;

		// v has to be either of size 1 and a terminal or size 2 and both elems non-terminals
		for (const auto& v : u_v.getRight()) {
			if (v.size() == 1) {
				auto findVinVt = std::find(Vt.begin(), Vt.end(), v);
				if (findVinVt == Vt.end())
					return false;
			} else if (v.size() == 2) {
				auto find2ElemsOfVinVn = std::find(Vn.begin(), Vt.end(), std::to_string(v[0]));
				if (find2ElemsOfVinVn == Vn.end())
					return false;
				find2ElemsOfVinVn = std::find(Vn.begin(), Vt.end(), std::to_string(v[1]));
				if (find2ElemsOfVinVn == Vn.end())
					return false;
			} else
				return false;
		}
	}

	return true;
}

bool Grammar::transformToChomskyNormalForm() {
	// so... this check is useless? 
	//if (checkIfCanTransformToChomskyNormalForm() == false) {
	//	std::cout << "the context-free grammar is not in chomsky normal form..";
	//	return false;
	//}
	return true;

	// step 1: remove all renamings and unreachable symbols

	// step 2: for all productions where v is longer than or equal to 2 and contains a terminal, replace it with a new non-terminal and add a new production that transforms to the changed terminal

	// step 3: for all productions where v is longer than 2, (to complete)
}

void Grammar::transformToGreibachNormalForm() {
	// check if function to transform to cnf returned true

	// if not print statement and return;

	// else check if the cnf can transform to gnf

	// // if yes transform to gnf

	// // else print statement and return;
}

// start with S and work your way up to the final word
std::string Grammar::generateWord() {
	// 'allCombinationsOfPMade' holds the combination of all transitions of P that will be made
	// 'PPoolOfCurrentPossibleTransitions' holds the current possible transitions for every instance of the currentWord
	std::vector<std::pair<std::string, std::string>> allCombinationsOfPMade, PPoolOfCurrentPossibleTransitions;
	std::string currentWord = S;  // to_string() makes it 83 instead of 'S'. why does to_string() look at the ascii number and not its representation
	int limitOfTransitions = 100;         // limit the transitions in case the operation runs forever
	while(--limitOfTransitions) {
		PPoolOfCurrentPossibleTransitions.clear();
		// check all u's of P if they are in the currentWord. if yes add the pair to the PPool
		for(const auto& u_v : P) {
			for(const auto& v : u_v.getRight()) {
				auto uInCurrentWord = std::find(currentWord.begin(), currentWord.end(), u_v.getLeft()[0]);
				if(uInCurrentWord != currentWord.end())
					PPoolOfCurrentPossibleTransitions.push_back({u_v.getLeft(), v});
			}
		}
		// if PPool is empty then another transition on currentWord is not possible -> break;
		if(PPoolOfCurrentPossibleTransitions.empty())
			break;
		// else choose randomly between the available transitions and save the one used
		else {
			std::pair<std::string, std::string> u_v_chosen;
			u_v_chosen = PPoolOfCurrentPossibleTransitions[randomIntFrom0untilN(PPoolOfCurrentPossibleTransitions.size())];
			int indexWhereToChange = currentWord.find(u_v_chosen.first[0]);
			currentWord.replace(indexWhereToChange, 1, u_v_chosen.second);
			allCombinationsOfPMade.push_back(u_v_chosen);
		}
	}
	std::cout << "for the transitions: \n";
	for(const auto& u_v : allCombinationsOfPMade)
		std::cout << u_v.first << " -> " << u_v.second << " \n";
	return currentWord;
}

void Grammar::printGrammar() {
	std::cout << *this;
}

void Grammar::readGrammar() {
	int VnSize = 0;
	std::cout << "Vn.size(): ";
	std::cin >> VnSize;
	for(int i = 0; i < VnSize; i++) {
		std::string chr;
		std::cout << "Vn[" << i << "]: ";
		std::cin >> chr;
		Vn.push_back(chr);
	}

	std::cout << "Vt.size(): ";
	int VtSize = 0;
	std::cin >> VtSize;
	for(int i = 0; i < VtSize; i++) {
		std::string chr;
		std::cout << "Vt[" << i << "]: ";
		std::cin >> chr;
		Vt.push_back(chr);
	}

	std::cout << "S: ";
	std::cin >> S;

	std::cout << "P.size(): ";
	int PSize = 0;
	std::cin >> PSize;
	for(int i = 0; i < PSize; i++) {
		std::string u = "", v = "";
		std::cout << "P[" << i << "]'s u: ";
		std::cin >> u;
		std::cout << "P[" << i << "]'s v: ";
		std::cin >> v;

		bool foundU = false;
		for(auto& production : P) {
			if(production.getLeft() == u) {
				foundU = true;
				production.getRight().push_back(v);
				break;
			}
		}

		if(foundU == false) {
			Production p(u, v);
			P.push_back(p);
		}
	}
}

std::vector<std::string> Grammar::getVn() const {
	return Vn;
}

std::vector<std::string> Grammar::getVt() const {
	return Vt;
}

std::string Grammar::getS() const {
	return S;
}

std::vector<Grammar::Production> Grammar::getP() const {
	return P;
}

void Grammar::addToVn(std::string nonTerminal){
	this->Vn.push_back(nonTerminal);
}

void Grammar::addToVt(std::string terminal){
	this->Vt.push_back(terminal);
}

std::ostream& operator<<(std::ostream& output, const Grammar& grammar) {
	output << "Vn: ";
	for(int i = 0; i < grammar.getVn().size() - 1; i++)
		output << grammar.getVn()[i] << ", ";
	output << grammar.getVn()[grammar.getVn().size() - 1] << " \n";

	output << "Vt: ";
	for(int i = 0; i < grammar.getVt().size() - 1; i++)
		output << grammar.getVt()[i] << ", ";
	output << grammar.getVt()[grammar.getVt().size() - 1] << " \n";

	output << "S: " << grammar.getS() << " \n";

	output << "P: \n";
	for(const auto& u_v : grammar.P) {
		output << u_v.getLeft() << " ->";
		for(const auto& v : u_v.getRight())
			output << " | " << v;
		std::cout << "\n";
	}

	return output;
}

std::istream& operator>>(std::istream& input, Grammar& grammar) {
	try {
		std::string input_str;

		input >> input_str;
		int VnSize = std::stoi(input_str);
		for(int i = 0; i < VnSize; i++) {
			input >> input_str;
			grammar.addToVn(input_str);
		}

		input >> input_str;
		int VtSize = std::stoi(input_str);
		for(int i = 0; i < VtSize; i++) {
			input >> input_str;
			grammar.addToVt(input_str);
		}

		input >> input_str;
		grammar.S = input_str[0];

		input >> input_str;
		int PSize = std::stoi(input_str);
		for(int i = 0; i < PSize; i++) {
			std::string u, v;
			input >> u >> v;
			if(v == "~")  // null reading. (just in case)
				v = "";
			
			bool foundU = false;
			for(auto& production : grammar.P) {
				if(production.getLeft() == u) {
					foundU = true;
					production.addRight(v);
					break;
				}
			}

			if(foundU == false) {
				Grammar::Production p(u, v);
				grammar.P.push_back(p);
			}
		}
	}
	catch(std::invalid_argument) {
		std::cerr << "the file is either empty or doesnt contain the right data..";
		exit(1);
	}
	return input;
}

int Grammar::randomIntFrom0untilN(int n) {
	std::random_device random;
	std::default_random_engine randomer{random()};
	std::uniform_int_distribution<int> range(0, n - 1);
	return range(randomer);
}

/*
// takes all combinations of indexesOfVLetter and adds all combinations of v with indexes deleted to allCombinations.
void Grammar::Combi(std::vector<int>& indexesOfVLetter, std::string& word, std::vector<std::string>& allCombinations, int reqLen, int s, int currLen, std::vector<bool> check) {
	if(currLen > reqLen)
		return;
	else if(currLen == reqLen) {
		std::string tempWord = word;
		for(int i = 0; i < indexesOfVLetter.size(); i++) {
			if(check[i] == true) {
				tempWord[indexesOfVLetter[i]] = ' ';
				// dont mess with deletion. make it a space. if you delete a letter, the position of another will shift, complicating things
			}
		}
		allCombinations.push_back(tempWord);
		return;
	}
	if(s == indexesOfVLetter.size()) {
		return;
	}
	check[s] = true;
	Combi(indexesOfVLetter, word, allCombinations, reqLen, s + 1, currLen + 1, check);
	check[s] = false;
	Combi(indexesOfVLetter, word, allCombinations, reqLen, s + 1, currLen, check);
}

void Grammar::eliminateNullProductions() {
	// check which non-terminals can transform to null
	std::vector<char> nonTerminalsThatCanTransformToNull;
	for(const auto& u_v : P){
		for(const auto& v : u_v.getRight()){
			if(v == ""){
				nonTerminalsThatCanTransformToNull.push_back(u_v.getLeft()[0]);
				break;
			}
		}
	}

	// for every production (u->v) check if v contains a non-terminal that can transform to null
	std::vector<std::string> allCombinations;
	for(auto& uToNull : nonTerminalsThatCanTransformToNull){
		for(auto& u_v : P){
			for(auto& v : u_v.getRight()){
				allCombinations.clear();
				std::vector<int> indexesOfVLetter;
				// check for the current v each chr_v that is a non-terminal that can transform to null
				for(int i = 0; i < v.size(); i++)
					if(v[i] == uToNull)
						indexesOfVLetter.push_back(i);

				// go through every elem of v and get every combination of v without the non-terminal that can transform to null
				if(indexesOfVLetter.size() > 0){
					std::vector<bool> check = std::vector<bool>(indexesOfVLetter.size(), false);
					for(int i = 1; i < indexesOfVLetter.size(); i++){
						Combi(indexesOfVLetter, v, allCombinations, i, 0, 0, check);
					}
				}

				// add the last combination without all occurences of the non-terminal that transforms to null
				std::string lastCombination = u_v.getRight()[0];
				for(int i = 0; i < lastCombination.size(); i++){
					if(lastCombination[i] == uToNull){
						lastCombination.erase(i, 1);
						i--;
					}
				}
				allCombinations.push_back(lastCombination);

				// delete all spaces in combinations where the non-terminals deleted were
				for(auto& combination : allCombinations){
					for(int i = 0; i < combination.size(); i++){
						if(combination[i] == ' '){
							combination.erase(i, 1);
							i--;
						}
					}
				}

				// add allCombinations to current P
				for(auto& production : allCombinations){
					u_v.addRight(production);
				}
			}
		}
	}
}

void Grammar::eliminateUselessProductionsInCFG() {
	// eliminate null productions
	eliminateNullProductions();

	// eliminate unit productions
}
*/
