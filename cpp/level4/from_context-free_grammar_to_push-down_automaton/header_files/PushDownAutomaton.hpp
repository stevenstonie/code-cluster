#include <vector>

#include "Inutils.hpp"

class PushDownAutomaton{
public:
	class Delta{
	public:
		std::string getState() const;
		std::string getInput() const;
		std::string getStackTop() const;
		std::string getNewState() const;
		std::vector<std::string> getNewStackTop() const;

		// changeable getters

	private:
		std::string state;
		std::string input;
		std::string stackHead;
		std::string nextState;
		std::vector<std::string> stackPush;
		// lambda == '~'
	};

	void printAutomaton();

	bool checkWord(std::string givenWord);

	bool isDeterministic();

	friend std::ostream& operator<<(std::ostream& output, const PushDownAutomaton& pushDownAutomaton);

	std::vector<std::string> getQ() const;
	std::vector<std::string> getSigma() const;
	std::vector<std::string> getGamma() const;
	std::vector<std::string> getDelta() const;
	std::string getq0() const;
	std::string getZ0() const;
	std::vector<std::string> getF() const;

	// changeable getters

private:
	std::vector<std::string> Q;  // states set
	std::vector<std::string> Sigma;  // alphabet of input symbols
	std::vector<std::string> Gamma;  // alphabet of stack symbols
	std::vector<Delta> delta; // transitions set
	std::string q0;  // initial state symbol
	std::string Z0;  // initial stack symbol
	std::vector<std::string> F;  // final states set
};