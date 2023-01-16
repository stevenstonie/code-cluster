#include "../header_files/TransformGNFintoPDA.hpp"

PushDownAutomaton transformGNFintoPDA(Grammar grammar){
	PushDownAutomaton automaton;
	std::vector<std::string> Q{"q0"};
	automaton.setQ(Q);
	automaton.setSigma(grammar.getChangeableVt());
	automaton.setGamma(grammar.getChangeableVn());
	automaton.setq0(automaton.getQ()[0]);
	automaton.setZ0(grammar.getVn()[0]);

	// for every v check if the u and the first vSymbol are the same as an already added one.
	// // if yes add it on the vector of productions
	// // if not create a new object of type Delta and do your job
	for(const auto& u : grammar.getUS_VS()){
		for(const auto& v : u.getVS()){

			bool alreadyExistingProduction = false;
			for(auto& deltas : automaton.getChangeableDeltas()){
				// check if the current delta's letter ==  current v's first symbol and if the current delta's stack elem == current u
				if(deltas.getLetter() == v.getV()[0][0] && deltas.getStackElem() == u.getU()){
					alreadyExistingProduction = true;

					PushDownAutomaton::Delta::Production newProduction(automaton.getq0());
					if(v.getV().size() == 1){
						deltas.getChangeableProductions().push_back(newProduction);
					}
					else{
						std::vector<std::string> newStackPush = v.getV();
						newStackPush.erase(newStackPush.begin());

						newProduction.setStackPush(newStackPush);
						deltas.getChangeableProductions().push_back(newProduction);
					}
				}
			}

			if(alreadyExistingProduction == false){
				PushDownAutomaton::Delta newDelta;

				newDelta.setState(automaton.getChangeableq0());

				newDelta.setLetter(v.getV()[0][0]);

				std::string nonConstStackTop = u.getU();
				newDelta.setStackTop(nonConstStackTop);

				PushDownAutomaton::Delta::Production newProduction(automaton.getq0());
				if(v.getV().size() == 1){
					newDelta.getChangeableProductions().push_back(newProduction);
				}
				else{
					std::vector<std::string> newStackPush = v.getV();
					newStackPush.erase(newStackPush.begin());

					newProduction.setStackPush(newStackPush);
					newDelta.getChangeableProductions().push_back(newProduction);
				}

				// push back new delta into current vector of deltas
				automaton.addNewDelta(newDelta);
			}
		}
	}

	return automaton;
}