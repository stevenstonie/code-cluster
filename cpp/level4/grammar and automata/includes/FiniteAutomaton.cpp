#include "FiniteAutomaton.h"

bool FiniteAutomaton::VerifyAutomaton(){
	// no element should be empty
	if(Q.empty() || sigma.empty() || delta.empty() || initial.empty() || final.empty())
		return false;

	//Q not equal to sigma
	for(auto& qElem : Q){
		auto qElemInSigma = std::find(sigma.begin(), sigma.end(), qElem);
		if(qElemInSigma != sigma.end())
			return false;
	}

	// domains of elements
	{
		// initial state has to be part of Q
		auto initialInQ = std::find(Q.begin(), Q.end(), initial);
		if(initialInQ == Q.end())
			return false;

		// the final state/states have to be part of 
		for(auto& finalState : final){
			auto finalStateInQ = std::find(Q.begin(), Q.end(), finalState);
			if(finalStateInQ == Q.end())
				return false;
		}

		// the delta function of form `````q x a -> p````` needs to have q and p as part of Q and a as part of sigma
		for(auto& q_a_p : delta){
			auto qInQ = std::find(Q.begin(), Q.end(), std::get<0>(q_a_p));
			auto aInSigma = std::find(sigma.begin(), sigma.end(), std::get<1>(q_a_p));
			auto pInQ = std::find(Q.begin(), Q.end(), std::get<2>(q_a_p));
			if(qInQ == Q.end() || aInSigma == sigma.end() || pInQ == Q.end())
				return false;
		}
	}

	return true;
}

void FiniteAutomaton::PrintAutomaton(){
	// std::cout << *this;
	std::cout << "still in maintenance.. \n";
}

// go through the given word. for every letter check in delta which states go in which states and change the 'currentStates' accordingly
bool FiniteAutomaton::CheckWord(std::string givenWord){
	// 'currentStates' holds the current states.. duuh
	std::vector<std::string> currentStates;
	currentStates.push_back(initial);
	// do it like this: for the current letter and current states, check in delta if 
	// they exist and the state they land on
	for(char letter : givenWord){
		std::string str_letter(1, letter);
		std::vector<std::string> nextCurrentStates;
		for(auto& state : currentStates)
			for(auto& q_a_p : delta)
				if(std::get<0>(q_a_p) == state && std::get<1>(q_a_p) == str_letter)
					nextCurrentStates.push_back(std::get<2>(q_a_p));
		currentStates = nextCurrentStates;
	}

	// go through the final states and see if there is one occurence of it in 
	// the current states. if yes then it means the word is accepted by the automaton
	for(auto& finalState : final){
		auto finalStateInCurrentStates = std::find(currentStates.begin(), currentStates.end(), finalState);
		if(finalStateInCurrentStates != currentStates.end())
			return true;
	}
	return false;
}