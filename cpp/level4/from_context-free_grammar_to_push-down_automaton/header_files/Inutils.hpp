#pragma once

#include <random>
#include <vector>
#include <Windows.h>
#include <iostream>

int randomIntFrom0untilN(int n);

std::vector<std::string> convertStringToVectorOfStrings(std::string string);

int getIndexOfStringInVector(const std::string& string, const std::vector<std::string>& vector);

bool checkIfFirstStringIsSmallerThanSecond(const std::string& string1, const std::string& string2);

void printThreeDots();

void printMainMenu();