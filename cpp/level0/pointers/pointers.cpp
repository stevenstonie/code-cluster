/* "nb" is a variable, "&nb" is the adress of "nb", "*p" is a special variable
which can store the adress of a variable. we can store an adress to a
pointer in two ways:-int* p=&nb;
					-p=&nb;
we cant do *p=&nb, otherwise the program will get an error. that is
because "*p", when it got past being declared, it points to the value
of the adress stored by "p"
*/
#include <iostream>

int main(){
	int nb = 27, * p;
	p = &nb;
	std::cout << " nb = " << nb << std::endl;   //value of "nb"
	std::cout << "&nb = " << &nb << std::endl;  //adress of "nb"
	std::cout << "  p = " << p << std::endl;    //adress of "nb" stored in "p"
	std::cout << " *p = " << *p << std::endl;   //value of the variable pointed by "p"
}

/*      stack       |         heap          |
					|                       |
					|                       |
					|                       |
   p[0xA]           |                       |
					|                       |
					|                       |
*/
