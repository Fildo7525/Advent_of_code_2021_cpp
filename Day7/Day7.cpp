// Day7.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

long long uloha1();
long long uloha2();

int main()
{
	cout << uloha1() << endl;
}

long long sumary(long long a, long long b) {
	long long timer = 1;
	long long sum = 0;
	while (a != b) {
		sum += timer;
		a++, timer++;
	}
	return sum;
}

long long uloha1() {
	fstream file("data.txt");
	vector<int> loadedData;
	char coma;
	long long minUsedFuel = LLONG_MAX;

	int* horizontalPoint = new int;
	while (file >> *horizontalPoint) {
		loadedData.push_back(*horizontalPoint);
		file >> coma;
	}
	delete horizontalPoint;
	std::sort(loadedData.begin(), loadedData.end());
	auto beg = *loadedData.begin();
	auto end = *(loadedData.end() - 1);

	for (auto aligmentPoint = beg; aligmentPoint != end; aligmentPoint++) {
		long long tempTotalUsedFuel = 0;
		//cout << "Aligment: " << aligmentPoint << endl;
		for (const auto& el : loadedData) {
			tempTotalUsedFuel += sumary(0,abs(el - aligmentPoint));
		}
		if (tempTotalUsedFuel < minUsedFuel)
			minUsedFuel = tempTotalUsedFuel;
	}

	return minUsedFuel;

}

long long uloha2() {
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
