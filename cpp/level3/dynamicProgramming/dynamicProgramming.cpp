#include <iostream>
#include <vector>
#include <tuple>

class Class1{
	long long fibonacci(int a, std::vector<std::pair<int, long long>>& holder){
		for(int i = 0; i < holder.size(); i++)
			if(a == holder[i].first)
				return holder[i].second;
		if(a == 0) return 0;
		if(a == 1) return 1;
		holder.emplace_back(a, (fibonacci(a - 1, holder) + fibonacci(a - 2, holder)));
		return holder[holder.size() - 1].second;
	}
	//iterative version
	/*int fibonacci(int a, std::vector<std::pair<int, long long>>& holder){
		holder.emplace_back(0, 0);
		holder.emplace_back(1, 1);
		for(int i = 2; i <= a; i++)
			holder.emplace_back(i, (long long) (holder[i - 1].second + holder[i - 2].second));
		return holder[holder.size() - 1].second;
	}*/

	long long gridTraveler(int n, int m, std::vector<std::tuple<int, int, long long>>& holder){
		for(int i = 0; i < holder.size(); i++){
			if(std::get<0>(holder[i]) == n && std::get<1>(holder[i]) == m ||
			   std::get<0>(holder[i]) == m && std::get<1>(holder[i]) == n)
				return std::get<2>(holder[i]);
		}
		if(n == 0 || m == 0) return 0;
		if(n == 1 && m == 1) return 1;
		holder.emplace_back(n, m, gridTraveler(n - 1, m, holder) + gridTraveler(n, m - 1, holder));
		return std::get<2>(holder[holder.size() - 1]);
	}

	bool canSum(int targetSum, std::vector<int> numbers, std::vector<std::pair<int, bool>>& holder){
		for(auto a : holder)
			if(targetSum == a.first)
				return a.second;
		if(targetSum == 0) return true;
		if(targetSum < 0) return false;
		for(auto a : numbers){
			int remainder = targetSum - a;
			if(canSum(remainder, numbers, holder) == true){
				holder.push_back({targetSum, true});
				return true;
			}
		}
		holder.push_back({targetSum, false});
		return false;
	}
public:
	void fibonacci(){
		std::vector<std::pair<int, long long>> holder;
		int a = 40;
		std::cout << fibonacci(a, holder);
	}

	void gridTraveler(){
		int n = 18, m = 18;
		std::vector<std::tuple<int, int, long long>> holder;
		std::cout << gridTraveler(n, m, holder);
	}

	void canSum(){
		std::vector<std::pair<int, bool>> holder;
		std::cout << canSum(7, {2,3}, holder) << "\n";
		holder.resize(0);
		std::cout << canSum(7, {5,3,4,7}, holder) << "\n";
		holder.resize(0);
		std::cout << canSum(7, {2,4}, holder) << "\n";
		holder.resize(0);
		std::cout << canSum(8, {2,3,5}, holder) << "\n";
		holder.resize(0);
		std::cout << canSum(300, {7,14}, holder) << "\n";
		holder.resize(0);
	}
}obj1;

int main(){
	obj1.canSum();
}
//https://www.youtube.com/watch?v=oBt53YbR9Kk