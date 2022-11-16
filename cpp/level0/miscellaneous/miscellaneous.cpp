#include <iostream>
#include <vector>
#include <random>

class Algorithms{
public:
	void binarySearch(){
		std::vector<int> arr{2,4,4,5,8,9,12,13,13,15,18};
		int a = 13;
		if(binarySearch(arr, 0, arr.size() - 1, a) != -1) std::cout << a << " has been found. \n";
		else std::cout << a << " has NOT been found..\n";
	}

private:
	int binarySearch(std::vector<int> arr, int left, int right, int a){
		if(left > right) return -1;
		int middle = (left + right) / 2;
		if(arr[middle] == a) return middle;
		if(a < arr[middle]) return binarySearch(arr, left, middle - 1, a);
		return binarySearch(arr, middle + 1, right, a);
	}
	//iterative version
	/*int binarySearch(std::vector<int> arr, int low, int high, int x){
		while(low <= high){
			int mid = low + (high - low) / 2;
			if(arr[mid] == x)
				return mid;
			if(arr[mid] < x)
				low = mid + 1;
			else
				high = mid - 1;
		}
		return -1;
	}*/
}alg;

class Others{
public:
	int generateRandomNbBtwn1andN(int n){
		std::random_device random;
		std::default_random_engine randomer{random()};
		std::uniform_int_distribution<int> range(1, n);
		return range(randomer);
	}
}others;


int main(){
	for(int i = 0; i < 100; i++)
		std::cout<<others.generateRandomNbBtwn1andN(100)<<"\n";
}
