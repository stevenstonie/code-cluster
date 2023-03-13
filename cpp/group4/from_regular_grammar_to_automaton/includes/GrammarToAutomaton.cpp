#include "GrammarToAutomaton.h"


// translate the grammar into the finite automaton.
// https://stackoverflow.com/questions/60160130/how-to-convert-a-regular-grammar-to-finite-automaton	<---- this isnt entirely correct 
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
	for(const auto& non_terminal : grammar.getVn()){
		std::string str_non_terminal(1, non_terminal);
		Q.push_back(str_non_terminal);
	}
	Q.push_back("Z");

	// make a transition from the terminals to symbols
	for(const auto& terminal : grammar.getVt()){
		std::string str_terminal(1, terminal);
		sigma.push_back(str_terminal);
	}

	// insert into delta like this:
	// go through the existent non-terminals and find them in the productions(u_v) set.
	// when found, if the non-terminal results in only a terminal then translate it into delta as {u, v, finalState}
	// else if it results in a terminal and also in a non-terminal then translate it into delta as {u, v0, v1}
	std::string finalState = Q.back();
	for(const auto& non_terminal : grammar.getVn()){
		for(const auto& production : grammar.getP()){
			if(production.getLeft()[0] == non_terminal){
				for(const auto& v : production.getRight()){
					std::string str_v_0(1, v[0]);
					if(v.size() == 1)
						delta.push_back({production.getLeft(), str_v_0, finalState});
					else{
						std::string str_v_1(1, v[1]);
						delta.push_back({production.getLeft(), str_v_0, str_v_1});
					}
				}
			}
		}
	}

	initial = Q.front();
	final.push_back(Q.back());

	FiniteAutomaton finaut(Q, sigma, delta, initial, final);
	return finaut;
}