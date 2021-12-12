// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>
using namespace std;

int uloha1();
int uloha2();

int main()
{
    cout << uloha2() << endl;
}

int uloha2() {
    fstream file("data.txt");
    vector<long> data;
    int *iter = new int;
    int logger = 0;

    while (file >> *iter)
        data.push_back(*iter);
    delete iter;

    auto winStart = data.begin(), winEnd = data.begin() + 3;
    while (true) {
        *winStart = std::accumulate(winStart, winEnd, 0);
        if (winStart != data.cbegin()) {
            if (*winStart > *(winStart - 1)) {
                logger++;
            }
        }
        if (winEnd == data.cend()) break;
        winStart++;
        winEnd = (winEnd < data.end() ? winEnd+1 : data.end());
    }
    ostream_iterator<int> oiter(cout, " ");
    copy(data.begin(),winEnd, oiter);
    cout << endl;
    return logger;
}

int uloha1() {
    fstream file;
    file.open("data.txt");
    int initValue, next, output = 0;
    if (file.is_open()) {
        file >> initValue;
        while (file >> next) {
            if (next > initValue)output++;
            initValue = next;
        }
        std::cout << output << endl;
        file.close();
    }
    return output;
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
