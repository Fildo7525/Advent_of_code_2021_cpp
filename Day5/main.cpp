#include <iostream>
#include <fstream>
#include <map>
using namespace std;

int uloha1();
int uloha2();

int main() {
	cout << uloha2() << endl;
}

void reorder(pair<int, int>& a, pair<int, int>& b) {
		if (a.first > b.first)
			std::swap(a.first, b.first);
		if (a.second > b.second)
			std::swap(a.second, b.second);
}

int uloha2() {
	fstream file("data.txt");
	string arrow;
	pair<int, int> in, out;
	map<pair<int, int>, int> HV;
	char a;

	while (file >> in.first >> a >> in.second >> arrow >> out.first >> a >> out.second) {
		//reorder(in, out);
		auto dx = out.first - in.first;
		auto dy = out.second - in.second;
		for (auto i = 0; i != (1 + (abs(dx) > abs(dy) ? abs(dx) : abs(dy))); i++) {
			auto x = in.first + (dx > 0 ? 1 : (dx < 0 ? -1 : 0)) * i;
			auto y = in.second + (dy > 0 ? 1 : (dy < 0 ? -1 : 0)) * i;
			HV[{ x,y }]++;
		}
	}

	int ans = 0;
	for (auto iter = HV.begin(); iter != HV.end(); iter++) {
		if (iter->second > 1) {
			//cout << '(' << iter->first.first << ", " << iter->first.second << ") = " << iter->second << endl;
			ans++;
		}
	}
	return ans;

}

int uloha1() {
	fstream file("test.txt");
	string arrow;
	pair<int, int> in, out;
	map<pair<int, int>, int> HV;
	char a;

	while (file >> in.first >> a >> in.second >> arrow >> out.first >> a >> out.second) {
		reorder(in, out);
		if (in.first == out.first || in.second == out.second) {
			for (auto x = in.first; x != out.first + 1; x++) {
				for (auto y = in.second; y != out.second + 1; y++) {
					HV[{ x,y }]++;
				}
			}
		}
	}

	int ans = 0;
	for (auto iter = HV.begin(); iter != HV.end(); iter++) {
		if (iter->second > 1) {
			ans++;
		}
	}
	return ans;

}