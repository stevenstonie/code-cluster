#pragma once

#include <algorithm>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <fstream>

#include "Inutils.hpp"

class Grammar {
public:
	class U_VS {
	public:
		class V {
		public:
			V(std::vector<std::string> v)
				: v(v) {}

			std::vector<std::string> getV() const {
				return v;
			}
			std::vector<std::string>& getChangeableV(){
				return v;
			}

			void setVSymbol(int index, std::string vSymbol){
				this->v[index] = vSymbol;
			}

		private:
			std::vector<std::string> v;
		};

		U_VS() = default;
		U_VS(std::string u, std::vector<V> vs)
			:u(u), vs(vs)
		{}
		U_VS(std::string u, std::vector<std::string> v)
			:u(u), vs({V(v)})
		{}
		U_VS(std::string u)
			:u(u)
		{}

		std::string getU() const {
			return u;
		}
		std::string& getChangeableU(){
			return u;
		}
		std::vector<V> getVS() const{
			return vs;
		}
		std::vector<V>& getChangeableVS(){
			return vs;
		}

		void addV(std::vector<std::string> v) {
			vs.push_back(V(v));
		}
		void setV(int index, std::vector<std::string> v){
			vs[index] = V(v);
		}
		void setVSymbol(int index, int index2, std::string vSymbol){
			vs[index].setVSymbol(index2, vSymbol);
		}
		void setU(std::string newU){
			u = newU;
		}
	private:
		std::string u;
		std::vector<V> vs;
	};

	Grammar() = default;

	static Grammar createGrammar();

	bool verifyGrammar();

	bool isContextFree();

	void transformToGreibachNormalForm();

	void printGrammar();

	void readGrammar();

	std::vector<std::string> getVn() const;
	std::vector<std::string> getVt() const;
	std::string getS() const;
	std::vector<U_VS> getUS_VS() const;

	std::string& getChangeableS();
	std::vector<std::string>& getChangeableVn();

	void addToVn(std::string nonTerminal);
	void addToVt(std::string terminal);
	void setS(std::string S);
	void setVn(const std::vector<std::string>& newVn);
	void addU(std::string u);

	friend std::ostream& operator<<(std::ostream& output, const Grammar& grammar);

	friend std::istream& operator>>(std::istream& input, Grammar& grammar);

private:
	void changeProductionsToSatisfyAscendingOrder();

	void renameNonTerminalsInAscendingOrder();

	void removeAllUnreachableProductionsAndAllRenamings();

	void replaceTerminalsOnRightOfVsWithNonTerms();

	void shortenProductionsAndAddNewOnes();

	void transformToChomskyNormalForm();

	std::string createNewUSymbolByIncrementing(std::string uSymbol);

	std::string createNewUSymbolByDecrementing(std::string uSymbol);

	void searchAndAddTerminalOnRhsOfReplacingSymbol(U_VS& replacingSymbol, std::string v);

	bool foundStringInVector(const std::vector<std::string>& vector, const std::string& string) const;

	bool isNonTerminal(std::string vSymbol) const;

private:
	std::vector<std::string> Vn, Vt; // Vn = [S, A, B, C]. Vt = [a, b, c, d]
	//^^no need for a vector of vectors of strings for Vn as the rule will always have only one element on the left hand side
	std::string S;
	// U_VS = S -> aA1 | BCD | cC
	// V = a, A1
	// vSymbol = a
	std::vector<U_VS> us_and_productions;
};
/*
for(const auto& u_vs : us_and_productions){
	for(const auto& v : u_vs.getVS()){
		for(const auto& vSymbol : v.getV()){

		}
	}
}
*/

/*
	std::vector<U_VS> allProductions;

	U_VS::V v1({"a", "A"});
	U_VS::V v2({"B", "C", "D"});
	U_VS::V v3({"c", "C"});

	U_VS u_vs("S", {v1, v2});

	u_vs.addV(v3);

	allProductions.push_back(u_vs);
*/
