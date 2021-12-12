#pragma once
#include <vector>
#include <fstream>
using namespace std;

namespace Table
{
	typedef vector<vector<int>> table;

	vector<int> loadDrowenNumbers(fstream &file);
	table loadTable(fstream& file);
	void markDrowenNumber(table& t, const int& number);
	int checkBingo(const table& t, int last);
	int checkLines(const table& t, int last);
	int checkColumns(const table& t, int last);
	int returnBingo(const table& t, int last);
};

