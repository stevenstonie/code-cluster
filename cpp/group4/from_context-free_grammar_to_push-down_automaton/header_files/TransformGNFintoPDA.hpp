#pragma once

#include "Grammar.hpp"
#include "PushDownAutomaton.hpp"

PushDownAutomaton transformGNFintoPDA(Grammar grammar);