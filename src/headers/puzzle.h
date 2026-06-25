#pragma once
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

extern string inicial;
extern unordered_map<string, string> parent;

bool isGoal(const string& s);
int findBlank(const string& s);
void printState(const string& s);
void showPath(const string& s, const string& ini, int depth);
void showPath2(const string& s, const string& ini, int depth);
vector<string> generateMoves(const string& s);