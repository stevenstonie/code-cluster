#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <random>

class Grammar{
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

	bool isRegular();

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
	std::vector<char> Vn, Vt;
	char S;
	std::vector<Production> P;

private:
	int randomIntFrom0untilN(int n);
};

