#define _USE_MATH_DEFINES
#pragma once
#include <iostream>
#include <cmath>
#include <math.h>
#include <vector>
#include <unordered_map>

class Algorithms {
public:
	int calculateAngle(int x1, int y1, int x2, int y2);

	int RecogniserLine(int x1, int y1, int x2, int y2);

	bool Stop(std::string table);

	int Recogniser(std::string table, std::vector<std::unordered_map<std::string, int>> line_data, std::vector<std::unordered_map<std::string, int>> right_line_data, std::vector<std::unordered_map<std::string, int>> left_line_data);
};
