// Day15.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <deque>
#include <chrono>
#include <limits>
using namespace std;
using ull = unsigned long long;
using pii = pair<int, int>;
using Cave = vector<vector<int>>;

int part1(const Cave&);
Cave expand(const Cave&);

int main()
{
    fstream file("data.txt");
    Cave cave;
    string line;
    int i = 0;

    while (getline(file, line)) {
        cave.push_back(vector<int>());
        for (auto& el : line)
            cave[i].push_back(el - '0');
        i++;
    }
    cout << part1(cave) << endl;
    auto newCave = expand(cave);
    auto a = std::chrono::high_resolution_clock::now();
    cout << part1(newCave) << endl;
    auto b = std::chrono::high_resolution_clock::now();
    cout << chrono::duration_cast<chrono::microseconds>(b - a).count() << " microseconds";
    return 0;
}

Cave expand(const Cave& cave) {
    auto dimensions = cave.size();
    Cave newCave = Cave(dimensions * 5, vector<int>(dimensions * 5, 0));
    for (auto i = 0; i != newCave.size(); i++) {
        for (auto j = 0; j != newCave.size(); j++) {
            auto a = cave[i % dimensions][j % dimensions];
            auto b = (j / dimensions + i / dimensions - 1);
            newCave[i][j] = (a + b) % 9 + 1;
        }
    }
    return newCave;
}

int part1(const Cave& cave) {
    Cave cost(cave.size(), vector<int>(cave.size(), numeric_limits<int>::max()));
    cost[0][0] = 0;
    
    deque<pair<int, int>> toCheck;
    toCheck.push_back({ 0,0 });
    while (!toCheck.empty()) {
        auto point = toCheck.front();
        toCheck.pop_front();

        auto r = point.first, c = point.second;

        if (r + 1 < cost.size() && cost[r][c] + cave[r + 1][c] < cost[r + 1][c]) {
            cost[r + 1][c] = cost[r][c] + cave[r + 1][c];
            toCheck.push_back({ r + 1, c });
        }
        if (c + 1 < cost[r].size() && cost[r][c] + cave[r][c + 1] < cost[r][c + 1]) {
            cost[r][c + 1] = cost[r][c] + cave[r][c + 1];
            toCheck.push_back({ r, c + 1 });
        }
        if (c > 0 && cost[r][c] + cave[r][c - 1] < cost[r][c - 1]) {
            cost[r][c - 1] = cost[r][c] + cave[r][c - 1];
            toCheck.push_back({ r, c - 1 });
        }
        if (r > 0 && cost[r][c] + cave[r - 1][c] < cost[r - 1][c]) {
            cost[r - 1][c] = cost[r][c] + cave[r - 1][c];
            toCheck.push_back({ r - 1, c });
        }
    }
    return cost[cost.size()-1][cost[cost.size() - 1].size() - 1];
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
