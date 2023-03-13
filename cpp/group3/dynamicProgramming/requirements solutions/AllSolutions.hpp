#pragma once

#include <iostream>
#include <tuple>
#include <vector>

class AllSolutions {
public:
	void fibonacci();

	void gridTraveler();

	void canSum();
private:
    long long fibonacci(int a, std::vector<std::pair<int, long long>>& holder);

    long long gridTraveler(int n, int m, std::vector<std::tuple<int, int, long long>>& holder);

    bool canSum(int targetSum, std::vector<int> numbers, std::vector<std::pair<int, bool>>& holder);
};