#pragma once
#include <iostream>
#include <tuple>
#include <vector>

class FiniteAutomaton {
   public:
    FiniteAutomaton(std::vector<std::string> p_Q, std::vector<std::string> p_sigma,
                    std::vector<std::tuple<std::string, std::string, std::string>> p_delta,
                    std::string p_initial,
                    std::vector<std::string> p_final);

    bool VerifyAutomaton();

    void PrintAutomaton();

    bool CheckWord(std::string givenWord);

    bool IsDeterministic();

    friend std::ostream& operator<<(std::ostream& output, const FiniteAutomaton& finiteautomaton);

   private:
    std::vector<std::string> Q;
    std::vector<std::string> sigma;
    std::vector<std::tuple<std::string, std::string, std::string>> delta;
    std::string initial;
    std::vector<std::string> final;
};
