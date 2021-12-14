// Day14.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <map>
#include <string>
using namespace std;
using ull = unsigned long long;
#define PART1 10
#define PART2 40
#define CYCLES PART2

ull part();

int main()
{
    std::cout << part() << endl;
}

unsigned long long min(const map<char, unsigned long long> &letters) {
    ull min = ULLONG_MAX;
    for (const auto& el : letters) {
        if (el.second < min) {
            min = el.second;
        }
    }
    return min;
}

unsigned long long max(const map<char, unsigned long long> &letters) {
    ull max = 0;
    for (const auto& el : letters) {
        if (el.second > max) {
            max = el.second;
        }
    }
    return max;
}

ull part() {
    fstream file("data.txt");
    string base, Pair, Mid;
    map<string, string> connections;
    map<string, ull> baseCon;

    getline(file, base);
    string trash;
    while (file >> Pair >> trash >> Mid)
        connections[Pair] = Mid;

    auto pairStart = base.begin(), pairEnd = base.begin() + 2;
    while (true) {
        baseCon[string(pairStart, pairEnd-1) += connections[string(pairStart, pairEnd)]]++;
        baseCon[connections[string(pairStart, pairEnd)] + string(pairStart+1, pairEnd)]++;
        if (pairEnd == base.cend())
            break;
        pairStart++;
        pairEnd++;
    }
    for (int i = 1; i < CYCLES; i++) {
        map<string, ull> temp;
        for (auto &pairs : baseCon) {
            auto help = pairs.second;
            pairs.second = 0;
            temp[(pairs.first[0] + connections[pairs.first])] += help;
            temp[(connections[pairs.first] + pairs.first[1])] += help;
        }
        baseCon = std::move(temp);
    }
    map<char, unsigned long long> letterCount;
    for (auto &el : baseCon) {
        letterCount[el.first[0]] += el.second;
    }
    letterCount[*base.rbegin()]++;
    return max(letterCount) - min(letterCount);

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
