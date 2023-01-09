#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <random>

class Grammar{
public:
	Grammar() = default;

	bool VerifyGrammar();

	bool isContextFree();

	void simplifyGrammar();
// implement!!

	std::string GenerateWord();

	void PrintGrammar();

	void ReadGrammar();

	std::vector<char> GetVn() const;

	std::vector<char> GetVt() const;

	char GetS() const;

	std::vector<std::pair<std::string, std::string>> GetP() const;

	friend std::ostream& operator<<(std::ostream& output, const Grammar& grammar);

	friend std::istream& operator>>(std::istream& input, Grammar& grammar);

private:
	std::vector<char> Vn, Vt;
	char S;
	std::vector<std::pair<std::string, std::string>> P;

private:
	int randomIntFrom0untilN(int n);
};

