#include"..\OAHM\OAHashMap.h"
#include"Stopwatch.h"
#include"FileTokenizer.h"

#include<iostream>
#include<fstream>
using namespace std;

const size_t TEST_ARRAY_SIZE(39000);


inline int hh(string s)
{
	const char* str = s.c_str();
	return (str[0] + str[s.length()/2] + str[s.length() - 1]) % TEST_ARRAY_SIZE;

}


int djb2(string s)
{
	unsigned long hash = 5381;
	int c;
	auto str = s.c_str();

	while (c = *str++)
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

	return (hash % TEST_ARRAY_SIZE);
}

int main()
{
	Stopwatch s;
	FileTokenizer ft;
	ofstream excelImportFile;

	size_t index = 0;
	size_t cumulativeLinearSearchTime = 0;
	size_t cumulativeMapSearchTime = 0;
	vector<string> wordsRead;
	string dummy;
	
	const size_t TEST_INCREMENT(250);

	string* testArray = new string[TEST_ARRAY_SIZE];
	OAHashMap<string, string> testMap(TEST_ARRAY_SIZE, djb2);

	ft.read("c:\\words.txt");
	excelImportFile.open("c:\\searchresults.txt");

	for (unsigned int i = 0; i < TEST_ARRAY_SIZE; i += TEST_INCREMENT)
	{
		// Add another TEST_INCREMENT words to the end of the array
		for (int j = 0; j < TEST_INCREMENT; j++)
		{
			wordsRead.push_back(ft.getNextWord());
			testArray[index++] = wordsRead[j];
			testMap.insert(wordsRead[j], wordsRead[j]);
		}

		// Search for each of the recently read words, register cumulative time spent to do so
		for (int j = 0; j < TEST_INCREMENT; j++)
		{
			// LINEAR SEARCH
			s.start();
			for (unsigned int k = 0; k < index; k++)
			{
				if (testArray[k] == wordsRead[j]) break;
			}
			s.stop();
			cumulativeLinearSearchTime += s.getDuration(Stopwatch::NANOSECONDS);

			s.start();
			bool result = testMap.search(wordsRead[j], dummy);
			s.stop();
			if (!result) cout << "ERROR!!!" << endl;
			cumulativeMapSearchTime += s.getDuration(Stopwatch::NANOSECONDS);
		}

		cout << static_cast<double>(index) / TEST_ARRAY_SIZE << "\t" << cumulativeLinearSearchTime << "\t" << cumulativeMapSearchTime << endl;
		excelImportFile << static_cast<double>(index) / TEST_ARRAY_SIZE << ";" << cumulativeLinearSearchTime << ";" << cumulativeMapSearchTime << endl;

		// Reset for next test run
		cumulativeLinearSearchTime = 0;
		cumulativeMapSearchTime = 0;
		wordsRead.clear();

	}
}