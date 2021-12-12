// Day11.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
using namespace std;

int uloha1();
int uloha2();

int main()
{
    std::cout << uloha1() << endl;
}

long long flashes = 0;
map<pair<int, int>, int> changedOnStep;
int step = 0;


void increaseMeAndAdjacent(vector<string>& octopuses, int row, int col) {
    octopuses[row][col] = '0';
    changedOnStep[{row, col}] = step;
    flashes++;

    for (int x = col - 1; x != col + 2; x++) {                                      // riadok nad
        if (x >= 0 && x < octopuses[row].size() && row - 1 >= 0 && changedOnStep[{row - 1, x}] != step) {
            octopuses[row - 1][x]++;
            if (octopuses[row - 1][x] > '9')
                increaseMeAndAdjacent(octopuses, row - 1, x);
        }
    }
    for (int x = col - 1; x != col + 2; x++) {                                      // riadok pod
        if (x >= 0 && x < octopuses[row].size() && row + 1 < octopuses.size() && changedOnStep[{row + 1, x}] != step) {
            octopuses[row + 1][x]++;
            if (octopuses[row + 1][x] > '9') {
                increaseMeAndAdjacent(octopuses, row + 1, x);
            }
        }
    }
    if (col - 1 >= 0 && changedOnStep[{row, col - 1}] != step) {                            // jedno nalavo                                            
        octopuses[row][col - 1]++;
        if (octopuses[row][col - 1] > '9')
            increaseMeAndAdjacent(octopuses, row, col - 1);
    }
    if (col + 1 < octopuses[row].size() && changedOnStep[{row, col + 1}] != step) {         // jedno napravo
        octopuses[row][col + 1]++;
        if (octopuses[row][col + 1] > '9')
            increaseMeAndAdjacent(octopuses, row, col + 1);
    }
}

void increaseFieldCount(vector<string>& octopuses) {
    for (int row = 0; row != octopuses.size(); row++) {
        for (int col = 0; col != octopuses[row].size(); col++) {
            if (changedOnStep.find({ row, col }) != changedOnStep.end() && changedOnStep[{row, col}] == step)
                continue;
            else if (octopuses[row][col] == '9') {
                increaseMeAndAdjacent(octopuses, row, col);
            }
            else
                octopuses[row][col]++;
        }
    }
}

bool checkIfAllUp(const vector<string>& octopuses) {
    for (const auto& line : octopuses) {
        for (const auto& octopus : line) {
            if (octopus != '0')
                return false;
        }
    }
    return true;
}

int uloha1() {
    fstream file("data.txt");
    string line;
    vector<string> octopuses;

    while (std::getline(file, line))
        octopuses.push_back(line);

    while(!checkIfAllUp(octopuses)) {
        increaseFieldCount(octopuses);
        step++;
        //if (step == 193)
          //  cout << step << endl;
    }
    return step;
}

int uloha2() {
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
