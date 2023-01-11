#include "../header_files/Grammar.h"

#include <iostream>

bool Grammar::verifyGrammar() {
	// each element has to be NOT null
	if(Vn.empty() || Vt.empty() || S == "")
		return false;
	for(const auto& u_vs : us_and_productions){
		if(u_vs.getU() == "")
			return false;
		for(const auto& v : u_vs.getVS())
			if(v.getV().empty())
				return false;
	}

	// Vt should not share elements with Vn
	for(const auto& vt_elem : Vt) {
		auto findIfElemIsShared = std::find(Vn.begin(), Vn.end(), vt_elem);
		if(findIfElemIsShared != Vn.end())
			return false;
	}

	// S has to be an element from Vn
	{
		auto find_if_S_is_in_Vn = std::find(Vn.begin(), Vn.end(), S);
		if(find_if_S_is_in_Vn == Vn.end())
			return false;
	}

	// every u of P has at least an element from Vn
	for(const auto& u_vs : us_and_productions){
		bool atLeastOneChrOfUfoundInVn = false;
		for(const auto& uLetter : u_vs.getU()){
			auto findChrInVn = std::find(Vn.begin(), Vn.end(), std::to_string(uLetter));
			if(findChrInVn != Vn.end()) {
				atLeastOneChrOfUfoundInVn = true;
				break;
			}
		}
		if(not atLeastOneChrOfUfoundInVn)
			return false;
	}

	// u and v need to have all elements from Vn OR Vt
	for(const auto& u_vs : us_and_productions) {
		// for each u with its every v check if every element of them is found in either Vn or Vt.
		for(const auto& uLetter : u_vs.getU()){
			auto findUletterInVn = std::find(Vn.begin(), Vn.end(), std::to_string(uLetter));
			if(findUletterInVn == Vn.end()){
				auto findUletterInVt = std::find(Vt.begin(), Vt.end(), std::to_string(uLetter));
				if(findUletterInVt == Vt.end())
					return false;
			}
		}

		for(const auto& v : u_vs.getVS()){
			for(const auto& vSymbol : v.getV()){
				auto findVsymbolInVn = std::find(Vn.begin(), Vn.end(), vSymbol);
				if(findVsymbolInVn == Vn.end()){
					auto findVsymbolInVt = std::find(Vt.begin(), Vt.end(), vSymbol);
					if(findVsymbolInVt == Vt.end())
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
	for(const auto& u_vs : us_and_productions) {
		// u has to be of size 1
		if(u_vs.getU().size() != 1)
			return false;

		// u has to be from Vn

		auto findUinVn = std::find(Vn.begin(), Vn.end(), u_vs.getU());
		if(findUinVn == Vn.end())
			return false;

		// v has to be of size at least 1
		for(const auto& v : u_vs.getVS())
			if(v.getV().size() < 1)
				return false;

		// check if each element of v is either part of Vn or Vt (also found in verifyGrammar())
		for(const auto& v : u_vs.getVS()){
			for(const auto& vSymbol : v.getV()){
				auto findVsymbolInVn = std::find(Vn.begin(), Vn.end(), vSymbol);
				if(findVsymbolInVn == Vn.end()){
					auto findVsymbolInVt = std::find(Vt.begin(), Vt.end(), vSymbol);
					if(findVsymbolInVt == Vt.end())
						return false;
				}
			}
		}

		return true;
	}
}


//void Grammar::transformToGreibachNormalForm(){
//	// transform to chomsky
//	transformToChomskyNormalForm();
//
//	//continue to transform to greibach here
//}

void Grammar::printGrammar() {
	std::cout << *this;
}

void Grammar::readGrammar() {
	int VnSize = 0;
	std::cout << "Vn.size(): ";
	std::cin >> VnSize;
	for(int i = 0; i < VnSize; i++) {
		std::string input_str;
		std::cout << "Vn[" << i << "]: ";
		std::cin >> input_str;
		Vn.push_back(input_str);
	}

	std::cout << "Vt.size(): ";
	int VtSize = 0;
	std::cin >> VtSize;
	for(int i = 0; i < VtSize; i++) {
		std::string input_str;
		std::cout << "Vt[" << i << "]: ";
		std::cin >> input_str;
		Vt.push_back(input_str);
	}

	std::cout << "S: ";
	std::cin >> S;

	std::cout << "nb of total productions: ";
	int productionsNb = 0;
	std::cin >> productionsNb;
	for(int i = 0; i < productionsNb; i++) {
		std::string u = "", v = "";
		std::cout << "P[" << i << "]'s u: ";
		std::cin >> u;
		std::cout << "P[" << i << "]'s v: ";
		std::cin >> v;

		bool foundU = false;
		for(auto& u_vs : us_and_productions){
			if(u_vs.getU() == u){
				foundU = true;
				u_vs.addV(convertStringToVectorOfStrings(v));
				break;
			}
		}

		if(foundU == false){
			U_VS u_v(u, convertStringToVectorOfStrings(v));
			us_and_productions.push_back(u_v);
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
std::vector<Grammar::U_VS> Grammar::getU_VS() const {
	return us_and_productions;
}

void Grammar::addToVn(std::string nonTerminal){
	this->Vn.push_back(nonTerminal);
}
void Grammar::addToVt(std::string terminal){
	this->Vt.push_back(terminal);
}
void Grammar::setS(std::string S){
	this->S = S;
}

std::ostream& operator<<(std::ostream& output, const Grammar& grammar) {
	if(grammar.getVn().empty() || grammar.getVt().empty() || grammar.getS() == "" || grammar.us_and_productions.empty()){
		std::cout << "parts of the grammar are empty. verify the input and try again..";
		exit(1);
	}

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
	for(const auto& u_vs : grammar.us_and_productions){
		output << u_vs.getU() << " -> ";
		for(const auto& v : u_vs.getVS()){
			for(const auto& vSymbol : v.getV()){
				output << vSymbol;
			}
			output << " | ";
		}
		output << "\n";
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
		grammar.setS(input_str);

		input >> input_str;
		int productionsNb = std::stoi(input_str);
		for(int i = 0; i < productionsNb; i++) {
			std::string u, v;
			input >> u >> v;
			if(v == "~")  // null reading. (just in case)
				v = "";

			bool foundU = false;
			for(auto& u_vs : grammar.us_and_productions){
				if(u_vs.getU() == u){
					foundU = true;
					u_vs.addV(grammar.convertStringToVectorOfStrings(v));
					break;
				}
			}
			
			if(foundU == false){
				Grammar::U_VS u_v(u, grammar.convertStringToVectorOfStrings((v)));
				grammar.us_and_productions.push_back(u_v);
			}
		}
	}
	catch(std::invalid_argument) {
		std::cerr << "the file is either empty or doesnt contain the right data..";
		exit(1);
	}
	return input;
}

///////////////////////////
/////////////////////////// private
///////////////////////////

// a grammar is in chomsky normal form when the productions (u->v) are of the form: S->null, A->x and A->BC
//bool Grammar::checkIfCanTransformToChomskyNormalForm() {
//	// for every u and v's
//	for(const auto& u_v : P) {
//		// u is of size 1 (also found in isContextFree())
//		if(u_v.getLeft().size() != 1)
//			return false;
//
//		// u has to be part of Vn (also found in isContextFree())
//		{
//			auto findUinVn = std::find(Vn.begin(), Vn.end(), u_v.getLeft());
//			if(findUinVn == Vn.end())
//				return false;
//		}
//
//		// only start symbol can transform to null (lambda (epsilon (empty (etc. etc.))
//		for(const auto& v : u_v.getRight())
//			if(v == "" && u_v.getLeft() != S)
//				return false;
//
//		// v has to be either of size 1 and a terminal or size 2 and both elems non-terminals
//		for(const auto& v : u_v.getRight()) {
//			if(v.size() == 1) {
//				auto findVinVt = std::find(Vt.begin(), Vt.end(), v);
//				if(findVinVt == Vt.end())
//					return false;
//			}
//			else if(v.size() == 2) {
//				auto find2ElemsOfVinVn = std::find(Vn.begin(), Vt.end(), std::to_string(v[0]));
//				if(find2ElemsOfVinVn == Vn.end())
//					return false;
//				find2ElemsOfVinVn = std::find(Vn.begin(), Vt.end(), std::to_string(v[1]));
//				if(find2ElemsOfVinVn == Vn.end())
//					return false;
//			}
//			else
//				return false;
//		}
//	}
//
//	return true;
//}
//
//void Grammar::removeAllUnreachableProductionsAndAllRenamings(){
//	// go through all productions and check if theres a non-terminal that doesnt appear on at least one rhs (i.e. a non-terminal thats unreachable)
//	std::vector<bool> foundNonTermOnRhs = std::vector<bool>(getP().size(), false);
//
//	for(int i = 0; i < getVn().size(); i++){
//		for(const auto& u_v : getP()){
//			for(const auto& v : u_v.getRight()){
//				if(v.find(getVn()[i][0]) != std::string::npos){
//					foundNonTermOnRhs[i] = true;
//					break;
//				}
//			}
//			if(foundNonTermOnRhs[i] == true)
//				break;
//		}
//	}
//
//	// delete all productions that are unreachable
//	for(int i = 0; i < foundNonTermOnRhs.size(); i++){
//		if(foundNonTermOnRhs[i] == false){
//			// delete the object in P at the index i 
//			std::swap(P[i], P[P.size() - 1]);
//			P.pop_back();
//
//			foundNonTermOnRhs[i] = foundNonTermOnRhs[foundNonTermOnRhs.size() - 1];
//			foundNonTermOnRhs.pop_back();
//
//			i--;
//		}
//	}
//
//	// now its time for the renamings
//	// for each production A->B called renaming set A->B1 and create a B1->B
//
//}
//
//void Grammar::transformToChomskyNormalForm() {
//	// so... this check is useless? 
//	//if (checkIfCanTransformToChomskyNormalForm() == false) {
//	//	std::cout << "the context-free grammar is not in chomsky normal form..";
//	//	return false;
//	//}
//
//	// step 1: remove all renamings and unreachable symbols
//	removeAllUnreachableProductionsAndAllRenamings();
//
//	// step 2: for all productions where v is longer than or equal to 2 and contains a terminal, replace it with a new non-terminal and add a new production that transforms to the changed terminal
//
//	// step 3: for all productions where v is longer than 2, (to complete)
//}
//
//int Grammar::randomIntFrom0untilN(int n) {
//	std::random_device random;
//	std::default_random_engine randomer{random()};
//	std::uniform_int_distribution<int> range(0, n - 1);
//	return range(randomer);
//}

std::vector<std::string> Grammar::convertStringToVectorOfStrings(std::string string){
	std::vector<std::string> vectorOfStrings;
	for(const auto& chr : string)
		vectorOfStrings.push_back(std::string(1, chr));

	return vectorOfStrings;
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

/*
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
*/
