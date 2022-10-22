#include <iostream>

void reverseOfANumber(){
	int a = 12345, rev = 0, a2;
	for(a2 = a; a2 != 0; a2 /= 10)
		rev = rev * 10 + a2 % 10;
	std::cout << rev << "\n";
}

void checkIfPalindrome(){
	int a = 2311132, rev = 0, a2;
	for(a2 = a; a2 != 0; a2 /= 10)
		rev = rev * 10 + a2 % 10;
	if(a == rev) std::cout << "the number " << a << " is palindrome. \n";
	else std::cout << "the number " << a << " is NOT palindrome.. \n";
}

void checkIfNumberIsPrime(){
	int a = 43;
	if(a <= 1){
		std::cout << "the number is NOT prime.. \n";
		return;
	}
	if(a == 2 || a == 3){
		std::cout << "the number is prime. \n";
		return;
	}
	// This is checked so that we can skip middle five numbers in below loop
	if(a % 2 == 0 || a % 3 == 0){
		std::cout << "the number is NOT prime. \n";
		return;
	}
	// Using concept of prime number can be represented in form of (6*n + 1) or(6*n - 1) hence
	// we have to go for every multiple of 6 and prime number would always be 1 less or 1 more than the multiple of 6.
	for(int i = 5; i * i <= a; i += 6)
		if(a % i == 0 || a % (i + 2) == 0){
			std::cout << "the number is NOT prime.. \n";
			return;
		}
	std::cout << "the number is prime. \n";
}

void checkIfNumberIsAPerfectNumber(){
	int a = 45, a2 = 0;
	for(int i = 1; i <= a / 2; i++)
		if(a % i == 0)
			a2 += i;
	if(a2 == a)
		std::cout << "the number is perfect. \n";
	else
		std::cout << "the number is NOT perfect.. \n";
}

void primeFactorization(){
	int a = 5, i, exp = 0;
	while(a % 2 == 0){
		a /= 2;
		exp++;
	}
	if(exp >= 1)
		std::cout << 2 << "^" << exp << "\n";
	for(i = 3, exp = 0; a != 1; i += 2, exp = 0){
		while(a % i == 0){
			a /= i;
			exp++;
		}
		if(exp >= 1)
			std::cout << i << "^" << exp << "\n";
	}
}

int gcd(int a, int b){
	if(a == 0)
		return b;
	gcd(b % a, a);
}
void gcd(){
	int a = 33, b = 15;
	std::cout << gcd(33, 15);
}

int lcm(int a, int b){
	return (a * b) / gcd(a, b);
}
void lcm(){
	int a = 33, b = 15;
	std::cout << lcm(33, 15);
}

void coprime(int a, int b){
	if(gcd(a, b) == 1)
		std::cout << "the two numbers are coprime";
	else
		std::cout << "the two numbers are not coprime";
}

int main(){
	checkIfNumberIsPrime();
}