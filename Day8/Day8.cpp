// Day8.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

int uloha1();
int uloha2();

int main()
{
    //string a = "acbd", b = "qn";
    //cout << a. << endl;
    cout << uloha2() << endl;
}

int uloha1() {
    fstream file("data.txt");
    char delim;
    string displayNum;
    int uniqueNums = 0;
    while (!file.eof()) {
        do {
            file >> delim;
        } while (delim != '|');
        //file >> delim;

        for (int i = 0; i < 4; i++) {
            file >> displayNum;
            if (displayNum.size() == 3 || displayNum.size() == 4 || displayNum.size() == 2 || displayNum.size() == 7)
                uniqueNums++;
        }
    }
    return uniqueNums;
}

string letterDifference(const string& a, const string& b) {
    string out = "";
    for (const auto& el : b) {
        if (a.find(el) == string::npos)
            out += el;
    }
    return out;
}

int uloha2() {
    fstream file("data.txt");
    map<int, string> signalRepresentation({ {1,""},{2,""},{3,""},{4,""},{5,""},{6,""},{7,""},{8,""},{9,""},{0,""} });
    vector<string> determine(4);
    map <int, vector<string>> unresolved; // 6 - 0,6,9;     5 - 2, 3, 5
    string signal,help;
    char delim;
    unsigned long long totalSum = 0;

    while (!file.eof()) {
        stringstream ss;
        std::getline(file, signal);
            ss << signal;
            for (int i = 0; i < 10; i++) {
                ss >> help;
                std::sort(help.begin(), help.end());
                switch (help.size()) {
                case 2:
                    signalRepresentation[1] = help;
                    break;
                case 4:
                    signalRepresentation[4] = help;
                    break;
                case 3:
                    signalRepresentation[7] = help;
                    break;
                case 7:
                    signalRepresentation[8] = help;
                    break;
                default:
                    unresolved[help.size()].push_back(help);
                }
            }

            ss >> delim;
            for (int i = 0; i < 4; i++) {
                ss >> help;
                std::sort(help.begin(), help.end());
                determine[i] = help;
            }

        for (auto& combination : unresolved[5]) {
            if (letterDifference(combination, signalRepresentation[4]).size() == 2)
                signalRepresentation[2] = combination;
            else if (letterDifference(combination, signalRepresentation[1]).size() == 1)
                signalRepresentation[5] = combination;
            else
                signalRepresentation[3] = combination;
        }

        for (auto& combination : unresolved[6]) {
            if (letterDifference(combination, signalRepresentation[4]).size() == 0)
                signalRepresentation[9] = combination;
            else if (letterDifference(combination, signalRepresentation[1]).size() == 1)
                signalRepresentation[6] = combination;
            else
                signalRepresentation[0] = combination;
        }

        int tempSum = 0;
        unsigned long long sum = 0;
        for (auto iter = determine.begin(); iter != determine.end(); iter++) {
            std::sort(iter->begin(), iter->end());
            for (auto match = signalRepresentation.cbegin(); match != signalRepresentation.cend(); match++) {
                if (*iter == match->second) {
                    sum = sum * 10 + match->first;
                    break;
                }
            }
        }
        //sum = tempSum;
        totalSum += sum;
    }

    return totalSum;
}

/*       
        if (find_if(signalRepresentation.begin(),
            signalRepresentation.end(),
            [&signal](const pair<int, string>& el) -> bool {return el.second == signal; }) != signalRepresentation.cend())
        {

        }
*/

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
