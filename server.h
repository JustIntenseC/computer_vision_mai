#pragma once
#include <iostream>
#include <httplib.h>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include "rapidjson/error/en.h"
#include <opencv2/opencv.hpp>
#include <atomic>

class MainServer {
private:
	rapidjson::Document d;
	std::vector<std::unordered_map<std::string, int>> line_data;
	std::vector<std::unordered_map<std::string, int>> right_line_data;
	std::vector<std::unordered_map<std::string, int>> left_line_data;
	std::string table;
	std::atomic<bool> lines_updated{ false };
	std::atomic<bool> table_updated{ false };
public:
	void ServerLow();

	void ShowLines();
};

