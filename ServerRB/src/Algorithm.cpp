#include <algorithm.h>

int Algorithms::calculateAngle(int x1, int y1, int x2, int y2) {
	double delta_x = x2 - x1;
	double delta_y = y2 - y1;
	double radians = std::atan2(delta_y, delta_x);
	double degrees = std::fmod(std::abs(std::round(std::fmod(radians * 180.0 / (M_PI), 360.0))), 360.0);
	return degrees;
}

int Algorithms::RecogniserLine(int x1, int y1, int x2, int y2) {
	int degrees = calculateAngle(x1, y1, x2, y2);
	if ((degrees >= 10 && degrees <= 80)) {
		if ((y1 >= y2) && (y1 >= 230)) {
			return 1; // left
		}
		else if ((y1 <= y2) && (y2 >= 230)) {
			return 2; // right
		}
		return 3;
	}
	else {
		return 0;
	}
}

bool Algorithms::Stop(std::string table) {
	for (int i = 25; i <= 28; ++i) {
		if (table[i] == '1') {
			return true;
		}
	}
	for (int i = 31; i <= 34; ++i) {
		if (table[i] == '1') {
			return true;
		}
	}
	return false;
}

int Algorithms::Recogniser(std::string table, std::vector<std::unordered_map<std::string, int>> line_data, std::vector<std::unordered_map<std::string, int>> right_line_data, std::vector<std::unordered_map<std::string, int>> left_line_data) {
	if (right_line_data.empty() || left_line_data.empty()) {
		std::cout << "Noun line\n" << std::endl;
		return 4;
	}
	bool tab = Stop(table);

	int R_x1 = 0, R_y1 = 0, R_x2 = 0, R_y2 = 0;
	for (const auto& R_line : right_line_data) {
		R_x1 += R_line.at("x1");
		R_y1 += R_line.at("y1");
		R_x2 += R_line.at("x2");
		R_y2 += R_line.at("y2");
	}
	double avgR_x1 = R_x1 / right_line_data.size();
	double avgR_y1 = R_y1 / right_line_data.size();
	double avgR_x2 = R_x2 / right_line_data.size();
	double avgR_y2 = R_y2 / right_line_data.size();

	int L_x1 = 0, L_y1 = 0, L_x2 = 0, L_y2 = 0;
	for (const auto& L_line : left_line_data) {
		L_x1 += L_line.at("x1");
		L_y1 += L_line.at("y1");
		L_x2 += L_line.at("x2");
		L_y2 += L_line.at("y2");
	}
	double avgL_x1 = L_x1 / left_line_data.size();
	double avgL_y1 = L_y1 / left_line_data.size();
	double avgL_x2 = L_x2 / left_line_data.size();
	double avgL_y2 = L_y2 / left_line_data.size();

	int avg_third_x1 = (avgR_x1 + avgL_x1) / 2;
	int avg_third_y1 = (avgR_y1 + avgL_y1) / 2;
	int avg_third_x2 = (avgR_x2 + avgL_x2) / 2;
	int avg_third_y2 = (avgR_y2 + avgL_y2) / 2;

	double degrees = calculateAngle(avg_third_x1, avg_third_y1, avg_third_x2, avg_third_y2);
	int stor = 0;
	if ((avg_third_y1 >= avg_third_y2)) {
		stor = 1; // left
	}
	else if ((avg_third_y1 <= avg_third_y2)) {
		stor =  2; // right
	}

	if (degrees <= 5) {
		std::cout << "Move Start " << degrees << "\n" << std::endl;
		return 1;
	}
	else {
		if ((stor == 2) && !tab) {
			std::cout << "Move Right " << degrees << "\n" << std::endl;
			return 2;
		}
		else if ((stor == 1) && !tab) {
			std::cout << "Move Left " << degrees << "\n" << std::endl;
			return 3;
		}
		else {
			std::cout << "Move Stop\n" << std::endl;
			return 4;
		}
	}
}
