// frequencyOccurrenceWords.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

using namespace std;

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

void ShowOccurrenceWords(map <string, int> & occurrenceWordsMap)
{
	if (!occurrenceWordsMap.empty())
	{
		for (auto map = occurrenceWordsMap.begin(); map != occurrenceWordsMap.end(); ++map)
		{
			cout << map->first << " : " << map->second << endl;
		}
	}
	else
	{
		cout << "The words did not come across!\n";
	}
}

int main()
{
	map <string, int> occurrenceWordsMap;
	occurrenceWordsMap = ReadsAndSearchOccurrenceWords(cin, occurrenceWordsMap);
	cout << "Result frequency occurrence words:" << endl;
	ShowOccurrenceWords(occurrenceWordsMap);
    return 0;
}