// Day6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

int uloha1();
int uloha2();

int main()
{
    cout << uloha2() << endl;
}

void print(const map<short, long long>& m) {
    for (const auto& el : m) {
        cout << el.second << "+";
    }
    cout << endl << "Copy to python" << endl;
}

void print(const vector<short>& v) {
    for (const auto& el : v) {
        cout << el << " ";
    }
    cout << endl;
}

int uloha1() {
    fstream file("data.txt");
    vector<short> fish;
    char coma;
    short oneFish;
    while (file >> oneFish) {
        fish.push_back(oneFish);
        file >> coma;
    }
    print(fish);
    for (int i = 0; i < 256; i++) {
        std::sort(fish.begin(), fish.end());
        auto zero = fish.begin();

        for (; zero != fish.cend(); zero++)
            (*zero)--;

        zero = fish.begin();
        int track = 0;
        while (*zero < 0) {
            *zero = 6;
            zero++, track++;
            fish.push_back(8);
            zero = fish.begin() + track;
        }
    }

    return fish.size();
}

int uloha2() {
    fstream file("data.txt");
    map<short, long long> fish;
    char coma;
    short oneFish;
    while (file >> oneFish) {
        fish[oneFish]++;
        file >> coma;
    }
    for (int i = 0; i < 256; i++) {
        long double temp1 = fish[8], temp2;
        fish[8] = 0;
        for (int j = 8; j >= 0; j--) {
            temp2 = fish[j-1];
            fish[j - 1] = temp1;
            temp1 = temp2;
        }
        if (fish[-1] > 0) {
            fish[6] += fish[-1];
            fish[8] += fish[-1];
            fish[-1] = 0;
        }
    }
    print(fish);
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
