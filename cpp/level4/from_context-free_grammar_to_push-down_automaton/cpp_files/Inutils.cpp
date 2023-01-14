#include "../header_files/Inutils.hpp"

int randomIntFrom0untilN(int n) {
	std::random_device random;
	std::default_random_engine randomer{random()};
	std::uniform_int_distribution<int> range(0, n - 1);
	return range(randomer);
}

std::vector<std::string> convertStringToVectorOfStrings(std::string string){
	std::vector<std::string> vectorOfStrings;
	for(const auto& chr : string)
		vectorOfStrings.push_back(std::string(1, chr));

	return vectorOfStrings;
}

int getIndexOfStringInVector(const std::string& string, const  std::vector<std::string>& vector){
	for(int i = 0; i < vector.size(); i++){
		if(vector[i] == string)
			return i;
	}
	return -1;
}

bool checkIfFirstStringIsSmallerThanSecond(const std::string& string1, const std::string& string2){
	if(string1[0] == string2[0]){
		return string1[1] < string2[1];
	}
	else{
		return string1[0] < string2[0];
	}
}