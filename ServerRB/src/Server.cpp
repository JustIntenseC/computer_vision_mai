#include <server.h>
#include <algorithm.h>

void MainServer::ServerLow() {
	Algorithms alg;
	httplib::Server server;
	std::string command_to_send;
	int flag = 0;

	// Handler POST request for /lines
	server.Post("/lines", [&](const httplib::Request& req, httplib::Response& res) {
		try {
			std::string body = req.body;
			d.Parse(body.c_str());
			if (d.HasParseError()) {
				std::cout << "Parse Error at offset " << d.GetErrorOffset()
					<< ". "
					<< rapidjson::GetParseError_En(d.GetParseError())
					<< '\n';
			}
			else {
				std::cout << "RECEIVED: " << body << '\n';
				if (d.HasMember("lines") && d["lines"].IsArray()) {
					const auto& linesArray = d["lines"].GetArray();
					line_data.clear();
					left_line_data.clear();
					right_line_data.clear();
					for (rapidjson::SizeType i = 0; i < linesArray.Size(); ++i) {
						const auto& line = linesArray[i];
						std::unordered_map<std::string, int> line_info;
						line_info["x1"] = line[0].GetInt();
						line_info["y1"] = line[1].GetInt();
						line_info["x2"] = line[2].GetInt();
						line_info["y2"] = line[3].GetInt();
						line_data.push_back(line_info);
						int line_pos = alg.RecogniserLine(line[0].GetInt(), line[1].GetInt(), line[2].GetInt(), line[3].GetInt());
						if (line_pos == 1) {
							left_line_data.push_back(line_info);
						}
						else if (line_pos == 2) {
							right_line_data.push_back(line_info);
						}
					}
					switch (alg.Recogniser(table, line_data, right_line_data, left_line_data)) {
					case 1:
						command_to_send = "Start";
						flag = 1;
						break;
					case 2:
						command_to_send = "Right";
						flag = 1;
						break;
					case 3:
						command_to_send = "Left";
						flag = 1;
						break;
					case 4:
						command_to_send = "Stop";
						flag = 1;
						break;
					default:
						command_to_send = "Noun";
						flag = 2;
						break;
					}
					lines_updated = true;
				}
				res.set_content("Response from server!", "text/plain");
			}
		}
		catch (const std::exception& e) {
			std::cerr << "Exception caught: " << e.what() << std::endl;
			res.status = 400;
			res.set_content("Error: Invalid line data", "text/plain");
		}
	});

	// Handler POST request for /string
	server.Post("/string", [&](const httplib::Request& req, httplib::Response& res) {
		try {
			table = req.body;
			std::cout << "RECEIVED: " << table << std::endl;
		}
		catch (const std::exception& e) {
			std::cerr << "Exception caught: " << e.what() << std::endl;
			res.status = 400;
			res.set_content("Error: Invalid line data", "text/plain");
		}
	});

	// Handler POST request for /command
	server.Post("/command", [&](const httplib::Request& req, httplib::Response& res) {
		if (flag == 1) {
			res.status = 200;
			res.set_content(command_to_send, "text/plain");
		}
		else if (flag == 2) {
			res.status = 404;
			res.set_content("Error: No command available", "text/plain");
		}
	});

	server.listen("0.0.0.0", 8080);
}

void MainServer::ShowLines() {
	cv::Mat image = cv::Mat::zeros(cv::Size(640, 480), CV_8UC3);
	cv::namedWindow("Lines", 1);
	while (true) {
		if (lines_updated) {
			lines_updated = false; // Resetting flag after processing
			image.setTo(cv::Scalar(0, 0, 0));

			// Drawing lines
			for (const auto& l : line_data) {
				int x1 = l.at("x1");
				int y1 = l.at("y1");
				int x2 = l.at("x2");
				int y2 = l.at("y2");
				cv::line(image, cv::Point(x1, y1), cv::Point(x2, y2), cv::Scalar(0, 0, 255), 2, cv::LINE_AA);
			}

			imshow("Lines", image);
			cv::waitKey(1);
		}
	}
}
