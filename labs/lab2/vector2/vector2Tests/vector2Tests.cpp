// vector2Tests.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "../vector2/ProcessVector.h"

std::vector<double> vectorOne = { 2, 4, 2 };
std::vector<double> vectorOneResult = { 4, 8, 4 };

std::vector<double> vectorTwo = { 10, 9, 20, 2, 3, 30, 6, 5 };
std::vector<double> vectorTwoResult = { 20, 18, 40, 4, 6, 60, 12, 10 };

std::vector<double> vectorThree = { 2.2, 4, 8, 16 };
std::vector<double> vectorThreeResult = { 4.84, 8.8, 17.6, 35.2 };

TEST_CASE("vector2 tests")
{
	ProcessVector(vectorOne);
	CHECK(vectorOne == vectorOneResult);
	ProcessVector(vectorTwo);
	CHECK(vectorTwo == vectorTwoResult);
	ProcessVector(vectorThree);
	CHECK(vectorThree == vectorThreeResult);
}