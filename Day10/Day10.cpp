// Day10.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

#define PARANTHES_COST 1 // 3
#define BRACKET_COST 2 // 57
#define CURLYBRACE_COST 3 // 1197
#define BEAKY_COST 4 // 25137

int uloha1();
unsigned long long uloha2();

int main()
{
    std::cout << uloha2() << endl;
}

int determineCost(const char& c) {
    if (c == '<')
        return BEAKY_COST;
    else if (c == '{')
        return CURLYBRACE_COST;
    else if (c == '[')
        return BRACKET_COST;
    else if(c == '(')
        return PARANTHES_COST;
}

unsigned long long emptiedStack(stack<char>& openedParantheses) {
    unsigned long long tempSum = 0;
    while (!openedParantheses.empty()) {
        tempSum = tempSum * 5 + determineCost(openedParantheses.top());
        openedParantheses.pop();
    }
    return tempSum;
}


int uloha1() {
    fstream file("data.txt");
    string line;
    long long sum = 0;
    while (file >> line) {
        stack<char> opendParantheses;
        for (auto iter = line.cbegin(); iter != line.cend(); iter++) {
            const auto& el = *iter;
            if (el == '{' || el == '(' || el == '[' || el == '<')
                opendParantheses.push(el);
            else if (el == '}') {
                if (opendParantheses.top() != '{') {
                    sum += determineCost(el);
                    opendParantheses._Get_container().~deque();
                    break;
                }
                opendParantheses.pop();
            }
            else if (el == ']') {
                if (opendParantheses.top() != '[') {
                    sum += determineCost(el);
                    opendParantheses._Get_container().~deque();
                    break;
                }
                opendParantheses.pop();
            }
            else if (el == ')') {
                if (opendParantheses.top() != '(') {
                    sum += determineCost(el);
                    opendParantheses._Get_container().~deque();
                    break;
                }
                opendParantheses.pop();
            }
            else if (el == '>') {
                if (opendParantheses.top() != '<') {
                    sum += determineCost(el);
                    opendParantheses._Get_container().~deque();
                    break;
                }
                opendParantheses.pop();
            }
            if (iter == line.cend() - 1) {
                sum += emptiedStack(opendParantheses);
            }
        }
    }
    return sum;
}

unsigned long long uloha2() {
    fstream file("data.txt");
    string line;
    vector<unsigned long long> sums;
    bool corrupted;
    while (file >> line) {
        corrupted = false;
        stack<char> openedParantheses;
        for (auto iter = line.cbegin(); iter != line.cend(); iter++) {
            const auto& el = *iter;
            if (el == '{' || el == '(' || el == '[' || el == '<')
                openedParantheses.push(el);
            else if (el == '}') {
                if (openedParantheses.top() != '{') {
                    corrupted = true;
                    break;
                }
                openedParantheses.pop();
            }
            else if (el == ']') {
                if (openedParantheses.top() != '[') {
                    corrupted = true;
                    break;
                }
                openedParantheses.pop();
            }
            else if (el == ')') {
                if (openedParantheses.top() != '('){ 
                    corrupted = true;
                    break;
                }
                openedParantheses.pop();
            }
            else if (el == '>') {
                if (openedParantheses.top() != '<') {
                    corrupted = true;
                    break;
                }
                openedParantheses.pop();
            }
            }
        if (!corrupted) {
            sums.push_back(emptiedStack(openedParantheses));
        }
    }
    sort(sums.begin(), sums.end());
    return sums[sums.size()/2];

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
