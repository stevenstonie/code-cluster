#pragma once
#include <vector>
#include <iostream>
#include <tuple>

class FiniteAutomaton{
public:
	bool VerifyAutomaton();

	void PrintAutomaton();

	bool CheckWord(std::string givenWord);
private:
	std::vector<std::string> Q;
	std::vector<std::string> sigma;
	std::vector<std::tuple<std::string, std::string, std::string>> delta;
	std::string initial;
	std::vector<std::string> final;
};