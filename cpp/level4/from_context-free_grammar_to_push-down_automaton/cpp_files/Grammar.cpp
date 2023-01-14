#include "../header_files/Grammar.hpp"

#include <iostream>

Grammar Grammar::createGrammar(){
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
	}
	return true;
}

void Grammar::transformToGreibachNormalForm(){
	// transform to chomsky
	transformToChomskyNormalForm();

	//continue to transform to greibach here
}

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
std::vector<Grammar::U_VS> Grammar::getUS_VS() const {
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
void Grammar::addU(std::string u){
	U_VS newU(u);
	us_and_productions.push_back(newU);
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
					u_vs.addV(convertStringToVectorOfStrings(v));
					break;
				}
			}

			if(foundU == false){
				Grammar::U_VS u_v(u, convertStringToVectorOfStrings((v)));
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

//////////////////////////////////

/////////////private//////////////

//////////////////////////////////

void Grammar::removeAllUnreachableProductionsAndAllRenamings(){
	// go through all productions and check if theres a non-terminal that doesnt appear on at least one rhs (i.e. a non-terminal thats unreachable)
	std::vector<bool> foundNonTermOnRhs = std::vector<bool>(getVn().size(), false);

	for(int i = 0; i < getVn().size(); i++){
		for(const auto& u_vs : us_and_productions){
			for(const auto& v : u_vs.getVS()){
				for(const auto& vSymbol : v.getV()){
					if(vSymbol.find(getVn()[i]) != std::string::npos){
						foundNonTermOnRhs[i] = true;
						break;
					}
				}
				if(foundNonTermOnRhs[i] == true) break;
			}
			if(foundNonTermOnRhs[i] == true) break;
		}
	}

	// delete all productions that are unreachable excluding the start symbol
	for(int i = 0; i < foundNonTermOnRhs.size(); i++){
		if(foundNonTermOnRhs[i] == false && us_and_productions[i].getU() != S){
			// delete the object in P at the index i 
			std::swap(us_and_productions[i], us_and_productions[us_and_productions.size() - 1]);
			us_and_productions.pop_back();

			foundNonTermOnRhs[i] = foundNonTermOnRhs[foundNonTermOnRhs.size() - 1];
			foundNonTermOnRhs.pop_back();

			i--;
		}
	}

	// now its time for the renamings
	// go through all productions. for a production that is of the form A -> B, make it A -> Ba, check if A -> a is already in P. if not add it
	for(auto& u_vs : us_and_productions){
		int i_v = 0;
		for(auto& v : u_vs.getChangeableVS()){
			if(v.getV().size() == 1 && isNonTerminal(v.getV()[0])){
				// add first terminal to the v
				auto newV = v.getChangeableV();
				newV.push_back(getVt()[0]);
				u_vs.setV(i_v, newV);


				// check if the current u transforms to the first terminal. if not add it
				bool found = false;
				for(const auto& v : u_vs.getVS()){
					if(v.getV() == std::vector<std::string>{getVt()[0]}){
						found = true;
						break;
					}
				}
				if(not found){
					u_vs.addV(std::vector<std::string>{getVt()[0]});
				}
			}
			i_v++;
		}
	}
}

void Grammar::replaceTerminalsOnRightOfVsWithNonTerms(){
	// create a new non-terminal Z1 and every time a new terminal needs to be replaced create a Z2 and so on
	std::string lastNonTerminalCreated = "Z";
	std::vector<U_VS> newUsAndProductions;

	// go through all productions and swap all terminals with the last non-terminal created
	for(int i_u = 0; i_u < us_and_productions.size(); i_u++){
		for(int i_v = 0; i_v < us_and_productions[i_u].getChangeableVS().size(); i_v++){
			if(us_and_productions[i_u].getChangeableVS()[i_v].getChangeableV().size() > 1){    // size > 1
				for(int i_vSymbol = 0; i_vSymbol < us_and_productions[i_u].getChangeableVS()[i_v].getChangeableV().size(); i_vSymbol++){    // each symbol
					if(isNonTerminal(us_and_productions[i_u].getChangeableVS()[i_v].getChangeableV()[i_vSymbol]) == false){    // current symbol contains terminal
						bool terminalFound = false;
						for(auto& u : newUsAndProductions){    // check if the terminal already got replaced before
							for(auto& v : u.getChangeableVS()){    // (1)
								// if yes just replace the terminal with the non-terminal that holds it
								if(v.getV() == std::vector<std::string>{us_and_productions[i_u].getChangeableVS()[i_v].getChangeableV()[i_vSymbol]}){
									us_and_productions[i_u].getChangeableVS()[i_v].setVSymbol(i_vSymbol, u.getU());
									terminalFound = true;
								}
							}
						}

						// else create a new non-terminal, make it hold the terminal and replace it with the new non-terminal made
						if(not terminalFound){
							lastNonTerminalCreated = createNewUSymbolByDecrementing(lastNonTerminalCreated);
							newUsAndProductions.push_back(U_VS(lastNonTerminalCreated, std::vector<std::string>{us_and_productions[i_u].getChangeableVS()[i_v].getChangeableV()[i_vSymbol]}));
							us_and_productions[i_u].getChangeableVS()[i_v].setVSymbol(i_vSymbol, newUsAndProductions[newUsAndProductions.size() - 1].getU());
						}

						// on (1) its safe to do it without indexes as i know that these new productions have only one terminal on rhs
					}
				}
			}
		}
	}

	for(const auto& new_u_vs : newUsAndProductions)
		us_and_productions.push_back(new_u_vs);
}

void Grammar::shortenProductionsAndAddNewOnes(){
	// create a non-terminal and every time a new pair of non-terminals needs to be replaced add a new non-terminal
	std::string lastCreatedUSymbol = "A0";

	for(int i_u = 0; i_u < us_and_productions.size(); i_u++){
		for(int i_v = 0; i_v < us_and_productions[i_u].getChangeableVS().size(); i_v++){
			if(us_and_productions[i_u].getVS()[i_v].getV().size() > 2){
				// create new u symbol
				lastCreatedUSymbol = createNewUSymbolByIncrementing(lastCreatedUSymbol);

				// add it to Vn and make it a new production
				addToVn(lastCreatedUSymbol);
				addU(lastCreatedUSymbol);

				// make its production result the current v without the first vSymbol
				std::vector<std::string> currVwithoutFirstSymbol = us_and_productions[i_u].getChangeableVS()[i_v].getChangeableV();
				for(int i = 0; i < currVwithoutFirstSymbol.size() - 1; i++)
					currVwithoutFirstSymbol[i] = currVwithoutFirstSymbol[i + 1];
				currVwithoutFirstSymbol.pop_back();
				us_and_productions.back().addV(currVwithoutFirstSymbol);

				// replace all the vSymbols from the right of the first vSymbol with last created u
				us_and_productions[i_u].setV(i_v, {us_and_productions[i_u].getVS()[i_v].getV().front(), lastCreatedUSymbol});
			}
		}
	}
}

void Grammar::transformToChomskyNormalForm() {
	// step 1: remove all renamings and unreachable symbols
	removeAllUnreachableProductionsAndAllRenamings();

	// shouldnt i also delete the productions that go on indefinitely?

	// step 2: for all productions where v is longer than or equal to 2 and contains a terminal, replace it with a new non-terminal and add a new production that transforms to the changed terminal
	replaceTerminalsOnRightOfVsWithNonTerms();

	// step 3: for all productions where v is longer than 2, shorten them and add new productions that transform to the discarded symbols
	shortenProductionsAndAddNewOnes();
}

std::string Grammar::createNewUSymbolByIncrementing(std::string uSymbol) {
	if(uSymbol.size() < 2)
		return uSymbol + '1';

	if(uSymbol.back() == '9') {
		// make the first char of uSymbol be next in ascii
		char nextLetter = (char) (uSymbol.front() + 1);
		uSymbol.front() = nextLetter;
		uSymbol.back() = '1';
		return uSymbol;
	}

	uSymbol.back() = uSymbol.back() + 1;
	return uSymbol;
}

std::string Grammar::createNewUSymbolByDecrementing(std::string uSymbol) {
	if(uSymbol.size() < 2)
		return uSymbol + '1';

	if(uSymbol.back() == '9') {
		// make the first char of uSymbol be next in ascii
		char nextLetter = (char) (uSymbol.front() - 1);
		uSymbol.front() = nextLetter;
		uSymbol.back() = '1';
		return uSymbol;
	}

	uSymbol.back() = uSymbol.back() + 1;
	return uSymbol;
}

bool Grammar::foundStringInVector(const std::vector<std::string>& vector, const std::string& string) const{
	for(const auto& str : vector)
		if(string == str)
			return true;
	return false;
}

bool Grammar::isNonTerminal(std::string vSymbol) const {
	for(const auto& nonTerminal : getVn())
		if(nonTerminal == vSymbol)
			return true;
	return false;
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

/*
// a grammar is in chomsky normal form when the productions (u->v) are of the form: S->null, A->x and A->BC
bool Grammar::checkIfCanTransformToChomskyNormalForm() {
	// for every u and v's
	for(const auto& u_v : P) {
		// u is of size 1 (also found in isContextFree())
		if(u_v.getLeft().size() != 1)
			return false;

		// u has to be part of Vn (also found in isContextFree())
		{
			auto findUinVn = std::find(Vn.begin(), Vn.end(), u_v.getLeft());
			if(findUinVn == Vn.end())
				return false;
		}

		// only start symbol can transform to null (lambda (epsilon (empty (etc. etc.))
		for(const auto& v : u_v.getRight())
			if(v == "" && u_v.getLeft() != S)
				return false;

		// v has to be either of size 1 and a terminal or size 2 and both elems non-terminals
		for(const auto& v : u_v.getRight()) {
			if(v.size() == 1) {
				auto findVinVt = std::find(Vt.begin(), Vt.end(), v);
				if(findVinVt == Vt.end())
					return false;
			}
			else if(v.size() == 2) {
				auto find2ElemsOfVinVn = std::find(Vn.begin(), Vt.end(), std::to_string(v[0]));
				if(find2ElemsOfVinVn == Vn.end())
					return false;
				find2ElemsOfVinVn = std::find(Vn.begin(), Vt.end(), std::to_string(v[1]));
				if(find2ElemsOfVinVn == Vn.end())
					return false;
			}
			else
				return false;
		}
	}

	return true;
}

*/

///!!!!!!!!!!!! greibach not yet done