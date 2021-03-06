// frequencyOccurrenceWords.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "OccurrenceWords.h"

using namespace std;

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
	cout << "Enter the words: " << endl;
	occurrenceWordsMap = FillOccurrenceWordsMap(cin, occurrenceWordsMap);
	cout << "Result frequency occurrence words:" << endl;
	ShowOccurrenceWords(occurrenceWordsMap);
    return 0;
}