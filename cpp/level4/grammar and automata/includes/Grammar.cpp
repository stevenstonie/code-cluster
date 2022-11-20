#include "Grammar.h"

#include <iostream>
#include <random>

Grammar::Grammar() = default;

bool Grammar::VerifyGrammar(){
	//each element has to be NOT null
	if(Vn.empty() || Vt.empty() || S == 0 || P.empty())
		return false;

	// Vn should not share elements with Vt
	for(auto& vn_elem : Vn){
		auto findIfElemIsShared = std::find(Vt.begin(), Vt.end(), vn_elem);
		if(findIfElemIsShared != Vt.end())
			return false;
	}

	// S has to be an element from Vn
	{
		auto find_if_S_is_in_Vn = std::find(Vn.begin(), Vn.end(), S);
		if(find_if_S_is_in_Vn == Vn.end())
			return false;
	}

	// every u of P has at least an element from Vn
	for(auto& u_v : P){
		bool atLeastOneChrOfuFoundInVn = false;
		for(auto& chrOfu : u_v.first){
			auto findChrInVn = std::find(Vn.begin(), Vn.end(), chrOfu);
			if(findChrInVn != Vn.end()){
				atLeastOneChrOfuFoundInVn = true;
				break;
			}
		}
		if(atLeastOneChrOfuFoundInVn != true)
			return false;
	}

	// u and v need to have all elements from Vn OR Vt
	for(auto& u_v : P){
		// for every pair u and v of P check if every element of them is found in either Vn or Vt.
		for(auto& chrOfu : u_v.first){
			auto findChrInVn = std::find(Vn.begin(), Vn.end(), chrOfu);
			if(findChrInVn == Vn.end()){
				auto findChrInVt = std::find(Vt.begin(), Vt.end(), chrOfu);
				if(findChrInVt == Vt.end())
					return false;
			}
		}
		for(auto& chrOfv : u_v.second){
			auto findChrInVn = std::find(Vn.begin(), Vn.end(), chrOfv);
			if(findChrInVn == Vn.end()){
				auto findChrInVt = std::find(Vt.begin(), Vt.end(), chrOfv);
				if(findChrInVt == Vt.end())
					return false;
			}
		}
	}
	return true;
}

// a grammar is regular if A->xB or A->Bx or A->x (general notation: u->v). a grammar is also generative if only A->xB or A->x
bool Grammar::IsRegular(){
	// for every u_v pair of P
	for(auto& u_v : P){
		// check if u is longer than 1 elem or if v is longer than 2 elements
		if(u_v.first.size() > 1 || u_v.second.size() > 2)
			return false;

		// check if u is part of Vn
		auto uInVn = std::find(Vn.begin(), Vn.end(), u_v.first[0]);    // if at least one elem of u is part of Vn then i believe this shouldnt be checked here
		if(uInVn == Vn.end())
			return false;

		// if v's size is one it has to be part of Vt
		if(u_v.second.size() == 1){
			auto vInVt = std::find(Vt.begin(), Vt.end(), u_v.second[0]);
			if(vInVt == Vt.end())
				return false;
		}

		// else if v's size is two then one elem has to be from Vt and the other one from Vn
		if(u_v.second.size() == 2){
			// search v's first elem in Vt
			auto chrInVt = std::find(Vt.begin(), Vt.end(), u_v.second[0]);
			// if it is not in Vt then check if it is in Vn and if the other element is from Vt
			if(chrInVt == Vt.end()){
				auto chrInVn = std::find(Vn.begin(), Vn.end(), u_v.second[0]);
				if(chrInVn == Vn.end())
					return false;
				else{
					auto chrInVt = std::find(Vt.begin(), Vt.end(), u_v.second[1]);
					if(chrInVt == Vt.end())
						return false;
				}
			}
			//if it is in Vt check if the other one is Vn
			else{
				auto chrInVn = std::find(Vn.begin(), Vn.end(), u_v.second[1]);
				if(chrInVn == Vn.end())
					return false;
			}
		}
	}
	return true;
}

// start with S and work your way up to the final word
std::string Grammar::GenerateWord(){
	// 'allCombinationsOfPMade' holds the combination of all transitions of P that will be made
	// 'PPoolOfCurrentPossibleTransitions' holds the current possible transitions for every instance of the currentWord
	std::vector<std::pair<std::string, std::string>> allCombinationsOfPMade, PPoolOfCurrentPossibleTransitions;
	std::string currentWord(1, this->S);   //to_string() makes it 83 instead of 'S'. why does to_string() look at the ascii number and not its representation
	int limitOfTransitions = 100;   // limit the transitions in case the operation runs forever
	while(--limitOfTransitions){
		PPoolOfCurrentPossibleTransitions.clear();
		// check all u's of P if they are in the currentWord. if yes add the pair to the PPool
		for(auto& u_v : P){
			auto uInCurrentWord = std::find(currentWord.begin(), currentWord.end(), u_v.first[0]);
			if(uInCurrentWord != currentWord.end())
				PPoolOfCurrentPossibleTransitions.push_back(u_v);
		}
		// if PPool is empty then another transition on currentWord is not possible -> break;
		if(PPoolOfCurrentPossibleTransitions.empty())
			break;
		// else choose randomly between the available transitions and save the one used
		else{
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

void Grammar::PrintGrammar(){
	// use the '<<' operator overloading
}

void Grammar::ReadGrammar(){
	// read from keyboard
}

std::ostream& operator<<(std::ostream& output, const Grammar& grammar){
	// print the grammar
}

std::istream& operator>>(std::istream& input, Grammar& grammar){
	// take input from file and read the grammar from it
}

int Grammar::randomIntFrom0untilN(int n){
	std::random_device random;
	std::default_random_engine randomer{random()};
	std::uniform_int_distribution<int> range(0, n - 1);
	return range(randomer);
}
