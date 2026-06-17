#pragma once
#include <string>
#include <vector>
#include <unordered_map>

extern std::string inicial;
extern std::unordered_map<std::string, std::string> parent;

bool isGoal(const std::string& s);
int findBlank(const std::string& s);
void printState(const std::string& s);
void showPath(const std::string& s, const std::string& ini, int depth);
std::vector<std::string> generateMoves(const std::string& s);