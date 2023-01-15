#include "../header_files/TransformGNFintoPDA.hpp"

PushDownAutomaton transformGNFintoPDA(Grammar grammar){
	PushDownAutomaton automaton;
	std::vector<std::string> Q{"q0"};
	automaton.setQ(Q);
	automaton.setSigma(grammar.getChangeableVt());
	automaton.setGamma(grammar.getChangeableVn());
	automaton.setq0(automaton.getQ()[0]);
	automaton.setZ0(grammar.getVn()[0]);

	// make a new delta for every v and not for every u because there might be some productions such as:
	// S -> aSA, S -> bC 
	// and so i cant do d(q0, a, S) = {(q0, SA),(q0, C)} as S transitions using a BUT ALSO b

	return automaton;
}