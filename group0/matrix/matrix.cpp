#include <iostream>
#include <vector>

class DynamicMatrix{
public:
	int** allocateMatrixDynamically(int n, int m){
		int** matrix = new int* [n];
		for(int i = 0; i < n; i++)
			matrix[i] = new int[m];
		return matrix;
	}

	void readMatrix(int** matrix, int n, int m){
		for(int i = 0; i < n; i++)
			for(int j = 0; j < m; j++){
				std::cout << "m[" << i << "][" << j << "]:";
				std::cin >> matrix[i][j];
			}
	}

	void printMatrix(int** matrix, int n, int m){
		for(int i = 0; i < n; i++){
			for(int j = 0; j < m; j++)
				std::cout << matrix[i][j] << " ";
			std::cout << "\n";
		}
	}

	void deleteDynamicMatrix(int** matrix, int n){
		for(int i = 0; i < n; i++)
			delete[] matrix[i];
		delete[] matrix;
	}

	void allocateMatrixDynamically(){
		int n = 4, m = 5;
		int** matrix = allocateMatrixDynamically(n, m);
		readMatrix(matrix, n, m);
		printMatrix(matrix, n, m);
		deleteDynamicMatrix(matrix, n);
	}
}dynmatr;

class PrintMatr{
	void printMatrix(std::vector<std::vector<int>> matrix){
		for(int i = 0; i < matrix.size(); std::cout << "\n", i++)
			for(int j = 0; j < matrix[i].size(); j++)
				std::cout << matrix[i][j] << " ";
	}
public:
	void printMatrixInSpiral(){
		std::vector<std::vector<int>> matrix{{11,22,33,44,55}, {23,34,45,56,67}, {78,89,90,10,12}, {97,95,93,91,80}, {75,73,71,62,68}};
		std::cout << "original matrix:\n";
		printMatrix(matrix);
		std::cout << "\n";

		std::cout << "matrix printed in spiral:\n";
		int sideLength = matrix.size() - 1, k, i, j;
		for(k = 1, i = j = 0; k <= sideLength; k++){
			std::cout << matrix[i][j] << " ";
			j++;
		}
		for(;;){
			for(k = 1; k <= sideLength; k++){		//down
				std::cout << matrix[i][j] << " ";
				i++;
			}
			for(k = 1; k <= sideLength; k++){		//left
				std::cout << matrix[i][j] << " ";
				j--;
			}
			sideLength--;
			if(sideLength == 0){					//check if done
				std::cout << matrix[i][j] << " ";
				break;
			}

			for(k = 1; k <= sideLength; k++){		//up
				std::cout << matrix[i][j] << " ";
				i--;
			}
			for(k = 1; k <= sideLength; k++){		//right
				std::cout << matrix[i][j] << " ";
				j++;
			}
			sideLength--;
			if(sideLength == 0){					//check if done
				std::cout << matrix[i][j];
				break;
			}
		}
	}

	void printEveryTriangleInTheMatrix(){
		std::vector<std::vector<int>> matrix{{11,22,33,44,55}, {23,34,45,56,67}, {78,89,90,10,12}, {97,95,93,91,80}, {75,73,71,62,68}};
		unsigned short i, j, i2;
		std::cout << "\nupper triangle\n";
		for(i = 0; i < matrix.size() / 2 + matrix.size() % 2; i++){
			for(i2 = 0; i2 < i; i2++) std::cout << "  ";
			for(j = i; j < matrix.size() - i; j++){
				std::cout << matrix[i][j] << " ";
			}
			std::cout << "\n";
		}

		std::cout << "\nlower triangle\n";
		for(i = matrix.size() / 2; i < matrix.size(); i++){
			for(i2 = 0; i2 < matrix.size() - 1 - i; i2++) std::cout << "  ";
			for(j = matrix.size() - i - 1; j <= i; j++){
				std::cout << matrix[i][j] << " ";
			}
			std::cout << "\n";
		}

		std::cout << "\nleft triangle\n";
		for(i = 0; i < matrix.size() / 2; i++){
			for(j = 0; j <= i; j++){
				std::cout << matrix[i][j] << " ";
			}
			std::cout << "\n";
		}
		for(i = matrix.size() / 2; i < matrix.size(); i++){
			for(j = 0; j < matrix.size() / 2 - (i - matrix.size() / 2) + matrix.size() % 2; j++){
				std::cout << matrix[i][j] << " ";
			}
			std::cout << "\n";
		}

		std::cout << "\nright triangle\n";
		for(i = 0; i < matrix.size() / 2; i++){
			for(i2 = matrix.size() / 2; i2 < matrix.size() - 1 - i; i2++) std::cout << "  ";
			for(j = matrix.size() - 1 - i; j < matrix.size(); j++)
				std::cout << matrix[i][j] << " ";
			std::cout << "\n";
		}
		for(i = matrix.size() / 2; i < matrix.size(); i++){
			for(i2 = matrix.size() / 2; i2 < i; i2++) std::cout << "  ";
			for(j = i; j < matrix.size(); j++)
				std::cout << matrix[i][j] << " ";
			std::cout << "\n";
		}

		std::cout << "\ntrangle above main diagonal\n";
		for(i = 0; i < matrix.size(); i++){
			for(i2 = 0; i2 < i; i2++) std::cout << "  ";
			for(j = i; j < matrix.size(); j++)
				std::cout << matrix[i][j] << " ";
			std::cout << "\n";
		}

		std::cout << "\ntriangle above secondary diagonal\n";
		for(i = 0; i < matrix.size(); i++){
			for(j = 0; j < matrix.size() - i; j++)
				std::cout << matrix[i][j] << " ";
			std::cout << "\n";
		}

		std::cout << "\ntriangle below main diagonal\n";
		for(i = 0; i < matrix.size(); i++){
			for(j = 0; j <= i; j++)
				std::cout << matrix[i][j] << " ";
			std::cout << "\n";
		}

		std::cout << "\ntriangle below secondary diagonal\n";
		for(i = 0; i < matrix.size(); i++){
			for(i2 = 0; i2 < matrix.size() - 1 - i; i2++) std::cout << "  ";
			for(j = matrix.size() - 1 - i; j < matrix.size(); j++)
				std::cout << matrix[i][j] << " ";
			std::cout << "\n";
		}
	}

}printMatr;

class MakeSomeMatrix{
public:
	void createMatrixOfType_1234_2123_3212_4321(){
		unsigned short n;
		std::cout << "n:"; std::cin >> n;
		unsigned short arr[10][10];
		for(unsigned short i = 0; i < n; i++)
			for(unsigned short j = 0; j <= i; j++)
				arr[i][j] = i - j + 1;
		for(unsigned short i = 0; i < n; i++)
			for(unsigned short j = i + 1; j < n; j++)
				arr[i][j] = j - i + 1;
		for(unsigned short i = 0; i < n; i++){
			for(unsigned short j = 0; j < n; j++)
				std::cout << arr[i][j] << " ";
			std::cout << "\n";
		}
	}
}makeMatr;

int main(){
	printMatr.printEveryTriangleInTheMatrix();
}