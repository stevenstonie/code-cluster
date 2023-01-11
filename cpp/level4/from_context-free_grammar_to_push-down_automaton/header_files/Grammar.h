#pragma once
#include <algorithm>
#include <iostream>
#include <random>
#include <string>
#include <vector>

class Grammar {
public:
	class U_VS {
	public:
		class V {
		public:
			V(std::vector<std::string> vSymbol)
				: vSymbol(vSymbol) {}

			std::vector<std::string> getV() const {
				return vSymbol;
			}

			void setV(std::vector<std::string> vSymbol) {
				this->vSymbol = vSymbol;
			}

		private:
			std::vector<std::string> vSymbol;
		};

		U_VS() = default;
		U_VS(std::string u, std::vector<V> vs)
			:u(u), vs(vs)
		{}
		U_VS(std::string u, std::vector<std::string> v)
			:u(u), vs({V(v)})
		{}

		std::string getU() const {
			return u;
		}
		std::vector<V> getVS() const{
			return vs;
		}

		// setU?
		
		void addV(std::vector<std::string> v) {
			vs.push_back(V(v));
		}

	private:
		std::string u;
		std::vector<V> vs;
	};

	Grammar() = default;

	bool verifyGrammar();

	bool isContextFree();

	//void transformToGreibachNormalForm();

	void printGrammar();

	void readGrammar();

	std::vector<std::string> getVn() const;
	std::vector<std::string> getVt() const;
	std::string getS() const;
	std::vector<U_VS> getU_VS() const;

	void addToVn(std::string nonTerminal);
	void addToVt(std::string terminal);
	void setS(std::string S);

	friend std::ostream& operator<<(std::ostream& output, const Grammar& grammar);

	friend std::istream& operator>>(std::istream& input, Grammar& grammar);
private:
	/*bool checkIfCanTransformToChomskyNormalForm();

	void removeAllUnreachableProductionsAndAllRenamings();

	void transformToChomskyNormalForm();

	int randomIntFrom0untilN(int n);
	*/
	std::vector<std::string> convertStringToVectorOfStrings(std::string string);

	// void eliminateUselessProductionsInCFG();
	// void eliminateNullProductions();
	// void Combi(std::vector<int>& indexesOfVLetter, std::string& word, std::vector<std::string>& allCombinations, int reqLen, int s, int currLen, std::vector<bool> check);

	// std::string generateWord();

private:
	std::vector<std::string> Vn, Vt; // Vn = [S, A, B, C]. Vt = [a, b, c, d]
	std::string S;
	// i dont need a separate class for u. it will be only one.
	std::vector<U_VS> us_and_productions;
	// U_VS = S -> aA | BCD | cC
	// VS = aA | BCD | cC
	// V = a, A1
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
