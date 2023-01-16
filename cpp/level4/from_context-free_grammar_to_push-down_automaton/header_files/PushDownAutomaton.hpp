#pragma once

#include <vector>
#include <iostream>
#include <stack>

#include "Inutils.hpp"

class PushDownAutomaton{
public:
	class Delta{
	public:
		class Production{
		public:
			Production(std::string nextState, std::vector<std::string> stackPush)
				:nextState(nextState), stackPush(stackPush)
			{}
			Production(std::string nextState)
				:nextState(nextState)
			{}

			std::string getNextState() const{
				return nextState;
			}
			std::vector<std::string> getStackPush() const{
				return stackPush;
			}

			void setNextState(std::string& nextState){
				this->nextState = nextState;
			}
			void setStackPush(std::vector<std::string>& stackPush){
				this->stackPush = stackPush;
			}
		private:
			std::string nextState;
			std::vector<std::string> stackPush;
		};

		void setState(std::string& state){
			this->state = state;
		}
		void setLetter(char& letter){
			this->letter = letter;
		}
		void setStackTop(std::string& stackElem){
			this->stackElem = stackElem;
		}
		void setProduction(std::vector<Production>& productions){
			this->productions = productions;
		}

		std::string getState() const{
			return state;
		}
		char getLetter() const{
			return letter;
		}
		std::string getStackElem() const{
			return stackElem;
		}
		std::vector<Production> getProductions() const{
			return productions;
		}

		std::vector<Production>& getChangeableProductions(){
			return productions;
		}

	private:
		std::string state;
		char letter;
		std::string stackElem;
		std::vector<Production> productions;
		// lambda == '~'
	};

	PushDownAutomaton() = default;

	void printAutomaton();

	bool checkWord(std::string givenWord);

	bool isDeterministic();

	friend std::ostream& operator<<(std::ostream& output, const PushDownAutomaton& pushDownAutomaton);

	void setQ(std::vector<std::string>& Q);
	void setSigma(std::vector<std::string>& sigma);
	void setGamma(std::vector<std::string>& gamma);
	void setDelta(std::vector<Delta>& delta);
	void setq0(std::string& q0);
	void setZ0(std::string& Z0);
	void setF(std::vector<std::string>& F);
	void addNewDelta(Delta& delta);

	std::vector<std::string> getQ() const;
	std::vector<std::string> getSigma() const;
	std::vector<std::string> getGamma() const;
	std::vector<Delta> getDeltas() const;
	std::string getq0() const;
	std::string getZ0() const;
	std::vector<std::string> getF() const;

	std::string& getChangeableq0();
	std::vector<Delta>& getChangeableDeltas();
	std::vector<std::string>& getChangeableGamma();

private:
	std::vector<std::string> Q;  // states set
	std::vector<std::string> sigma;  // alphabet of letter symbols
	std::vector<std::string> gamma;  // alphabet of stack symbols
	std::vector<Delta> deltas; // transitions set
	std::string q0;  // initial state symbol
	std::string Z0;  // initial stack symbol
	std::vector<std::string> F;  // final states set
};