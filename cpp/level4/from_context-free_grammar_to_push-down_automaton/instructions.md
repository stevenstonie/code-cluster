# Building a pushdown automaton from a context-free grammar

#### Description: Write an application that, for a context-free grammar, builds a push-down automaton M = (Q, Σ, Γ, δ, q0, Z0, ∅), for which T(M) = L(G).

#### Requirements:

##### I. Define a class Gramar with the members Vn, Vt, S, P, having the following methods:

1. verifyGrammar - verifies if the grammar is correct/valid. Identify from theory.
2. generateWord - generates a word from the start symbol. When creating the word, the production that can be applied is chosen at random. Print all combinations that led to the final word.
3. printGrammar - print the elements of the grammar. Here, an overload of the implicit operator can be taken into consideration.
4. readGrammar - read the elements of the grammar. Here, an overload of the implicit operator can  be taken into consideration.
5. isContextFree - verifies if the grammar is context-free or not
6. simplifyGrammar - simplifies the grammar
7. transformToGreibachNormalForm - transforms the grammar to Greibach Normal Form

##### II. Define a class PushDownAutomaton with the members (Q, Σ, Γ, δ, q0, Z0). The following methods of the class should be:

1. printAutomaton - print the elements of the automaton. Here, the overloading of the implied operator can be taken into consideration.
2. checkWord - a function that verifies if a word is either accepted by the automaton or not.
3. isDeterministic - verifies if the automaton is either deterministic or not.

##### III. Define a function that takes a context-free grammar G as parameter and returns an object of type push-down automaton. The returned automaton needs to recognize the generated language by G.

##### IV. In the main function: read from a file a context-free grammar. Verify if the grarmmar is valid and context-free. Only then the the corresponding PDA is built and next menu becomes available:

1. print the grammar G
2. generates a word in the grammar
3. prints the simplified grammar result
4. prints the grammar in Greibach Normal Form
5. generates a word in G and verifies if it is accepted by the automaton
6. verifies if a word read from the keyboard is acceptetd by the automaton
