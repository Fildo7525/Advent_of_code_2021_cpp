// Day16.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <cstdint>
#include <numeric>
#include <algorithm>
using namespace std;
using ull = unsigned long long;

ull pt1();

int main()
{
    std::cout << pt1() << endl;
}

string hex2bin(const string& hex) {
    string bin;
    for (const auto& el : hex) {
        if (el >= '0' && el <= '9') {
            uint8_t temp = el - '0';
            for (int i = 3; i >= 0; i--) {
                bin.push_back((temp >> i & 1) + '0');
            }
        }
        else if (el >= 'A' && el <= 'F') {
            uint8_t temp = el - 'A' + 10;
            for (int i = 3; i >= 0; i--) {
                bin.push_back((temp >> i & 1) + '0');
            }
        }
    }
    return bin;
}

ull bin2dec(const string& bin) {
    ull dec = 0;
    for (auto iter = bin.crbegin(); iter != bin.crend(); iter++) {
        dec += (static_cast<char>(*iter) - '0') * pow(2, (iter - bin.crbegin()));
    }
    return dec;
}

ull product(const vector<ull>& literals) {
    ull out = 1;
    for (const auto& el : literals)
        out *= el;
    return out;
}

ull solveLiterals(int IDdec, vector<ull>& literals) {
    ull numToReturn = 0;
    switch (IDdec) {
    case 0:
        numToReturn = std::accumulate(literals.begin(), literals.end(), 0ull);
        break;
    case 1:
        numToReturn = product(literals);
        break;
    case 2:
        std::sort(literals.begin(), literals.end());
        numToReturn = literals[0];
        break;
    case 3:
        std::sort(literals.begin(), literals.end());
        numToReturn = literals[literals.size() - 1];
        break;
    case 5:
        numToReturn = literals[0] > literals[1];
        break;
    case 6:
        numToReturn = literals[0] < literals[1];
        break;
    case 7:
        numToReturn = literals[0] == literals[1];
        break;
    }
    return numToReturn;
}

int versionSum = 0;

std::pair<string,ull> parsePacekt(string &packet) {
    string bin = packet;
    string version(bin.begin(), bin.begin() + 3);
    auto Vdec = bin2dec(version);
    
    string ID(bin.begin() + 3, bin.begin() + 6);
    auto IDdec = bin2dec(ID);
    versionSum += Vdec;

    bin.erase(bin.begin(), bin.begin() + 6);
    
    if (IDdec == 4) {
        auto beg = bin.begin();
        auto toShrink = string(beg, bin.end());

        int i = 0;
        while (true) {
            if (*(toShrink.begin() + i * 4) == '0') {
                toShrink.erase(toShrink.begin() + i * 4, toShrink.begin() + i * 4 + 1);
                break;
            }
            toShrink.erase(toShrink.begin() + i * 4, toShrink.begin() + i * 4 + 1);
            i++;
        }
        auto num = bin2dec(string(toShrink.begin(), toShrink.begin() + (i + 1) * 4));
        auto out = string((beg + (i + 1) * 5), bin.end());
        return { out, num };
    }
    else {
        char lengthTypeID = *bin.begin();
        bin.erase(bin.begin(), bin.begin() + 1);
        string subPackets;
        int SubpacketNum;
        vector<int> subpacketNumbers;
        if (lengthTypeID == '0') {
            subPackets = string(bin.begin(), bin.begin() + 15);
            bin.erase(bin.begin(), bin.begin() + 15);
            SubpacketNum = bin2dec(subPackets);

            subPackets = bin;
            vector<ull> literals;
            literals.empty();
            while (true) {
                if (bin.size() - subPackets.size() == SubpacketNum)
                    break;
                auto par = parsePacekt(subPackets);
                subPackets = par.first;
                literals.push_back(par.second);
            }
            ull numToReturn = solveLiterals(IDdec, literals);
            return { subPackets, numToReturn };
        }
        else {
            subPackets = string(bin.begin(), bin.begin() + 11);
            bin.erase(bin.begin(), bin.begin() + 11);
            SubpacketNum = bin2dec(subPackets);
            vector<ull> literals;
            for (int i = 0; i < SubpacketNum; i++) {
                if (i == 20) {
                    cout << "Now" << endl;
                }
                auto par = parsePacekt(bin);
                bin = par.first;
                literals.push_back(par.second);
            }
            ull numToReturn = solveLiterals(IDdec, literals);
            return { bin, numToReturn };
        }
    }
}

ull pt1() {
    fstream file("data.txt");
    string hex;
    vector<uint8_t> data;
    
    file >> hex;
    string bin = hex2bin(hex);
   // cout << bin << endl;

    auto out = parsePacekt(bin);
    cout << "Aswer2: " << out.second << endl;
    cout << versionSum << endl;

    return out.second;

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
//110100010100101001000100100
//110100010100101001000100100
