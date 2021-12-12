// Day9.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
using namespace std;

int uloha1();
int uloha2();

int main()
{
    cout << uloha2() << endl;
}

int uloha1() {
    fstream file("data.txt");
    vector<string> floor;
    string vrstva;

    long long sumPoints = 0;

    while (getline(file, vrstva))
        floor.push_back(vrstva);

    for (auto x = 0; x != floor.size(); x++) {
        if (x == 0) {
            for (auto y = 0; y != floor[x].size(); y++) {
                if (y == 0) {
                    if (floor[x][y] < floor[x][y+1] && floor[x][y] < floor[x + 1][y])
                        sumPoints += static_cast<long long>(floor[x][y]) - '0' + 1;
                }
                else if (y == floor[x].size() - 1) {
                    if (floor[x][y] < floor[x][y - 1] && floor[x][y] < floor[x + 1][y])
                        sumPoints += static_cast<long long>(floor[x][y]) - '0' + 1;
                }
                else {
                    if (floor[x][y] < floor[x][y + 1] && floor[x][y] < floor[x][y - 1] && floor[x][y] < floor[x+1][y])
                        sumPoints += static_cast<long long>(floor[x][y])-'0' + 1;
                }
            }
        }
        else if (x == floor.size()-1) {
            for (auto y = 0; y != floor[x].size(); y++) {
                if (y == 0) {
                    if (floor[x][y] < floor[x][y+1] && floor[x][y] < floor[x-1][y])
                        sumPoints += static_cast<long long>(floor[x][y]) - '0' + 1;
                }
                else if (y == floor[x].size()-1) {
                    if (floor[x][y] < floor[x][y-1] && floor[x][y] < floor[x-1][y])
                        sumPoints += static_cast<long long>(floor[x][y]) - '0' + 1;
                }
                else {
                    if (floor[x][y] < floor[x][y + 1] && floor[x][y] < floor[x][y - 1] && floor[x][y] < floor[x-1][y])
                        sumPoints += static_cast<long long>(floor[x][y]) - '0' + 1;
                }
            }
        }
        else {
            for (auto y = 0; y != floor[x].size(); y++) {
                if (y == 0) {
                    if (floor[x][y] < floor[x][y+1] && floor[x][y] < floor[x-1][y] && floor[x][y] < floor[x + 1][y])
                        sumPoints += static_cast<long long>(floor[x][y]) - '0' + 1;
                }
                else if (y == floor[x].size()-1) {
                    if (floor[x][y] < floor[x][y-1] && floor[x][y] < floor[x-1][y] && floor[x][y] < floor[x + 1][y])
                        sumPoints += static_cast<long long>(floor[x][y]) - '0' + 1;
                }
                else {
                    if (floor[x][y] < floor[x][y + 1] && floor[x][y] < floor[x][y - 1] && floor[x][y] < floor[x-1][y] && floor[x][y] < floor[x + 1][y])
                        sumPoints += static_cast<long long>(floor[x][y]) - '0' + 1;
                }
            }

        }

    }
    return sumPoints;

}

set<pair<int, int>> exploredPoints;
int basinSizeNum = 0;

void basinSize(vector<string>& field, int x, int y) {
    if (x >= field.size() || x < 0 ||
        y >= field[x].size() || y < 0 ||
        exploredPoints.find({ x,y }) != exploredPoints.end()) {
        return;
    }
    exploredPoints.insert({ x,y });
    basinSizeNum++; 
    //field[x][y] = '-';
    if (x + 1 < field.size() && field[x + 1][y] < '9') // dole
        basinSize(field, x + 1, y);

    if (y + 1 < field[x].size() && field[x][y + 1] < '9') // doprava
        basinSize(field, x, y + 1);

    if (x - 1 >= 0 && field[x - 1][y] < '9') // hore
        basinSize(field, x - 1, y);

    if (y - 1 >= 0 && field[x][y - 1] < '9')  // dolava
        basinSize(field, x, y - 1);
 }
    /*
     21915
     19999
     99991
     99992
    */

int uloha2() {
    fstream file("data.txt");
    vector<string> floor;
    string vrstva;
    vector<int> basins = {0, 0, 0};

    while (getline(file, vrstva))
        floor.push_back(vrstva);

    for (int x = 0; x != floor.size(); x++) {
        for (int y = 0; y != floor[x].size(); y++) {
            if (floor[x][y] == '9')
                exploredPoints.insert({ x,y });
            else if (exploredPoints.find({ x,y }) == exploredPoints.end()) {
                basinSize(floor, x, y);
                std::sort(basins.begin(), basins.end());  
                if (*basins.begin() < basinSizeNum) {
                    *basins.begin() = basinSizeNum; 
                }
                basinSizeNum = 0; 
            }
        }
    }
    return basins[0] * basins[1] * basins[2];
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
