// Day13.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <deque>
#include <vector>
#include <algorithm>
#define PART 1
using namespace std;

int part();

int main()
{
    std::cout << part() << endl;
}

int part() {
    fstream file("data.txt");
    vector<pair<int, int>> transparentPaper;
    string line;
    deque<pair<char, int>> folds;
    vector<string> out;

    while (getline(file, line)) {
        if (line == "")
            break;
        int x = atoi(string(line.begin(), line.begin() + line.find(',')).c_str());
        int y = atoi(string(line.begin() + line.find(',') + 1, line.end()).c_str());
        transparentPaper.push_back({ x,y });
    }

    while (getline(file, line)) {
        char axis = *(line.begin() + line.find('=') - 1);
        int folding = atoi(string(line.begin() + line.find('=') + 1, line.end()).c_str());
        folds.push_front({ axis, folding });
    }
    
    while (!folds.empty()) {
        auto fold = folds.back();
        folds.pop_back();
        for (auto iter = transparentPaper.begin(); iter != transparentPaper.end(); iter++) {
            if (fold.first == 'y' && iter->second > fold.second)
                iter->second = fold.second - (iter->second - fold.second);
            else if (fold.first == 'x' && iter->first > fold.second)
                iter->first = fold.second - (iter->first - fold.second);
        }
        std::sort(transparentPaper.begin(), transparentPaper.end());
        auto uniquePtr = std::unique(transparentPaper.begin(), transparentPaper.end());
        transparentPaper.erase(uniquePtr, transparentPaper.end());
    }
#if PART == 1
    return static_cast<int>(transparentPaper.size());
#else
    line = string(39, ' ');
    for (int i = 0; i < 6; i++)
        out.push_back(line);

    for (const auto& el : transparentPaper)
        out[el.second][el.first] = '#';

    copy(out.cbegin(), out.cend(), ostream_iterator<string>(cout, "\n"));
    return transparentPaper.size();
#endif
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
