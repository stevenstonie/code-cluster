#pragma once

#include <unordered_map>

#include "Grammar.h"
#include "FiniteAutomaton.h"

FiniteAutomaton GrammarToFiniteAutomaton(const Grammar& grammar);