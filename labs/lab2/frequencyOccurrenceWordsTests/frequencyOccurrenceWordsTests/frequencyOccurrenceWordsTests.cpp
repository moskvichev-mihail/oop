// frequencyOccurrenceWordsTests.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

using namespace std;

map <string, int> ReadsAndSearchOccurrenceWords(istream & input, map <string, int> occurrenceWordsMap);

map <string, int> stringOne;
map <string, int> stringOneResult = { {"hello", 5 } };
map <string, int> outputStringOne;

map <string, int> stringTwo;
map <string, int> stringTwoResult = { { "fedya", 3 },
											 { "is", 3 },
											 { "the", 4 },
											 { "best", 3 },
											 { "programmer", 2 },
											 { "in", 2 },
											 { "world", 2 } };
ifstream inputStringTwo("Fedya FEDYA FedyA Is is IS the THe THE best BEST beST PROGRAMMER programmer in IN The WORLD world");
map <string, int> outputStringTwo;

TEST_CASE("frequencyOccurrenceWords tests")
{
	stringOne = ReadsAndSearchOccurrenceWords(cin, outputStringOne);
	CHECK(outputStringOne == stringOneResult);
	stringTwo = ReadsAndSearchOccurrenceWords(cin, outputStringTwo);
	CHECK(outputStringTwo == stringTwoResult);
}

map <string, int> ReadsAndSearchOccurrenceWords(istream & input, map <string, int> occurrenceWordsMap)
{
	string word;

	cout << "Enter the words: " << endl;
	while (input >> word)
	{
		transform(word.begin(), word.end(), word.begin(), ::tolower);
		++occurrenceWordsMap[word];
	}
	return occurrenceWordsMap;
}