// Day3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <bitset>
using namespace std;

void printV(vector<string>& vec) {
    for (const auto& el : vec) {
        cout << el << " ";
    }
    cout << endl;
}

int uloha1();
int uloha2();

int main()
{
    cout << uloha2() << endl;
}

int strBin2Int(string str) {
    int val = 0;
    for (auto riter = str.rbegin(); riter != str.rend(); riter++) {
        if(*riter == '1')
            val += pow(2, riter - str.rbegin());
    }
    return val;
}

int uloha2() {
    fstream file("data.txt");
    vector<string> data_O, data_CO;
    string input;
    int oxygen = 0, co2 = 0;

    while (file >> input) {
        data_O.push_back(input);
        data_CO.push_back(input);
    }

    auto filter = [](vector<string>& data, char tr, char fal) {
        string sortedData;
        int mostCommon;
        for (int i = 0; i != data[0].size(); i++) {
            mostCommon = 0;
            for (int j = 0; j != data.size(); j++) {
                data[j][i] == '0' ? mostCommon-- : mostCommon++;
            }
            sortedData.push_back(mostCommon < 0 ? tr : fal);

            for (auto el = data.begin(); el != data.end();) {
                if (el->find(sortedData) != 0) {
                    std::swap(*el, *(data.end() - 1));
                    if (el == data.end()-1)
                        el = data.end() - 2;
                    data.pop_back();
                    if (data.size() == 1) {
                        return strBin2Int(*data.begin());
                    }
                }
                else
                    el++;
            }

        }
    };
    oxygen = filter(data_O, '0', '1');
    co2 = filter(data_CO, '1', '0');
    return co2 * oxygen;
}

int uloha1() {
    fstream file("data.txt");
    vector<string> data;
    vector<int> mostCommon;
    string input;
    int gamma = 0, epsilon = 0;

    while (file >> input)
        data.push_back(input);
    
    for (int j = 0; j != data.size(); j++) {
        for (auto i = 0; i != data[j].size(); i++) {
            if(j ==0)
                mostCommon.push_back(0);
            data[j][i] == '0' ? mostCommon[i]-- : mostCommon[i]++;
        }
    }

    for (auto iter = mostCommon.begin(); iter != mostCommon.end(); iter++) {
        if (*iter > 0)
            gamma |= 1;
        gamma <<= 1;
    }
    gamma >>= 1;
    
    for (int i = 11; i >= 0; i--) {
        epsilon |= ((gamma >> i & 1) == 1 ? 0 : 1);
        epsilon <<= 1;
    }
    epsilon >>= 1;

    return epsilon * gamma;
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
