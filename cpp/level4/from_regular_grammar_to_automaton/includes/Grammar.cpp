#include "Grammar.h"

bool Grammar::verifyGrammar() {
    // each element has to be NOT null
    if (Vn.empty() || Vt.empty() || S == 0)
        return false;
    for (const auto& u_v : P) {
        if (u_v.getLeft() == "" || u_v.getRight().empty())
            return false;
    }

    // Vt should not share elements with Vn
    for (const auto& vt_elem : Vt) {
        auto findIfElemIsShared = std::find(Vn.begin(), Vn.end(), vt_elem);
        if (findIfElemIsShared != Vn.end())
            return false;
    }

    // S has to be an element from Vn
    {
        auto find_if_S_is_in_Vn = std::find(Vn.begin(), Vn.end(), S);
        if (find_if_S_is_in_Vn == Vn.end())
            return false;
    }

    // every u of P has at least an element from Vn
    for (const auto& u_v : P) {
        bool atLeastOneChrOfuFoundInVn = false;
        for (const auto& chrOfu : u_v.getLeft()) {
            auto findChrInVn = std::find(Vn.begin(), Vn.end(), chrOfu);
            if (findChrInVn != Vn.end()) {
                atLeastOneChrOfuFoundInVn = true;
                break;
            }
        }
        if (atLeastOneChrOfuFoundInVn != true)
            return false;
    }

    // u and v need to have all elements from Vn OR Vt
    for (const auto& u_v : P) {
        // for every pair u and v of P check if every element of them is found in either Vn or Vt.
        for (const auto& chrOfu : u_v.getLeft()) {
            auto findChrInVn = std::find(Vn.begin(), Vn.end(), chrOfu);
            if (findChrInVn == Vn.end()) {
                auto findChrInVt = std::find(Vt.begin(), Vt.end(), chrOfu);
                if (findChrInVt == Vt.end())
                    return false;
            }
        }
        for (const auto& v : u_v.getRight()) {
            for (const auto& chrOfv : v) {
                auto findChrInVn = std::find(Vn.begin(), Vn.end(), chrOfv);
                if (findChrInVn == Vn.end()) {
                    auto findChrInVt = std::find(Vt.begin(), Vt.end(), chrOfv);
                    if (findChrInVt == Vt.end())
                        return false;
                }
            }
        }
    }
    return true;
}

// a grammar is regular if A->xB or A->x (general notation: u->v). a grammar is also generative if only A->xB or A->x
bool Grammar::isRegular() {
    // for every u_v pair of P
    for (const auto& u_v : P) {
        // check if u is longer than 1 elem or if v is longer than 2 elements
        if (u_v.getLeft().size() > 1)
            return false;
        for (const auto& v : u_v.getRight())
            if (v.size() > 2)
                return false;

        // check if u is part of Vn
        auto uInVn = std::find(Vn.begin(), Vn.end(), u_v.getLeft()[0]);
        if (uInVn == Vn.end())
            return false;

        for (const auto& v : u_v.getRight()) {
            // if v's size is one it has to be part of Vt
            if (v.size() == 1) {
                auto vInVt = std::find(Vt.begin(), Vt.end(), v[0]);
                if (vInVt == Vt.end())
                    return false;
            }

            // else if v's size is two then the first elem has to be from Vt and the other one from Vn
            if (v.size() == 2) {
                auto firstElemOfvInVt = std::find(Vt.begin(), Vt.end(), v[0]);
                auto secondElemOfvInVn = std::find(Vn.begin(), Vn.end(), v[1]);
                if (firstElemOfvInVt == Vt.end() || secondElemOfvInVn == Vn.end())
                    return false;
            }
        }
    }
    return true;
}

// start with S and work your way up to the final word
std::string Grammar::generateWord() {
    // 'allCombinationsOfPMade' holds the combination of all transitions of P that will be made
    // 'PPoolOfCurrentPossibleTransitions' holds the current possible transitions for every instance of the currentWord
    std::vector<std::pair<std::string, std::string>> allCombinationsOfPMade, PPoolOfCurrentPossibleTransitions;
    std::string currentWord(1, this->S);  // to_string() makes it 83 instead of 'S'. why does to_string() look at the ascii number and not its representation
    int limitOfTransitions = 100;         // limit the transitions in case the operation runs forever
    while (--limitOfTransitions) {
        PPoolOfCurrentPossibleTransitions.clear();
        // check all u's of P if they are in the currentWord. if yes add the pair to the PPool
        for (const auto& u_v : P) {
            for (const auto& v : u_v.getRight()) {
                auto uInCurrentWord = std::find(currentWord.begin(), currentWord.end(), u_v.getLeft()[0]);
                if (uInCurrentWord != currentWord.end())
                    PPoolOfCurrentPossibleTransitions.push_back({u_v.getLeft(), v});
            }
        }
        // if PPool is empty then another transition on currentWord is not possible -> break;
        if (PPoolOfCurrentPossibleTransitions.empty())
            break;
        // else choose randomly between the available transitions and save the one used
        else {
            std::pair<std::string, std::string> u_v_chosen;
            u_v_chosen = PPoolOfCurrentPossibleTransitions[randomIntFrom0untilN(PPoolOfCurrentPossibleTransitions.size())];
            int indexWhereToChange = currentWord.find(u_v_chosen.first[0]);
            currentWord.replace(indexWhereToChange, 1, u_v_chosen.second);
            allCombinationsOfPMade.push_back(u_v_chosen);
        }
    }
    std::cout << "for the transitions: \n";
    for (const auto& u_v : allCombinationsOfPMade)
        std::cout << u_v.first << " -> " << u_v.second << " \n";
    return currentWord;
}

void Grammar::printGrammar() {
    std::cout << *this;
}

void Grammar::readGrammar() {
    int VnSize = 0;
    std::cout << "Vn.size(): ";
    std::cin >> VnSize;
    for (int i = 0; i < VnSize; i++) {
        char chr;
        std::cout << "Vn[" << i << "]: ";
        std::cin >> chr;
        this->Vn.push_back(chr);
    }

    std::cout << "Vt.size(): ";
    int VtSize = 0;
    std::cin >> VtSize;
    for (int i = 0; i < VtSize; i++) {
        char chr;
        std::cout << "Vt[" << i << "]: ";
        std::cin >> chr;
        this->Vt.push_back(chr);
    }

    std::cout << "S: ";
    std::cin >> this->S;

    std::cout << "P.size(): ";
    int PSize = 0;
    std::cin >> PSize;
    for (int i = 0; i < PSize; i++) {
        std::string u = "", v = "";
        std::cout << "P[" << i << "]'s u: ";
        std::cin >> u;
        std::cout << "P[" << i << "]'s v: ";
        std::cin >> v;

        bool foundU = false;
        for (auto& production : this->P) {
            if (production.getLeft() == u) {
                foundU = true;
                production.getRight().push_back(v);
                break;
            }
        }

        if (foundU == false) {
            Production p(u, v);
            this->P.push_back(p);
        }
    }
}

std::ostream& operator<<(std::ostream& output, const Grammar& grammar) {
    output << "Vn: ";
    for (int i = 0; i < grammar.Vn.size() - 1; i++)
        output << grammar.Vn[i] << ", ";
    output << grammar.Vn[grammar.Vn.size() - 1] << " \n";

    output << "Vt: ";
    for (int i = 0; i < grammar.Vt.size() - 1; i++)
        output << grammar.Vt[i] << ", ";
    output << grammar.Vt[grammar.Vt.size() - 1] << " \n";

    output << "S: " << grammar.S << " \n";

    output << "P: \n";
    for (const auto& u_v : grammar.P) {
        output << u_v.getLeft() << " ->";
        for (const auto& v : u_v.getRight())
            output << " | " << v;
        std::cout << "\n";
    }

    return output;
}

std::istream& operator>>(std::istream& input, Grammar& grammar) {
    try {
        std::string input_str;

        input >> input_str;
        int VnSize = std::stoi(input_str);
        for (int i = 0; i < VnSize; i++) {
            input >> input_str;
            grammar.Vn.push_back(input_str[0]);
        }

        input >> input_str;
        int VtSize = std::stoi(input_str);
        for (int i = 0; i < VtSize; i++) {
            input >> input_str;
            grammar.Vt.push_back(input_str[0]);
        }

        input >> input_str;
        grammar.S = input_str[0];

        input >> input_str;
        int PSize = std::stoi(input_str);
        for (int i = 0; i < PSize; i++) {
            std::string u, v;
            input >> u >> v;

            bool foundU = false;
            for (auto& production : grammar.P) {
                if (production.getLeft() == u) {
                    foundU = true;
                    production.addRight(v);
                    break;
                }
            }

            if (foundU == false) {
                Grammar::Production p(u, v);
                grammar.P.push_back(p);
            }
        }
    } catch (std::invalid_argument) {
        std::cerr << "the file is either empty or doesnt contain the right data..";
        exit(1);
    }
    return input;
}

std::vector<char> Grammar::getVn() const {
    return Vn;
}

std::vector<char> Grammar::getVt() const {
    return Vt;
}

char Grammar::getS() const {
    return S;
}

std::vector<Grammar::Production> Grammar::getP() const {
    return P;
}

int Grammar::randomIntFrom0untilN(int n) {
    std::random_device random;
    std::default_random_engine randomer{random()};
    std::uniform_int_distribution<int> range(0, n - 1);
    return range(randomer);
}
