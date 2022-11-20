# Building a finite automaton for a regular grammar


### Description: Write an application that builds a finite automaton M = (Q, Σ, δ, q0, F) from a regular grammar G = (Vn , Vt , S, P) given as input, for which T(M) = L(G)


#### Requirements: 

##### I. Create a class Grammar with the members Vn, Vt, S, P. (for the set of productions a class/struct can be used)
The methods of the class: 

1. VerifyGrammar - verifies if the grammar is correct/valid. Identify from theory.
2. IsRegular - verifies if the grammar is regular or not
3. GenerateWord - generates a word from the start symbol. When creating the word, the production that can be applied is chosen at random. Print all combinations that led to the final word.
4. PrintGrammar - print the elements of the grammar. Here, an overload of the implicit operator can be taken into consideration.
5. ReadGrammar - read the elements of the grammar. Here, an overload of the implicit operator can  be taken into consideration.


##### II. Define a class FiniteAutomaton with the members (Q, Σ, δ, q0, F) (define for both dfa and nfa)

The methods of the class: 

1. VerifyAutomaton - verifies if an automaton is valid. Identify from theory.
2. PrintAutomaton - print the elements of the automaton. Here, the overloading of the implied operator can be taken into consideration.
3. CheckWord - a function that verifies if a word is either accepted by the automaton or not.
4. IsDeterministic - verifies if the automaton is either deterministic or not.

##### III. Define a function that takes a regular grammar G and returns an object of type automaton. The returned automaton needs to recognize the generated language by G. The function can be a member of the class Grammar (or not).

##### IV. In the main function:

1. Read from a file the elements of a regular grammar. Verify if the grammar is correct and regular. Only if the statements before are true the menu becomes available.
2. Create a menu (that prints until no options are wanted anymore) with the following options:
   a) print the grammar G
   b) generate an n number of words with the grammar G
   c) the equivalent automaton produced from G. The automaton is printed
   d) verify if a word is either accepted by the generated automaton or not.
   e) generate a word in G and verify if it is accepted by the automaton.