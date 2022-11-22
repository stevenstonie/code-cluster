#include "GrammarToAutomaton.h"

// translate the grammar into the finite automaton.
// https://stackoverflow.com/questions/60160130/how-to-convert-a-regular-grammar-to-finite-automaton	<---- i dont think this is entirely correct 
// http://www.cs.um.edu.mt/gordon.pace/Research/Software/Relic/Transformations/RG/toFSA.html
// https://www.jflap.org/modules/ConvertedFiles/Regular%20Grammar%20to%20DFA%20Conversion%20Module.pdf
// https://www.youtube.com/watch?v=kAIc96Jk-0s
FiniteAutomaton GrammarToFiniteAutomaton(const Grammar& grammar){
	std::vector<std::string> Q;
	std::vector<std::string> sigma;
	std::vector<std::tuple<std::string, std::string, std::string>> delta;
	std::string initial;
	std::vector<std::string> final;

	// make a transition from the non-terminals to states + add an additional final state 
	// use a counter to insert the states with the naming: 'q0', 'q1', 'q2', etc.
	// also create an unordererd map to remember the non-terminals and their associated state name
	std::unordered_map<char, std::string> non_terminal_to_state;
	uint8_t counter = 0;
	for(const auto& non_terminal : grammar.GetVn()){
		Q.push_back("q" + std::to_string(counter++));
		non_terminal_to_state.insert({non_terminal, Q.back()});
	}
	Q.push_back("q" + std::to_string(counter));


	// make a transition from the terminals to symbols
	// use a counter to insert the symbols with the naming: '0', '1', '2', etc.
	// also create an unordered map to remember the terminals and their associated symbol name
	std::unordered_map<char, std::string> terminal_to_symbol;
	counter = 0;
	for(const auto& terminal : grammar.GetVt()){
		sigma.push_back(std::to_string(counter++));
		terminal_to_symbol.insert({terminal, sigma.back()});
	}

	// insert into delta like this:
	// go through the existent non-terminals and find them in the productions(u_v) set.
	// when found, if the non-terminal results in only a terminal then translate it into delta as {u, v0, finalState}
	// else if it results in a terminal and also in a non-terminal then translate it into delta as {u, v0, v1}
	// ps: instead of inserting u, v0, v1, insert their associated state/symbol name (u = q, v0 = a, v1 = p)
	std::string finalState = Q.back();
	for(auto& non_terminal : grammar.GetVn()){
		for(auto& production : grammar.GetP()){
			if(production.first[0] == non_terminal){
				std::string q = non_terminal_to_state.find(production.first[0])->second;
				std::string a = terminal_to_symbol.find(production.second[0])->second;
				if(production.second.size() == 1)
					delta.push_back({q, a, finalState});
				else{
					std::string p = non_terminal_to_state.find(production.second[1])->second;
					delta.push_back({q, a, p});
				}
			}
		}
	}

	initial = Q.front();
	final.push_back(Q.back());

	FiniteAutomaton finaut(Q, sigma, delta, initial, final);
	return finaut;
}
