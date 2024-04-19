#include <send.h>

void Send::JsonSend(std::vector<cv::Vec4i>& lines, cv::Mat edges) {
	rapidjson::StringBuffer s;
	rapidjson::Writer<rapidjson::StringBuffer> writer(s);
	writer.StartObject();
	writer.Key("lines");
	writer.StartArray();
	for (unsigned i = 0; i < lines.size(); ++i) {
		cv::Vec4i& l = lines[i];
		cv::line(edges, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]), cv::Scalar(255, 0, 0), 3, cv::LINE_AA);
		writer.StartArray();
		for (unsigned j = 0; j < 4; ++j) {
			writer.Uint(l[j]);
		}
		writer.EndArray();
	}
	writer.EndArray();
	writer.EndObject();

	std::cout << "SENDING: " << s.GetString() << std::endl;
	httplib::Client cli("http://127.0.0.1:8080");
	auto res = cli.Post("/lines", s.GetString(), "application/json");
	if (res && res->status == 200) {
		std::cout << "\n";
	}
	else {
		std::cerr << "Request failed, error code: " << (res ? res->status : -1) << std::endl;
	}
}

void Send::TableSend(std::string table) {
	std::cout << "SENDING: " << table << std::endl;
	httplib::Client cli("http://127.0.0.1:8080");
	auto res = cli.Post("/string", table, "text/plain");
	if (res && res->status == 200) {
		std::cout << "\n";
	}
	else {
		std::cerr << "Request failed, error code: " << (res ? res->status : -1) << std::endl;
	}
}
