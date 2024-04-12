#include <application.h>
#include <send.h>
#include <clientget.h>

int Application::process() {
	Send send;
	cv::VideoCapture cap(0); // Opening the camera
	if (!cap.isOpened()) // Checking for success
		return -1;
	cv::Mat edges;
	cv::namedWindow("edges", 1);
	while (1) {
		cv::Mat frame;
		cap >> frame; // Getting frame from camera
		cv::cvtColor(frame, edges, cv::COLOR_BGR2GRAY); // Grayscale translation
		cv::GaussianBlur(edges, edges, cv::Size(7, 7), 1.5, 1.5); // Blur
		cv::Canny(edges, edges, 10, 30, 3, 1); // Border selection
		send.TableSend(show(recogniser->recogniser(frame)));
		/*
		// Detection of the Harris method
		cv::Mat corners;
		cv::cornerHarris(edges, corners, 2, 3, 0.04);
		cv::threshold(corners, corners, 0.01, 255, cv::THRESH_BINARY);
		*/
		std::vector<cv::Vec4i> lines;
		cv::HoughLinesP(edges, lines, 1, CV_PI / 180, 120, 150, 40);
		for (size_t i = 0; i < lines.size(); i++) {
			cv::Vec4i l = lines[i];
			cv::line(edges, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]), cv::Scalar(255, 0, 0), 3, cv::LINE_AA);
		}
		/*
		// Rendering Harris method on image
		for (int i = 0; i < corners.rows; i++) {
			for (int j = 0; j < corners.cols; j++) {
				if ((int)corners.at<float>(i, j) > 0) {
					cv::circle(frame, cv::Point(j, i), 5, cv::Scalar(0, 255, 0), 2);
				}
			}
		}
		*/
		send.JsonSend(lines, edges);
		cv::imshow("edges", edges);
		if (cv::waitKey(30) >= 0) break;
	}
	return 0;
}

void Application::run() {
	ClientGet CG;
	std::string command;
	while (1) {
		int a = CG.GetCommand();
		switch (a) {
		case 1:
			command = "Start";
			break;
		case 2:
			command = "Right";
			break;
		case 3:
			command = "Left";
			break;
		case 4:
			command = "Stop";
			break;
		default:
			break;
		}
	}
}

std::string Application::show(Table frame) {
	std::string table;
	for (int i = 0; i < frame.getRow(); ++i) {
		for (int j = 0; j < frame.getCol(); ++j) {
			table += frame.get(i, j);
			std::cout << frame.get(i, j) << " ";
		}
		std::cout << std::endl;
	}
	return table;
}
