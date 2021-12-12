// Day4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Table.h"

int uloha1();
int uloha2();

int main()
{
    cout << uloha1() << endl;
}


int uloha1() {
    fstream file("data.txt");
    vector<Table::table> bingoTables;
    vector<int> drowenNumbers = Table::loadDrowenNumbers(file);
    int score;

    while (!file.eof())
        bingoTables.push_back(Table::loadTable(file));
    
    for (auto iter = drowenNumbers.cbegin(); iter != drowenNumbers.cend();
        iter++) {
        for (auto tab = bingoTables.begin(); tab != bingoTables.cend();) {
            Table::markDrowenNumber(*tab, *iter);
            if ((score = Table::checkBingo(*tab, *iter)) != 0) {
                //return score;
                score *= *iter;
                if (bingoTables.size() == 1)
                    return score;
                if (tab == bingoTables.end() - 1) {
                    tab--;
                    bingoTables.pop_back();
                    tab++;
                }
                else {
                    bingoTables.erase(std::remove(bingoTables.begin(), bingoTables.end(), *tab), bingoTables.end());
                }
                /*
                else if (tab == bingoTables.begin()) {
                    tab++;
                    bingoTables.
                }
                else {
                    tab++;
                    bingoTables.erase(tab - 1);
                }*/
            }
            else {
                tab++;
            }
        }
    }
    return 0;
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
