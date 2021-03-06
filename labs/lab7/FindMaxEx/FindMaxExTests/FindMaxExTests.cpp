// FindMaxExTests.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "../FindMaxEx/FindMaxEx.h"

struct Athlete
{
	string name;
	unsigned short height;
	unsigned short weight;

};

struct Athletes_
{
	const Athlete first{ "first", 175, 70 };
	const Athlete second{ "second", 173, 69 };
	const Athlete third{ "third", 176, 70 };
	const Athlete fourth{ "fourth", 172, 67 };
	const Athlete fifth{ "fifth", 181, 77 };
	const Athlete sixth{ "sixth", 194, 87 };
	const Athlete seventh{ "seventh", 168, 60 };
	const Athlete eighth{ "eighth", 175, 73 };
	const Athlete ninth{ "ninth", 179, 79 };
	const vector<Athlete> athletes{ first, second, third, fourth, fifth, sixth, seventh, eighth, ninth };
};

bool IsHeightLess(const Athlete &first, const Athlete &second)
{
	return (first.height < second.height);
}

bool IsWeightLess(const Athlete &first, const Athlete &second)
{
	return (first.weight < second.weight);
}

TEST_CASE("FindMaxEx Tests")
{
	cout << "FindMaxEx Tests" << endl;
	SECTION("can_find_max_element_by_copmarator_function")
	{
		cout << "can_find_max_element_by_copmarator_function" << endl;
		Athlete maxValue1;
		Athletes_ athletes1;
		FindMaxEx(athletes1.athletes, maxValue1, IsHeightLess);
		CHECK(maxValue1.height == 194);
	}
	SECTION("can_find_max_element_by_copmarator_function2")
	{
		cout << "can_find_max_element_by_copmarator_function2" << endl;
		Athlete maxValue;
		Athletes_ athletes2;
		Athlete maxValue2;
		FindMaxEx(athletes2.athletes, maxValue2, IsWeightLess);
		CHECK(maxValue2.weight == 87);
	}
}