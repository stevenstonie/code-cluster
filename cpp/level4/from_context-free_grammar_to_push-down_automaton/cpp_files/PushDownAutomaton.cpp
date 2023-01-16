#include "../header_files/PushDownAutomaton.hpp"

void PushDownAutomaton::printAutomaton(){
	std::cout << *this;
}

bool PushDownAutomaton::checkWord(std::string givenWord){
	std::stack<std::string> stack;
	stack.push(getZ0());

	std::vector<std::stack<std::string>> allPossibleCombinationsOfStacks;
	allPossibleCombinationsOfStacks.push_back(stack);
	std::vector<std::stack<std::string>> nextPossibleCombinationsOfStacks;

	int lettersLeft = givenWord.size();
	// go through each letter of the word
	for(const auto& letter : givenWord){
		// if the vector of stacks is empty but there still are letters to read then it is not accepted
		if(allPossibleCombinationsOfStacks.size() == 0)
			return false;

		// go through the vector of stacks
		for(int i_stack = 0; i_stack < allPossibleCombinationsOfStacks.size(); i_stack++){
			// go through the deltas and check if the stackHead and letter appear in a delta
			for(int i_delta = 0; i_delta < deltas.size(); i_delta++){
				// if yes delete the top and add its variations in the nextPossibleCombinationsOfStacks
				if(allPossibleCombinationsOfStacks[i_stack].top() == deltas[i_delta].getStackElem() &&
					letter == deltas[i_delta].getLetter()){

					allPossibleCombinationsOfStacks[i_stack].pop();

					for(auto& production : deltas[i_delta].getChangeableProductions()){
						std::stack<std::string> newStack = allPossibleCombinationsOfStacks[i_stack];
						for(int i_prodElem = production.getStackPush().size() - 1; i_prodElem >= 0; i_prodElem--)
							newStack.push(production.getStackPush()[i_prodElem]);
						nextPossibleCombinationsOfStacks.push_back(newStack);
					}

					break;
				}

			}
		}
		// at the end make allpossiblecombs = nextpossiblecombs and empty nextpossiblecombs
		allPossibleCombinationsOfStacks = nextPossibleCombinationsOfStacks;
		// if all possible combs is empty there cant be any more operations
		if(allPossibleCombinationsOfStacks.empty() == true)
			break;
		nextPossibleCombinationsOfStacks.clear();

		--lettersLeft;
	}
	// if there are still more letters to read or if there are still elements in the stack then the word is not accepted by the automaton
	if(lettersLeft > 0 || allPossibleCombinationsOfStacks.size() != 0)
		return false;

	return true;
}

bool PushDownAutomaton::isDeterministic(){
	for(const auto& delta : deltas){
		if(delta.getProductions().size() > 1){
			return false;
		}
		/// second case here
	}
	return true;
}

std::ostream& operator<<(std::ostream& output, const PushDownAutomaton& pushDownAutomaton){
	if(pushDownAutomaton.getQ().size() == 0 || pushDownAutomaton.getSigma().size() == 0
		|| pushDownAutomaton.getGamma().size() == 0 || pushDownAutomaton.getDeltas().size() == 0
		|| pushDownAutomaton.getq0().size() == 0 || pushDownAutomaton.getZ0().size() == 0){
		std::cout << "the automaton contains an empty field.. ";
		exit(1);
	}

	output << "Q: ";
	for(int i = 0; i < pushDownAutomaton.getQ().size() - 1; i++)
		output << pushDownAutomaton.getQ()[i] << ", ";
	output << pushDownAutomaton.getQ().back() << std::endl;

	output << "Sigma: ";
	for(int i = 0; i < pushDownAutomaton.getSigma().size() - 1; i++)
		output << pushDownAutomaton.getSigma()[i] << ", ";
	output << pushDownAutomaton.getSigma().back() << std::endl;

	output << "Gamma: ";
	for(int i = 0; i < pushDownAutomaton.getGamma().size() - 1; i++)
		output << pushDownAutomaton.getGamma()[i] << ", ";
	output << pushDownAutomaton.getGamma().back() << std::endl;

	output << "initial state: " << pushDownAutomaton.getq0() << std::endl;

	output << "initial stack symbol: " << pushDownAutomaton.getZ0() << std::endl;

	output << "final states: ";
	if(pushDownAutomaton.getF().size() == 0){
		output << "none" << std::endl;
	}
	else{
		for(int i = 0; i < pushDownAutomaton.getF().size() - 1; i++)
			output << pushDownAutomaton.getF()[i] << ", ";
		output << pushDownAutomaton.getF().back() << std::endl;
	}

	output << "deltas: " << std::endl;
	for(int i = 0; i < pushDownAutomaton.getDeltas().size(); i++){
		output << "d(";
		output << pushDownAutomaton.getDeltas()[i].getState() << ", ";

		output << pushDownAutomaton.getDeltas()[i].getLetter() << ", ";

		output << pushDownAutomaton.getDeltas()[i].getStackElem() << " ) = {(";

		for(int i_prod = 0; i_prod < pushDownAutomaton.getDeltas()[i].getProductions().size() - 1; i_prod++){
			output << pushDownAutomaton.getDeltas()[i].getProductions()[i_prod].getNextState() << ", ";

			for(int i_stackSymbol = 0; i_stackSymbol < pushDownAutomaton.getDeltas()[i].getProductions()[i_prod].getStackPush().size(); i_stackSymbol++)
				output << pushDownAutomaton.getDeltas()[i].getProductions()[i_prod].getStackPush()[i_stackSymbol];
			output << "), (";
		}

		output << pushDownAutomaton.getDeltas()[i].getProductions().back().getNextState() << ", ";

		for(int i_stackSymbol = 0; i_stackSymbol < pushDownAutomaton.getDeltas()[i].getProductions().back().getStackPush().size(); i_stackSymbol++)
			output << pushDownAutomaton.getDeltas()[i].getProductions().back().getStackPush()[i_stackSymbol];
		output << ")}" << std::endl;
	}
	output << std::endl;

	return output;
}

void PushDownAutomaton::setQ(std::vector<std::string>& Q){
	this->Q = Q;
}
void PushDownAutomaton::setSigma(std::vector<std::string>& sigma){
	this->sigma = sigma;
}
void PushDownAutomaton::setGamma(std::vector<std::string>& gamma){
	this->gamma = gamma;
}
void PushDownAutomaton::setDelta(std::vector<Delta>& deltas){
	this->deltas = deltas;
}
void PushDownAutomaton::setq0(std::string& q0){
	this->q0 = q0;
}
void PushDownAutomaton::setZ0(std::string& Z0){
	this->Z0 = Z0;
}
void PushDownAutomaton::setF(std::vector<std::string>& F){
	this->F = F;
}
void PushDownAutomaton::addNewDelta(Delta& deltas){
	this->deltas.push_back(deltas);
}

std::vector<std::string> PushDownAutomaton::getQ() const{
	return Q;
}
std::vector<std::string> PushDownAutomaton::getSigma() const{
	return sigma;
}
std::vector<std::string> PushDownAutomaton::getGamma() const{
	return gamma;
}
std::vector<PushDownAutomaton::Delta> PushDownAutomaton::getDeltas() const{
	return deltas;
}
std::string PushDownAutomaton::getq0() const{
	return q0;
}
std::string PushDownAutomaton::getZ0() const{
	return Z0;
}
std::vector<std::string> PushDownAutomaton::getF() const{
	return F;
}

std::string& PushDownAutomaton::getChangeableq0(){
	return q0;
}
std::vector<PushDownAutomaton::Delta>& PushDownAutomaton::getChangeableDeltas(){
	return deltas;
}
std::vector<std::string>& PushDownAutomaton::getChangeableGamma(){
	return gamma;
}
