#include <iostream>
#include <vector>
#include <random>
/*in order have all the sorting algorithms cleanly presented i placed the "real" sorting algorithms inside the
* private part of the class with an additional 'uselessVar' so that i can call each one of them from
* their own overloaded functions inside the public part. the 'uselessVar' should be deleted
* when borrowing any of the sorting algorithms presented.
*/

class SortingAlgorithms{
	void selectionsort(std::vector<int>& arr, bool uselessVar){
		int i_min;
		for(int i = 0; i < arr.size() - 1; i++){
			i_min = arr[i];
			for(int j = i + 1; j < arr.size(); j++)
				if(arr[j] <= arr[i_min])
					i_min = j;
			std::swap(arr[i], arr[i_min]);
		}
	}

	void bubblesort(std::vector<int>& arr, bool uselessVar){
		bool isUnsorted = true;
		while(isUnsorted == true){
			isUnsorted = false;
			for(int i = 0; i < arr.size() - 1; i++){
				if(arr[i + 1] < arr[i]){
					isUnsorted = true;
					std::swap(arr[i], arr[i + 1]);
				}
			}
		}
	}

	/* This function takes the last element as pivot, places
	the pivot element at its correct position in sorted
	array, and places all the smaller elements than the pivot
	to the left of it and all the greater elements to the right
	of it */
	int partition(std::vector<int>& arr, int firstindex, int lastindex){
		int j, pivot = arr[lastindex], i = firstindex;		// Index of smaller element
		for(j = firstindex; j <= lastindex - 1; j++){
			// If current element is smaller than the pivot
			if(arr[j] < pivot)
				std::swap(arr[i++], arr[j]);
		}
		std::swap(arr[i], arr[lastindex]);		//its arr[lastindex] instead of pivot because the function swaps the elements on the indexes
		return (i);								//("pointed" by the indexes).std::swap() looks at the indexes not at the elements themselves
	}
	//main fuction of quicksort
	void quicksort(std::vector<int>& arr, int firstindex, int lastindex, bool uselessVar){
		if(firstindex < lastindex){
			// pi is partitioning index, arr[pi] is at the right place
			int pi = partition(arr, firstindex, lastindex);
			// Separately sort elements before partition and after partition
			quicksort(arr, firstindex, pi - 1, true);
			quicksort(arr, pi + 1, lastindex, true);
		}
	}

	//// Merges two subarrays of arr. First subarray is arr[firstindex..mid], Second subarray is arr[mid+1..lastindex]
	//void merge(std::vector<int>& arr, int firstindex, int mid, int lastindex){
	//	int i, j, k;
	//	int n = mid - firstindex + 1;
	//	int m = lastindex - mid;
	//	// create temp arrays
	//	int larr[n], rarr[m];
	//	// Copy data to temp arrays larr[] and rarr[]
	//	for(i = 0; i < n; i++)
	//		larr[i] = arr[firstindex + i];
	//	for(j = 0; j < m; j++)
	//		rarr[j] = arr[mid + 1 + j];
	//	// Merge the temp arrays back into arr[firstindex..lastindex]
	//	i = 0; // Initial index of first subarray
	//	j = 0; // Initial index of second subarray
	//	// Initial index of merged subarray
	//	for(k = firstindex; i < n && j < m; k++){
	//		if(larr[i] <= rarr[j])
	//			arr[k] = larr[i++];
	//		else
	//			arr[k] = rarr[j++];
	//	}
	//	// Copy the remaining elements of larr[], if there are any
	//	while(i < n){
	//		arr[k++] = larr[i++];
	//	}
	//	// Copy the remaining elements of rarr[], if there are any
	//	while(j < m){
	//		arr[k++] = rarr[j++];
	//	}
	//}
	////firstindex is for left index and lastindex is right index of the sub-array of arr to be sorted
	//void mergesort(std::vector<int> arr, int firstindex, int lastindex, bool uselessVar){
	//	if(firstindex < lastindex){
	//		//Same as (firstindex+lastindex)/2, but avoids overflow for
	//		//large firstindex and lastindex
	//		int mid = firstindex + (lastindex - firstindex) / 2;
	//		//Sort first and second halves
	//		mergesort(arr, firstindex, mid, true);
	//		mergesort(arr, mid + 1, lastindex, true);
	//		merge(arr, firstindex, mid, lastindex);
	//	}
	//}

	void heapify(std::vector<int>& arr, int rangeOfAction, int i_parent){
		int i_largest = i_parent, i_left = i_parent * 2 + 1, i_right = i_parent * 2 + 2;
		if(i_left < rangeOfAction && arr[i_left] > arr[i_largest])
			i_largest = i_left;
		if(i_right<rangeOfAction && arr[i_right]>arr[i_largest])
			i_largest = i_right;
		if(i_largest != i_parent){
			std::swap(arr[i_parent], arr[i_largest]);
			heapify(arr, rangeOfAction, i_largest);
		}
	}
	//main function of heapsort
	void heapsort(std::vector<int>& arr, bool uselessVar){
		//build the max heap (max heap the nodes that are parents --> n/2-1 are parents)
		for(int i = arr.size() / 2 - 1; i >= 0; --i)
			heapify(arr, arr.size(), i);
		//one by one ignore the elements at the end until the first one
		for(int i = arr.size() - 1; i > 0; i--){
			//move current root to the end
			std::swap(arr[0], arr[i]);
			//heapifying the root element will get the greatest elem at the root
			heapify(arr, i, 0);
		}
	}
	//implementing heap sort. 
	/*steps:
	- build the max heap -> call heapify()(it makes the tree a heap) for half of the array (only the first half elements are parents).
	BREAK;
	- reduce the size of the heap by 1
	- swap first item with last
	- heapify() the root
	- repeat the last three actions with 'rangeOfAction' from n-1 to 0 (sorting the tree from the bottom to the top).
	!!! heapSort(&arr) -> first builds a max heap. then continuously swaps the root with the last elem and heapifies the root while the 'rangeOfAction' becomes smaller
	!!! heapify(&arr, rangeOfAction, indexOfRoot) -> finds if one of the children are greater than the parent (if yes then
		assign the index to 'i_largerst'). if the parent hasnt been the largest then swap the values of the indexes and
		recursively call the function with the swapped child. (the two ifs assigns the index of the greatest child to
		the 'i_largest' but also serve the purpose of checking if the parent didnt exceed the 'rangeOfAction')
	see: https://www.programiz.com/dsa/heap-sort
	*/

	int generateRandomNbBtwn0andn(int n){
		std::random_device random;
		std::default_random_engine randomer{random()};
		std::uniform_int_distribution<int> probability(0, n);
		return probability(randomer);
	}
	void bogosort(std::vector<int>& arr, bool uselessVar){
		bool isSorted = true;
		for(int i = 1; i < arr.size() && isSorted == true; i++)
			if(arr[i] < arr[i - 1])
				isSorted = false;
		while(isSorted == false){
			isSorted = true;
			for(int i = 0; i < arr.size(); i++)
				std::swap(arr[i], arr[generateRandomNbBtwn0andn(arr.size() - 1)]);
			for(int i = 1; i < arr.size() && isSorted == true; i++)
				if(arr[i] < arr[i - 1])
					isSorted = false;
		}
	}
public:
	void selectionsort(std::vector<int>& arr){
		selectionsort(arr, true);
	}

	void bubblesort(std::vector<int>& arr){
		bubblesort(arr, true);
	}

	void quicksort(std::vector<int>& arr){
		quicksort(arr, 0, arr.size() - 1, true);
	}

	//void mergesort(std::vector<int>& arr){
	//	mergesort(arr, 0, arr.size() - 1, true);
	//}

	void heapsort(std::vector<int>& arr){
		heapsort(arr, true);
	}

	void bogosort(std::vector<int>& arr){
		bogosort(arr, true);
	}
}obj1;

int main(){
	std::vector<int> arr{7,2,6,1,2,6,4,8,6,5};
	obj1.bogosort(arr);
	for(auto a : arr) std::cout << a << " ";
}

//!!!!!!!!finish mergesort
