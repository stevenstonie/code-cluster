#include "../header_files/Grammar.h"

bool Grammar::verifyGrammar() {
    // each element has to be NOT null
    if(Vn.empty() || Vt.empty() || S == 0 || P.empty())
        return false;

    // Vt should not share elements with Vn
    for(auto& vt_elem : Vt) {
        auto findIfElemIsShared = std::find(Vn.begin(), Vn.end(), vt_elem);
        if(findIfElemIsShared != Vn.end())
            return false;
    }

    // S has to be an element from Vn
    {
        auto find_if_S_is_in_Vn = std::find(Vn.begin(), Vn.end(), S);
        if(find_if_S_is_in_Vn == Vn.end())
            return false;
    }

    // every u of P has at least an element from Vn
    for(auto& u_v : P) {
        bool atLeastOneChrOfuFoundInVn = false;
        for(auto& chrOfu : u_v.first) {
            auto findChrInVn = std::find(Vn.begin(), Vn.end(), chrOfu);
            if(findChrInVn != Vn.end()) {
                atLeastOneChrOfuFoundInVn = true;
                break;
            }
        }
        if(atLeastOneChrOfuFoundInVn != true)
            return false;
    }

    // u and v need to have all elements from Vn OR Vt
    for(auto& u_v : P) {
        // for every pair u and v of P check if every element of them is found in either Vn or Vt.
        for(auto& chrOfu : u_v.first) {
            auto findChrInVn = std::find(Vn.begin(), Vn.end(), chrOfu);
            if(findChrInVn == Vn.end()) {
                auto findChrInVt = std::find(Vt.begin(), Vt.end(), chrOfu);
                if(findChrInVt == Vt.end())
                    return false;
            }
        }
        for(auto& chrOfv : u_v.second) {
            auto findChrInVn = std::find(Vn.begin(), Vn.end(), chrOfv);
            if(findChrInVn == Vn.end()) {
                auto findChrInVt = std::find(Vt.begin(), Vt.end(), chrOfv);
                if(findChrInVt == Vt.end())
                    return false;
            }
        }
    }
    return true;
}

// a grammar with productions (u->v) is context-free when it is of form A->w where A is a non-terminal and w is a set of terminals and/or non-terminals (at least one)
bool Grammar::isContextFree(){
    // for every u and v
    for(const auto& u_v : P){
        // u has to be of size 1
        if(u_v.first.size() != 1)
            return false;

        // u has to be from Vn
        auto findUinVn = std::find(Vn.begin(), Vn.end(), u_v.first[0]);
        if(findUinVn == Vn.end())
            return false;

        // v has to be of size at least 1
        if(u_v.second.size() < 1)
            return false;

        // check if each element of v is either part of Vn or Vt (also found in verifyGrammar())
        auto findElemsOfVinVnAndVt = std::find(Vn.begin(), Vn.end(), u_v.second[0]);
        for(const auto& elemOfV : u_v.second){
            findElemsOfVinVnAndVt = std::find(Vn.begin(), Vn.end(), elemOfV);
            if(findElemsOfVinVnAndVt == Vn.end()){
                findElemsOfVinVnAndVt = std::find(Vt.begin(), Vt.end(), elemOfV);
                if(findElemsOfVinVnAndVt == Vt.end())
                    return false;
            }
        }
    }
    return true;
}

// a grammar is in chomsky normal form when 
bool Grammar::checkIfCanTransformToChomskyNormalForm(){
    
}

bool Grammar::transformToChomskyNormalForm(){
    // check if the cfg can transform to cnf

    // // if yes transform to cnf

    // // else print statement and return false;
}

void Grammar::transformToGreibachNormalForm(){
    // check if function to transform to cnf returned true

    // if not print statement and return;

    // else check if the cnf can transform to gnf

    // // if yes transform to gnf

    // // else print statement and return;
}

// start with S and work your way up to the final word
std::string Grammar::GenerateWord() {
    // 'allCombinationsOfPMade' holds the combination of all transitions of P that will be made
    // 'PPoolOfCurrentPossibleTransitions' holds the current possible transitions for every instance of the currentWord
    std::vector<std::pair<std::string, std::string>> allCombinationsOfPMade, PPoolOfCurrentPossibleTransitions;
    std::string currentWord(1, this->S);  // to_string() makes it 83 instead of 'S'. why does to_string() look at the ascii number and not its representation
    int limitOfTransitions = 100;         // limit the transitions in case the operation runs forever
    while(--limitOfTransitions) {
        PPoolOfCurrentPossibleTransitions.clear();
        // check all u's of P if they are in the currentWord. if yes add the pair to the PPool
        for(auto& u_v : P) {
            auto uInCurrentWord = std::find(currentWord.begin(), currentWord.end(), u_v.first[0]);
            if(uInCurrentWord != currentWord.end())
                PPoolOfCurrentPossibleTransitions.push_back(u_v);
        }
        // if PPool is empty then another transition on currentWord is not possible -> break;
        if(PPoolOfCurrentPossibleTransitions.empty())
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
    for(auto& u_v : allCombinationsOfPMade)
        std::cout << u_v.first << " -> " << u_v.second << " \n";
    return currentWord;
}

void Grammar::PrintGrammar() {
    std::cout << *this;
}

void Grammar::ReadGrammar() {
    int VnSize = 0;
    std::cout << "Vn.size(): ";
    std::cin >> VnSize;
    for(int i = 0; i < VnSize; i++) {
        char chr;
        std::cout << "Vn[" << i << "]: ";
        std::cin >> chr;
        this->Vn.push_back(chr);
    }

    std::cout << "Vt.size(): ";
    int VtSize = 0;
    std::cin >> VtSize;
    for(int i = 0; i < VtSize; i++) {
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
    for(int i = 0; i < PSize; i++) {
        std::string u = "", v = "";
        std::cout << "P[" << i << "]'s u: ";
        std::cin >> u;
        std::cout << "P[" << i << "]'s v: ";
        std::cin >> v;
        this->P.push_back({u, v});
    }
}

std::ostream& operator<<(std::ostream& output, const Grammar& grammar) {
    output << "Vn: ";
    for(int i = 0; i < grammar.Vn.size() - 1; i++)
        output << grammar.Vn[i] << ", ";
    output << grammar.Vn[grammar.Vn.size() - 1] << " \n";

    output << "Vt: ";
    for(int i = 0; i < grammar.Vt.size() - 1; i++)
        output << grammar.Vt[i] << ", ";
    output << grammar.Vt[grammar.Vt.size() - 1] << " \n";

    output << "S: " << grammar.S << " \n";

    output << "P: \n";
    for(auto& u_v : grammar.P)
        output << u_v.first << " -> " << u_v.second << " \n";

    return output;
}

std::istream& operator>>(std::istream& input, Grammar& grammar) {
    try {
        std::string input_str;

        input >> input_str;
        int VnSize = std::stoi(input_str);
        for(int i = 0; i < VnSize; i++) {
            input >> input_str;
            grammar.Vn.push_back(input_str[0]);
        }

        input >> input_str;
        int VtSize = std::stoi(input_str);
        for(int i = 0; i < VtSize; i++) {
            input >> input_str;
            grammar.Vt.push_back(input_str[0]);
        }

        input >> input_str;
        grammar.S = input_str[0];

        input >> input_str;
        int PSize = std::stoi(input_str);
        for(int i = 0; i < PSize; i++) {
            std::string u, v;
            input >> u >> v;
            grammar.P.push_back({u, v});
        }
    }
    catch(std::invalid_argument) {
        std::cerr << "the file is either empty or doesnt contain the right data..";
        exit(1);
    }
    return input;
}

std::vector<char> Grammar::GetVn() const {
    return Vn;
}

std::vector<char> Grammar::GetVt() const {
    return Vt;
}

char Grammar::GetS() const {
    return S;
}

std::vector<std::pair<std::string, std::string>> Grammar::GetP() const {
    return P;
}

int Grammar::randomIntFrom0untilN(int n) {
    std::random_device random;
    std::default_random_engine randomer{random()};
    std::uniform_int_distribution<int> range(0, n - 1);
    return range(randomer);
}
