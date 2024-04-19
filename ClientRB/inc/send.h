#pragma once
#include <iostream>
#include <httplib.h>
#include <opencv2/opencv.hpp>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <vector>

class Send {
public:
	void JsonSend(std::vector<cv::Vec4i>& lines, cv::Mat edges);

	void TableSend(std::string table);
};
