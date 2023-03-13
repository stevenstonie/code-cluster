#include <iostream>
#include <vector>
#include <string>
#include <random>

class Lot1_of_set1{
	bool canMove(std::string piece, std::string current, std::string target){
		char j1 = current[0], j2 = target[0];
		int i1 = current[1] - 48, i2 = target[1] - 48;
		if(piece == "pawn"){
			if(j1 == j2){
				if(i2 == i1 + 2 && i2 <= 4) return true;
				if(i2 == i1 + 1) return true;
			}
			return false;
		}
		else if(piece == "rook"){
			if(j2 == j1 || i2 == i1) return true;
			return false;
		}
		else if(piece == "knight"){
			if(j2 == j1 - 1 || j2 == j1 + 1)
				if(i2 == i1 - 2 || i2 == i1 + 2)
					return true;
			if(j2 == j1 - 2 || j2 == j1 + 2)
				if(i2 == i1 - 1 || i2 == i1 + 1)
					return true;
		}
		else if(piece == "bishop"){
			int dif = j2 - j1;
			if(j2 == j1 - dif)
				if(i2 == i1 - dif || i2 == i1 + dif)
					return true;
			if(j2 == j1 + dif)
				if(i2 == i1 - dif || i2 == i1 + dif)
					return true;
			return false;
		}
		else if(piece == "queen"){
			if(j2 == j1)
				return true;
			if(i2 == i1)
				return true;
			int dif = j2 - j1;
			if(j2 == j1 - dif)
				if(i2 == i1 - dif || i2 == i1 + dif)
					return true;
			if(j2 == j1 + dif)
				if(i2 == i1 - dif || i2 == i1 + dif)
					return true;
			return false;
		}
		else if(piece == "king"){
			if(j2 == j1 - 1)
				if(i2 == i1 - 1 || i2 == i1 || i2 == i1 + 1)
					return true;
			if(j2 == j1)
				if(i2 == i1 - 1 || i2 == i1 + 1)
					return true;
			if(j2 == i1 + 1)
				if(i2 == i1 - 1 || i2 == i1 || i2 == i1 + 1)
					return true;
		}
	}
public:
	void caesarcipher(){
		std::string text = "this is a sample text: i like big buffed men. that was a joke. ";
		int shiftNumber = 7;
		std::cout << text << " \n" << "the text: shifted with " << shiftNumber << " letters: \n";
		for(char& c : text)
			if(isalpha(c))
				c = (c <= 90) ? 65 + ((c - 'A' + shiftNumber) % 26) : 97 + ((c - 'a' + shiftNumber) % 26);
		std::cout << text << "\n";
	}


	void checkIfUnder21blackjack(){
		std::vector<char> cards = {'K', 'K', 'K'};
		int sumofcards = 0, countaces = 0;
		for(char c : cards){
			sumofcards += (isdigit(c) ? (c - '0') : 0) + (c == 'J' || c == 'K' || c == 'Q' || c == 'j' || c == 'k' || c == 'q') * 10;
			countaces += (c == 'a' || c == 'A') ? 1 : 0;
		}
		while(countaces > 0){
			if(sumofcards + 11 + countaces - 1 <= 21){
				sumofcards += 11;
				countaces--;
			}
			else
				break;
		}
		sumofcards += countaces;
		if(sumofcards <= 21) std::cout << "the value of the cards is under or equal to 21. \n";
		else std::cout << "the value of the cards exceeds 21!!! \n";
	}


	void checkIfPieceCanMove(){
		std::string piece{"rook"}, current{"a8"}, target{"h8"};
		if(canMove(piece, current, target))
			std::cout << "the " << piece << " can move from " << current << " to " << target << " \n";
		else
			std::cout << "the " << piece << " from " << current << " to " << target << " is an invalid move!!! \n";
	}


	void groupNeighbouringChars(){
		std::string text = "paapppy the cattt";
		if(text == "") std::cout << "";
		else{
			char lastc = '\n';
			int increment = 1;
			for(char c : text){
				if(c == lastc) increment++;
				else{
					std::cout << lastc;
					if(increment != 1){
						std::cout << "*" << increment;
						increment = 1;
					}
				}
				lastc = c;
			}
			std::cout << lastc;
			if(increment != 1) std::cout << "*" << increment << "\n";
		}
	}


	void countSieveOfErathostene(){
		int n = 1000; ++n;
		std::vector<bool> primeArr(n, true);
		for(int i = 2; i * i < n; i++)
			if(primeArr[i] == true)
				for(int ii = i * i; ii < n; ii += i)
					primeArr[ii] = false;
		int k = 0;
		for(int i = 2; i < n; i++)
			if(primeArr[i] == true)
				k++;
		std::cout << "there are " << k << " prime numbers up to " << n - 1 << "\n";
	}


	void countSharedLetters(){
		std::string str1 = "apple", str2 = "papi";
		int nbOfShared = 0;
		std::vector<char> passed;
		bool alreadyExists;
		for(char c1 : str1){
			alreadyExists = false;
			for(char c2 : passed)
				if(c2 == c1){
					alreadyExists = true;
					break;
				}
			if(!alreadyExists){
				passed.push_back(c1);
				for(char c2 : str2)
					if(c2 == c1){
						nbOfShared++;
						break;
					}
			}
		}
		std::cout << "there are " << nbOfShared << " shared letters between " << "\"" << str1 << "\"" << " and " << "\"" << str2 << "\"" << "\n";
	}


	void letterDistanceBtwnTwoWords(){
		std::string word1 = "house", word2 = "fly";
		if(word2.size() < word1.size()) std::swap(word1, word2);
		int dist = 0, letterDist = 0;
		for(int i = 0; i < word1.size(); i++){
			letterDist = word1[i] - word2[i];
			if(letterDist < 0) letterDist -= 2 * letterDist;
			dist += letterDist;
		}
		if(dist < 0) dist += 2 * dist;
		dist += word2.size() - word1.size();
		std::cout << "the distance between " << "\"" << word1 << "\"" << " and " << "\"" << word2 << "\"" << " is " << dist << "\n";
	}


	void checkIfNumberIsSmiley(){
		long long number = 8873459;
		if(number < 100){
			std::cout << "a number with less than 3 digits cannot be smiley.. \n";
			return;
		}
		int powOf10 = 1;
		for(; number / powOf10 != 0; powOf10 *= 10);
		powOf10 /= 100;
		if(number / powOf10 % 10 >= number / (powOf10 * 10)){
			std::cout << "the left part of the number is not smiley.. \n";
			return;
		}
		bool notSm = false;
		for(powOf10 /= 10; powOf10 != 0; powOf10 /= 10){
			if(number / powOf10 % 10 == number / (powOf10 * 10) % 10){
				notSm = true;
				break;
			}
			if(number / powOf10 % 10 > number / (powOf10 * 10) % 10)
				break;
		}
		for(powOf10 /= 10; powOf10 != 0; powOf10 /= 10){
			if(number / powOf10 % 10 <= number / (powOf10 * 10) % 10){
				notSm = true;
				break;
			}
		}
		if(notSm) std::cout << "the number " << number << " is not smiley..\n";
		else std::cout << "the number " << number << " is smiley. \n";
	}


	void rootsOfQuadraticEquation(){
		int a = -2, b = 5, c = 2;
		if(a == 0){
			std::cout << "this is not a quadratic equation.";
			return;
		}
		float discriminant, x1, x2;
		discriminant = (float) (b * b - 4 * a * c);
		if(discriminant > 0){
			x1 = (-b + sqrt(discriminant)) / (2 * a);
			x2 = (-b - sqrt(discriminant)) / (2 * a);
			std::cout << "roots are real and different. \n";
			std::cout << "x1=" << x1 << "\n";
			std::cout << "x1=" << x2 << "\n";
		}
		else if(discriminant == 0){
			std::cout << "roots are real and same. \n";
			x1 = (-b + sqrt(discriminant)) / (2 * a);
			std::cout << "x1=x2=" << x1 << "\n";
		}
		else{
			int realpart, imaginarypart;
			realpart = (float) -b / (2 * a);
			imaginarypart = sqrt(-discriminant) / (2 * a);
			std::cout << "roots are complex and different.\n";
			std::cout << "x1=" << realpart << "+" << imaginarypart << "i\n";
			std::cout << "x2=" << realpart << "-" << imaginarypart << "i\n";
		}
	}


	void replaceLettersWithPosInAlphabet(){
		std::string text = "No i didnt sleep on the bed, because IM not gay.", text2 = "";
		int pos;
		for(char c : text){
			if(isalpha(c)){
				pos = (islower(c) ? c - 97 : c - 65) + 1;
				text2 += std::to_string(pos) + " ";
			}
		}
		std::cout << text2 << "\n";
	}


	class Nbhoods_streets_population{
		struct hoodstrasse{
			unsigned short noPers;
		};
		struct hood{
			std::vector<hoodstrasse> str;
		};

		short noCartiere(){
			std::random_device random;
			std::default_random_engine randomer{random()};
			std::uniform_int_distribution<int> probability(2, 13);
			unsigned short noCartiere = probability(randomer);
			std::cout << "nr de cartiere este de:" << noCartiere << "\n";
			return noCartiere;
		}

		void citireHood(std::vector<hood>& ngbHood){
			for(short i = 0; i < ngbHood.size(); std::cout << "\n", i++){
				std::cout << "introdu nr de strazi al cartierului no." << i << ":";
				short a;
				std::cin >> a;
				ngbHood[i].str.resize(a);
				for(short j = 0; j < ngbHood[i].str.size(); j++){
					std::cout << "persoane pe str no." << j << ":";
					std::cin >> ngbHood[i].str[j].noPers;
				}
			}
		}

		void subpoint_a(std::vector<hood>& ngbHood){
			for(short i = 0; i < ngbHood.size(); i++)
				for(short j = 0; j < ngbHood[i].str.size(); j++)
					if(ngbHood[i].str[j].noPers > 500)
						std::cout << i << " " << j << " " << ngbHood[i].str[j].noPers << "\n";
		}

		int partition(std::vector<hoodstrasse>& str, int firstindex, int lastindex){
			int j, i = firstindex, pivot = str[lastindex].noPers;
			for(j = firstindex; j <= lastindex - 1; j++)
				if(str[j].noPers > pivot)
					std::swap(str[i++].noPers, str[j].noPers);
			std::swap(str[i].noPers, str[lastindex].noPers);
			return i;
		}
		void subpoint_b(std::vector<hoodstrasse>& str, int firstindex, int lastindex){
			if(firstindex < lastindex){
				int pi = partition(str, firstindex, lastindex);
				subpoint_b(str, firstindex, pi - 1);
				subpoint_b(str, pi + 1, lastindex);
			}
		}

		void subpoint_c(std::vector<hood>& ngbHood){
			int sumOfMax = 0;
			for(short i = 0; i < ngbHood.size(); i++){
				int sumOfCurrStreet = 0;
				for(short j = 0; j < ngbHood[i].str.size(); j++)
					sumOfCurrStreet += ngbHood[i].str[j].noPers;
				if(sumOfCurrStreet > sumOfMax) sumOfMax = sumOfCurrStreet;
			}
			std::cout << sumOfMax;
		}

		void subpoint_extra(std::vector<hood>& ngbHood){
			for(int i = 0; i < ngbHood.size(); i++){
				for(int j = 0; j < ngbHood[i].str.size() - 1; j++){
					if(ngbHood[i].str[j].noPers <= 10){
						bool mergeable = true;
						while(mergeable){			//		here 'j' is the pivot place where the streets merge.
							if(ngbHood[i].str[j + 1].noPers <= 10 && ngbHood[i].str[j + 1].noPers != -1 && ngbHood[i].str[j].noPers + ngbHood[i].str[j + 1].noPers <= 100){
								ngbHood[i].str[j].noPers += ngbHood[i].str[j + 1].noPers;						//merge
								int jj = j + 1;													//shift left
								for(; jj < ngbHood[i].str.size() - 1 && ngbHood[i].str[jj].noPers != -1; jj++)
									ngbHood[i].str[jj].noPers = ngbHood[i].str[jj + 1].noPers;
								if(jj == ngbHood[i].str.size() - 1)		//sp case for the last street (it cant be equal to a nonexistent value)
									ngbHood[i].str[jj].noPers = -1;
							}
							else mergeable = false;
						}
					}
				}
			}
			std::cout << "neighbourhoods merged \n";
		}

		void subpoint_d(std::vector<hood>& ngbHood){
			for(int i = 0; i < ngbHood.size(); i++){
				int sumOfCurrentHood = 0;
				for(int j = 0; j < ngbHood[i].str.size(); j++) sumOfCurrentHood += ngbHood[i].str[j].noPers;
				ngbHood[i].str.resize(ngbHood[i].str.size() + 1);
				ngbHood[i].str[ngbHood[i].str.size() - 1].noPers = sumOfCurrentHood;
			}
			bool verif = true;
			while(verif){
				verif = false;
				for(int i = 0; i < ngbHood.size() - 1; i++){
					int lastElemFromRowi = ngbHood[i].str[ngbHood[i].str.size() - 1].noPers;
					int lastElemFromRowiPlus1 = ngbHood[i + 1].str[ngbHood[i + 1].str.size() - 1].noPers;
					if(ngbHood[i].str[lastElemFromRowi].noPers > ngbHood[i + 1].str[lastElemFromRowiPlus1].noPers){
						std::swap(ngbHood[i], ngbHood[i + 1]);
						verif = true;
					}
				}
			}
			for(int i = 0; i < ngbHood.size(); i++)
				ngbHood[i].str.resize(ngbHood[i].str.size() - 1);
		}

		void subpoint_e(std::vector<hood>& ngbHood){
			bool verif = true;
			while(verif){
				verif = false;
				for(int i = 0; i < ngbHood.size() - 1; i++){
					if(ngbHood[i].str.size() > ngbHood[i + 1].str.size()){
						std::swap(ngbHood[i], ngbHood[i + 1]);
						verif = true;
					}
				}
			}
		}

		void afisareHood(std::vector<hood>& ngbHood){
			std::cout << "\n///////afisare//////////\n";
			for(short i = 0; i < ngbHood.size(); i++){
				for(short j = 0; j < ngbHood[i].str.size(); j++)
					std::cout << ngbHood[i].str[j].noPers << " ";
				std::cout << "\n";
			}
		}
	}nbh;

}lot1;


int main(){
	lot1.replaceLettersWithPosInAlphabet();
}
