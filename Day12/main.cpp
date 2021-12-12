#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <set>
#include <functional>
#include <algorithm>
using namespace std;

int uloha1();
int uloha2();

int main() {
	cout << uloha2() << endl;
}

bool isLow(char c) {
	return (c >= 'a' && c <= 'z');
}

bool isBig(char c) {
	return (c >= 'A' && c <= 'Z');
}

int uloha1() {
	fstream file("data.txt");
	map<string, vector<string>> graph;
	vector<string> visited;
	string verticleStart, verticleEnd, help;

	int pathCount = 0;

	while (file >> help) {
		verticleStart = help.substr(0, help.find('-'));
		verticleEnd = help.substr(help.find('-')+1);
		graph[verticleStart].push_back(verticleEnd);
		graph[verticleEnd].push_back(verticleStart);
	}

	function<void(string, vector<string>)> dfs = [&graph, &pathCount, &dfs](string point, vector<string> alreadyVisited) {
		if (point == "end")
			pathCount++;
		else {
			for (auto& pointToVisit : graph[point])
				if (isLow(pointToVisit[0]) && find(alreadyVisited.cbegin(), alreadyVisited.cend(), pointToVisit) == alreadyVisited.end()) {
					alreadyVisited.push_back(pointToVisit);
					dfs(pointToVisit, alreadyVisited);
					alreadyVisited.pop_back();
				}
				else if (isBig(pointToVisit[0])) {
					//alreadyVisited.push_back(pointToVisit);
					dfs(pointToVisit, alreadyVisited);
					//alreadyVisited.pop_back();
				}
		}
	};

	visited.push_back("start");
	dfs("start", visited);
	return pathCount;
}

bool countSmall(map<string, int>& alreadyVisited, string pointToVisit) {
	int numberOfTwos = 0;
	alreadyVisited[pointToVisit]++;
	for (const auto& el : alreadyVisited) {
		if (el.second == 2)
			numberOfTwos++;
		else if (el.second > 2) {
			alreadyVisited[pointToVisit]--;
			return false;
		}
	}
	alreadyVisited[pointToVisit]--;
	if (numberOfTwos > 1)
		return false;
	return true;
}

int uloha2() {
	fstream file("data.txt");
	map<string, vector<string>> graph;
	map<string,int> visited;
	string verticleStart, verticleEnd, help;

	int pathCount = 0;

	while (file >> help) {
		verticleStart = help.substr(0, help.find('-'));
		verticleEnd = help.substr(help.find('-') + 1);
		graph[verticleStart].push_back(verticleEnd);
		graph[verticleEnd].push_back(verticleStart);
	}

	function<void(string, map<string, int>)> dfs = [&graph, &pathCount, &dfs](string point, map<string, int> alreadyVisited) {
		if (point == "end")
			pathCount++;
		else {
			for (auto& pointToVisit : graph[point])
				if (isLow(pointToVisit[0]) && pointToVisit != "start" && countSmall(alreadyVisited, pointToVisit)) {
					alreadyVisited[pointToVisit]++;
					dfs(pointToVisit, alreadyVisited);
					alreadyVisited[pointToVisit]--;
				}
				else if (isBig(pointToVisit[0])) {
					dfs(pointToVisit, alreadyVisited);
				}
		}
	};

	visited["start"]++;
	dfs("start", visited);
	return pathCount;
}
