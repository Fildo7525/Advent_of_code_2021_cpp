// Day17.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <map>
#include <cmath>
using namespace std;
using ull = unsigned long long;
using ll = long long;

ull pt1();

int main()
{
    pt1();
}

ull pt1() {
    fstream file("data.txt");
    char ctrash;
    string trash;
    pair<int, int> x, y;// , position{ 0,0 };

    getline(file, trash, '=');
    file >> x.first >> ctrash >> ctrash >> x.second;
    getline(file, trash, '=');
    file >> y.first >> ctrash >> ctrash >>  y.second;
    //cout << x.first << ' ' << x.second << '\n' << y.first << ' ' << y.second << '\n' << endl;

    pair<ll, ll> position;
    pair<int, int> velocity;
    ll hit = 0;
    ll ans = 0;
    
    for (int vertical = 0; vertical <= 2000; vertical++) {
        for (int horizontal = -2000; horizontal <= 2000; horizontal++) {
            bool hitTarget = false;
            ll yMax = 0;
            position = { 0,0 };
            velocity = { vertical, horizontal };

            for (int step = 0; step < 1000; step++) {
                position.first += velocity.first;
                position.second += velocity.second;
                
                yMax = std::max(yMax, position.second);

                if (velocity.first > 0)
                    velocity.first--;
                else if (velocity.first < 0)
                    velocity.first++;
                velocity.second--;

                if (position.first >= x.first && position.first <= x.second && position.second >= y.first && position.second <= y.second)
                    hitTarget = true;
            }
            if (hitTarget) {
                hit++;
                //cout << vertical << ' ' << horizontal << ' ' << hit << '\n';
                ans = std::max(ans, yMax);
            }
        }
    }

    cout << "pt1: " << ans << "\npt2: " << hit << endl;
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
