#include "FiniteAutomaton.h"

FiniteAutomaton::FiniteAutomaton(std::vector<std::string> p_Q, std::vector<std::string> p_sigma,
	std::vector<std::tuple<std::string, std::string, std::string>> p_delta,
	std::string p_initial,
	std::vector<std::string> p_final)
	: Q(p_Q), sigma(p_sigma), delta(p_delta), initial(p_initial), final(p_final)
{}

bool FiniteAutomaton::VerifyAutomaton(){
	// no element should be empty
	if(Q.empty() || sigma.empty() || delta.empty() || initial.empty() || final.empty())
		return false;

	//Q not equal to sigma
	for(const auto& qElem : Q){
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
		for(const auto& finalState : final){
			auto finalStateInQ = std::find(Q.begin(), Q.end(), finalState);
			if(finalStateInQ == Q.end())
				return false;
		}

		// the delta function of form `````q x a -> p````` needs to have q and p as part of Q and a as part of sigma
		for(const auto& q_a_p : delta){
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
	std::cout << *this;
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
		for(const auto& state : currentStates)
			for(const auto& q_a_p : delta)
				if(std::get<0>(q_a_p) == state && std::get<1>(q_a_p) == str_letter)
					nextCurrentStates.push_back(std::get<2>(q_a_p));
		currentStates = nextCurrentStates;
	}

	// go through the final states and see if there is one occurence of it in 
	// the current states. if yes then it means the word is accepted by the automaton
	for(const auto& finalState : final){
		auto finalStateInCurrentStates = std::find(currentStates.begin(), currentStates.end(), finalState);
		if(finalStateInCurrentStates != currentStates.end())
			return true;
	}
	return false;
}

// an automaton is deterministic when every state in delta has no more than one instance regarding a specific symbol/letter. 
// if, for example, delta has ```q0 x 0 -> q0``` and also ```q0 x 0 -> q2``` then it is not deterministic
/// ...... i think...........
// https://www.stechies.com/difference-between-nfa-dfa/, https://www.tutorialspoint.com/what-is-the-difference-between-dfa-and-nfa
bool FiniteAutomaton::IsDeterministic(){
	// do it like this: go through delta and use a vector to remember states that have already been encountered. 
	// if the state is new add it to the vector and iterate for the same state throughout delta.
	// if the state is not new ignore it
	std::vector<std::string> alreadyCheckedqs;
	for(int i = 0; i < delta.size(); i++){
		std::string qOfDelta = std::get<0>(delta[i]);
		auto qOfDeltaAleadyChecked = std::find(alreadyCheckedqs.begin(), alreadyCheckedqs.end(), qOfDelta);
		if(qOfDeltaAleadyChecked != alreadyCheckedqs.end())
			continue;

		alreadyCheckedqs.push_back(qOfDelta);
		// for every new state iterate through delta for the same state and remember the letter that it uses in a vector.
		// if the state uses the same letter multiple times it is NOT deterministic and so we return false
		std::vector<std::string> usedLettersByCurrentq;
		usedLettersByCurrentq.push_back(std::get<1>(delta[i]));
		for(int j = i + 1; j < delta.size(); j++){
			std::string qOfDeltaa = std::get<0>(delta[j]);
			std::string aOfDeltaa = std::get<1>(delta[j]);
			if(qOfDeltaa == qOfDelta){
				auto findIfLetterAlreadyUsed = std::find(usedLettersByCurrentq.begin(), usedLettersByCurrentq.end(), aOfDeltaa);
				if(findIfLetterAlreadyUsed != usedLettersByCurrentq.end())
					return false;
				else
					usedLettersByCurrentq.push_back(aOfDeltaa);
			}
		}
	}
	return true;
}

std::ostream& operator<<(std::ostream& output, const FiniteAutomaton& finiteautomaton){
	int i;

	output << "Q: ";
	for(i = 0; i < finiteautomaton.Q.size() - 1; i++)
		output << finiteautomaton.Q[i] << ", ";
	output << finiteautomaton.Q[i] << std::endl;

	output << "sigma: ";
	for(i = 0; i < finiteautomaton.sigma.size() - 1; i++)
		output << finiteautomaton.sigma[i] << ", ";
	output << finiteautomaton.sigma[i] << std::endl;

	output << "delta: \n";
	for(i = 0; i < finiteautomaton.delta.size(); i++){
		output << "&(" << std::get<0>(finiteautomaton.delta[i]) << ", ";
		output << std::get<1>(finiteautomaton.delta[i]) << ") = ";
		output << std::get<2>(finiteautomaton.delta[i]) << std::endl;
	}

	output << "initial state: " << finiteautomaton.initial << std::endl;

	output << "final states: ";
	for(i = 0; i < finiteautomaton.final.size() - 1; i++)
		output << finiteautomaton.final[i] << ", ";
	output << finiteautomaton.final[i] << std::endl;

	return output;
}