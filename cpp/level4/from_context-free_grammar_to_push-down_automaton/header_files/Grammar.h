#pragma once
#include <algorithm>
#include <iostream>
#include <random>
#include <string>
#include <vector>

class Grammar {
   public:
	   class Production {
	   public:
		   Production() = default;
		   Production(std::string left, std::string right)
			   : left(left){
			   this->right.push_back(right);
		   }
		   Production(std::string left, std::vector<std::string> right)
			   : left(left), right(right) {}

		   std::string getLeft() const {
			   return left;
		   }
		   std::vector<std::string> getRight() const {
			   return right;
		   }
		   void setLeft(std::string left) {
			   this->left = left;
		   }
		   void setRight(std::vector<std::string> right) {
			   this->right = right;
		   }
		   void addRight(std::string v){
			   this->right.push_back(v);
		   }

		   friend std::ostream& operator<<(std::ostream& output, const Production& production);
		   friend std::istream& operator>>(std::istream& input, Production& production);

	   private:
		   std::string left;
		   std::vector<std::string> right;
	   };

	Grammar() = default;

	bool verifyGrammar();

	bool isContextFree();

	void transformToGreibachNormalForm();

	void simplifyGrammar();
	// implement!!

	std::string generateWord();

	void printGrammar();

	void readGrammar();

	std::vector<char> getVn() const;

	std::vector<char> getVt() const;

	char getS() const;

	std::vector<Production> getP() const;

	friend std::ostream& operator<<(std::ostream& output, const Grammar& grammar);

	friend std::istream& operator>>(std::istream& input, Grammar& grammar);
   private:
	int randomIntFrom0untilN(int n);

	bool checkIfCanTransformToChomskyNormalForm();

	bool transformToChomskyNormalForm();

	void eliminateUselessProductionsInCFG();

	void eliminateNullProductions();

   private:
	std::vector<char> Vn, Vt;
	char S;
	std::vector<Production> P;
};
/// !!!!!! Every elem is exactly 1 char long so there will be no elements
/// such as S0 or A1, A2 etc. S0 is $ whereas A1, A2, A3 will be 1, 2, 3, etc.
