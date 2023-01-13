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
