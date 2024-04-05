#include <header.h>

class Robot {
public:
	// Drawing lines on edges and returns json
	json WriteLine(vector<Vec4i> lines, Mat edges) {
		json line_data;
		for (size_t i = 0; i < lines.size(); i++) {
			Vec4i l = lines[i];
			line_data.push_back({ {"x1", l[0]}, {"y1", l[1]}, {"x2", l[2]}, {"y2", l[3]} });
			line(edges, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255, 0, 0), 3, LINE_AA);
		}
		return line_data.dump();
	}

	// Sends json to the server
	void Send(vector<Vec4i> lines, Mat edges) {
		Client client("http://127.0.0.1:8080");
		auto res = client.Post("/lines", WriteLine(lines, edges), "application/json");
		if (res && res->status == 200) {
			cout << "Lines sent successfully" << endl;
		}
		else {
			cerr << "Error sending lines to server" << endl;
		}
	}

	// Video stream processing
	int App() {
		VideoCapture cap(0); // Opening the camera
		if (!cap.isOpened()) // Checking for success
			return -1;
		Mat edges;
		namedWindow("edges", 1);
		while (1) {
			Mat frame;
			cap >> frame; // Getting frame from camera
			cvtColor(frame, edges, COLOR_BGR2GRAY); // Grayscale translation
			GaussianBlur(edges, edges, Size(7, 7), 1.5, 1.5); // Blur
			Canny(edges, edges, 0, 30, 3); // Border selection 
			vector<Vec4i> lines;
			HoughLinesP(edges, lines, 1, CV_PI / 180, 100, 50, 300);
			Send(lines, edges);
			imshow("edges", edges);
			if (waitKey(30) >= 0) break;
		}
		return 0;
	}
};

class SRV {
public :
	json line_data;
	atomic<bool> lines_updated{ false };

	// Create server
	void Server_laptop() {
		Server server;

		// Handler POST request for /lines
		server.Post("/lines", [&](const Request& req, Response& res) {
			try {
				json data = json::parse(req.body); // Getting data from body of POST request

				line_data = data;
				lines_updated = true;

				res.status = 200;
				res.set_content("Lines received successfully", "text/plain");
			}
			catch (const exception& e) {
				cerr << "Exception caught: " << e.what() << endl;
				res.status = 400;
				res.set_content("Error: Invalid line data", "text/plain");
			}
			});

		// Handler GET request for /line
		server.Get("/line", [&](const Request& req, Response& res) {
			try {
				res.status = 200;
				res.set_content(line_data.dump(), "application/json");
			}
			catch (const exception& e) {
				cerr << "Exception caught: " << e.what() << endl;
				res.status = 500;
				res.set_content("Error: Internal server error", "text/plain");
			}
			});

		server.listen("0.0.0.0", 8080);
	}

	// Create Window where lines will be
	void ShowLines() {
		Mat image = Mat::zeros(Size(640, 480), CV_8UC3);
		namedWindow("Lines", 1);
		while (true) {
			if (lines_updated) {
				lines_updated = false; // Resetting flag after processing
				image.setTo(Scalar(0, 0, 0));

				// Drawing lines
				for (const auto& lines : line_data) {
					int x1 = lines["x1"];
					int y1 = lines["y1"];
					int x2 = lines["x2"];
					int y2 = lines["y2"];
					line(image, Point(x1, y1), Point(x2, y2), Scalar(0, 0, 255), 2, LINE_AA);
				}

				imshow("Lines", image);
				waitKey(1); 
			}
		}
	}
};

int main(int, char**) {
	SRV srv;
	Robot app;
	thread th_1{ &SRV::Server_laptop, &srv };
	thread th_2{ &SRV::ShowLines, &srv };
	app.App();
	return 0;
}
