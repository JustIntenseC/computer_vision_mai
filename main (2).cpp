#include <opencv2/opencv.hpp>
#include <iostream>
#include <httplib.h>

using namespace httplib;
using namespace std;
using namespace cv;

void Ser() {
	Server svr;

	svr.Get("/hi", [](const Request& /*req*/, Response& res) { //По запросу к адресу 0.0.0.0:8080/hi Вернуть текст
		res.set_content("Hello World!", "text/plain"); //Текст для возврата и формат
		});

	svr.Get("/", [](const Request& /*req*/, Response& res) { //По запросу к адресу 0.0.0.0:8080/ Вернуть текст
		res.set_content("Main Pages!", "text/plain");
		});

	svr.listen("0.0.0.0", 8080); // 0.0.0.0:8080 Ип куда розшарить, Ип вашого пк ну и порт
}

int foo() {
	VideoCapture cap(0); // Открываем камеру или файл
	std::thread th(Ser);
	if (!cap.isOpened()) // check if we succeeded
		return -1;
	Mat edges;
	namedWindow("edges", 1);
	while (1) {
		Mat frame;
		cap >> frame; // get a new frame from camera
		cvtColor(frame, edges, COLOR_BGR2GRAY); // Перевод в градации серого
		GaussianBlur(edges, edges, Size(7, 7), 1.5, 1.5); // Размытие
		Canny(edges, edges, 0, 30, 3); // Выделение границ
		vector<Vec4i> lines;
		HoughLinesP(edges, lines, 1, CV_PI / 180, 100, 50, 300);
		for (size_t i = 0; i < lines.size(); i++) {
			Vec4i l = lines[i];
			line(edges, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255, 0, 0), 3, LINE_AA);
		}
		imshow("edges", edges);
		if (waitKey(30) >= 0) break;

	}
	return 0;
}

int main(int, char**) {
	foo();
}
