#include "Grammar.h"

Grammar::Grammar() = default;

bool Grammar::VerifyGrammar(){
	// each element has to be NOT null
	if(Vn.empty() || Vt.empty() || S == NULL || P.empty())
		return false;

	// Vn should not share elements with Vt
	for(auto vn_elem : Vn){
		auto findIfElemIsShared = std::find(Vt.begin(), Vt.end(), vn_elem);
		if(findIfElemIsShared != Vt.end())
			return false;
	}

	// S should be an element from Vn
	{
		auto find_if_S_is_in_Vn = std::find(Vn.begin(), Vn.end(), S);
		if(find_if_S_is_in_Vn == Vn.end())
			return false;
	}

	// every u of P has at least an element from Vn
	for(auto& u_v : P){
		bool atLeastOneChrOfuFoundInVn = false;
		for(auto chrOfu : u_v.first){
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
		for(auto chrOfu : u_v.first){
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
		// check if u is longer than 1 elem or if v is longer than 2 elements
		// check if u is part of Vn
		// if v's size is one it has to be part of Vt
		// else if v's size is two then one elem has to be from Vt and the other one from Vn

	return true;
}

// start with S and work your way up to the final word
std::string Grammar::GenerateWord(){
	// create a vector that holds the combination of all transitions of P that will be made
	// and another one that holds the current possible transitions for every instance of the currentWord

	// make a while with max 100 iterations in case loop runs forever
		// check all u's of P if they are in the currentWord. if yes add the pair to the PPool
		// if PPool is empty then another transition on currentWord is not possible -> break;
		// else choose randomly between the available transitions and save the one used

	return "test";
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