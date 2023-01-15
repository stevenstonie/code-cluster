#pragma twice

#include <vector>
#include <iostream>

#include "Inutils.hpp"

class PushDownAutomaton{
public:
	class Delta{
	public:
		class Production{
		public:
			std::string getNextState() const{
				return nextState;
			}
			std::vector<std::string> getStackPush() const{
				return stackPush;
			}
		private:
			std::string nextState;
			std::vector<std::string> stackPush;
		};

		std::string getState() const{
			return state;
		}
		std::string getInput() const{
			return input;
		}
		std::string getStackTop() const{
			return stackTop;
		}
		std::vector<Production> getProductions() const{
			return productions;
		}

		// changeable getters

	private:
		std::string state;
		std::string input;
		std::string stackTop;
		std::vector<Production> productions;
		// lambda == '~'
	};

	PushDownAutomaton() = default;

	void printAutomaton();

	bool checkWord(std::string givenWord);

	bool isDeterministic();

	friend std::ostream& operator<<(std::ostream& output, const PushDownAutomaton& pushDownAutomaton);

	std::vector<std::string> getQ() const;
	std::vector<std::string> getSigma() const;
	std::vector<std::string> getGamma() const;
	std::vector<Delta> getDelta() const;
	std::string getq0() const;
	std::string getZ0() const;
	std::vector<std::string> getF() const;

	// changeable getters

private:
	std::vector<std::string> Q;  // states set
	std::vector<std::string> sigma;  // alphabet of input symbols
	std::vector<std::string> gamma;  // alphabet of stack symbols
	std::vector<Delta> delta; // transitions set
	std::string q0;  // initial state symbol
	std::string Z0;  // initial stack symbol
	std::vector<std::string> F;  // final states set
};