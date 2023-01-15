#include "../header_files/PushDownAutomaton.hpp"

void PushDownAutomaton::printAutomaton(){
	std::cout << *this;
}

std::ostream& operator<<(std::ostream& output, const PushDownAutomaton& pushDownAutomaton){
	if(pushDownAutomaton.getQ().size() == 0 || pushDownAutomaton.getSigma().size() == 0
		|| pushDownAutomaton.getGamma().size() == 0 || pushDownAutomaton.getDelta().size() == 0
		|| pushDownAutomaton.getq0().size() == 0 || pushDownAutomaton.getZ0().size()
		|| pushDownAutomaton.getF().size() == 0){
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
	for(int i = 0; i < pushDownAutomaton.getF().size() - 1; i++)
		output << pushDownAutomaton.getF()[i] << ", ";
	output << pushDownAutomaton.getF().back() << std::endl;

	output << "delta: " << std::endl;
	for(int i = 0; i < pushDownAutomaton.getDelta().size(); i++){
		output << "d(";
		output << pushDownAutomaton.getDelta()[i].getState() << ", ";

		output << pushDownAutomaton.getDelta()[i].getLetter() << ", ";

		output << pushDownAutomaton.getDelta()[i].getStackTop() << " ) = {(";

		for(int i_prod = 0; i_prod < pushDownAutomaton.getDelta()[i].getProductions().size() - 1; i_prod++){
			output << pushDownAutomaton.getDelta()[i].getProductions()[i_prod].getNextState() << ", ";

			for(int i_stackSymbol = 0; i_stackSymbol < pushDownAutomaton.getDelta()[i].getProductions()[i_prod].getStackPush().size(); i_stackSymbol++)
				output << pushDownAutomaton.getDelta()[i].getProductions()[i_prod].getStackPush()[i_stackSymbol];
			output << "), (";
		}

		output << pushDownAutomaton.getDelta()[i].getProductions().back().getNextState() << ", ";

		for(int i_stackSymbol = 0; i_stackSymbol < pushDownAutomaton.getDelta()[i].getProductions().back().getStackPush().size(); i_stackSymbol++)
			output << pushDownAutomaton.getDelta()[i].getProductions().back().getStackPush()[i_stackSymbol];
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
void PushDownAutomaton::setDelta(std::vector<Delta>& delta){
	this->delta = delta;
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

std::vector<std::string> PushDownAutomaton::getQ() const{
	return Q;
}
std::vector<std::string> PushDownAutomaton::getSigma() const{
	return sigma;
}
std::vector<std::string> PushDownAutomaton::getGamma() const{
	return gamma;
}
std::vector<PushDownAutomaton::Delta> PushDownAutomaton::getDelta() const{
	return delta;
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
