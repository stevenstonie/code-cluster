#pragma once
#include <vector>
#include <string>

class Grammar{
public:
	Grammar();

	bool VerifyGrammar();

	bool IsRegular();

	std::string GenerateWord();

	void PrintGrammar();

	void ReadGrammar();

	friend std::ostream& operator<<(std::ostream& output, const Grammar& grammar);

	friend std::istream& operator>>(std::istream& input, Grammar& grammar);
private:
	std::vector<char> Vn, Vt;
	char S;
	std::vector<std::pair<std::string, std::string>> P;
};