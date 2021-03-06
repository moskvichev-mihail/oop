// HTMLEncode.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Encode.h"

using namespace std;

int main()
{
	string inputLine, encodeText;
	char ch = NULL;
	cout << "To exit the program, press @." << endl;
	cout << "Enter text for encode: " << endl;
	while (ch != '@')
	{
		ch = cin.get();
		inputLine += ch;
		if (ch == '\n')
		{
			encodeText += HtmlEncode(inputLine);
			inputLine = "";
		}
	}
	cout << "Decode text:" << endl;
	cout << encodeText << endl;
    return 0;
}

