#include <iostream>
#include <vector>


class Lot1{
public:
	void shortestServingTime(){
		std::vector<int> customerTime = {5, 10, 3};
		bool atLeast1Swap = true;
		while(atLeast1Swap){
			atLeast1Swap = false;
			for(int i = 0; i < customerTime.size() - 1; i++){
				if(customerTime[i] > customerTime[i + 1]){
					atLeast1Swap = true;
					std::swap(customerTime[i], customerTime[i + 1]);
				}
			}
		}
		int sum = 0, nb = customerTime.size();
		for(int i = 0; i < customerTime.size(); i++)
			sum += nb-- * customerTime[i];
		std::cout << sum;
	}
}lot1;

int main(){
	lot1.shortestServingTime();
}
