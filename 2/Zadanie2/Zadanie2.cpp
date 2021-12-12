// Zadanie2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Directions {
	int horizontal, vertical, aim;
};

int uloha1();
int uloha2();

int main()
{
	cout << uloha2() << endl;
   
}

int uloha2() {
	fstream file("data.txt");
	Directions directions = { 0 };
	int data;
	string prikaz;

	while (file >> prikaz) {
		file >> data;
		if (prikaz == "up")
			directions.aim -= data;
		else if (prikaz == "down")
			directions.aim += data;
		else {
			directions.horizontal += data;
			directions.vertical += directions.aim * data;
		}
	}
	return directions.horizontal * directions.vertical;
}

int uloha1() {
	fstream file("data.txt");
	Directions directions = { 0 };
	int data;
	string prikaz;

	while (file >> prikaz) {
		file >> data;
		if (prikaz == "up")
			directions.vertical -= data;
		else if (prikaz == "down")
			directions.vertical += data;
		else
			directions.horizontal += data;
	}
	return directions.horizontal * directions.vertical;
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
