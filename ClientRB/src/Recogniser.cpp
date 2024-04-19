#include <recogniser.h>

Table FooRecogniser::recogniser(cv::Mat frame) {
    int row = table.getRow();
    int col = table.getCol();
    std::vector<std::vector<std::string>> tableData(row, std::vector<std::string>(col, "0"));

    // Loading a classifier for human detection
    cv::CascadeClassifier human_cascade;
	std::string cascadePath = std::string(CMAKE_CURRENT_BINARY_DIR) + "/Data/haarcascade_fullbody.xml";
    if (!human_cascade.load(cascadePath)) {
        std::cerr << "Failed to load cascade classifier" << std::endl;
        table.setTable(tableData);
        return table;
    }
    // The focal length of the camera (replace with the actual value)
    double focalLength = 1000.0;

    // The actual size of a person in meters
    double realHumanHeight = 1.7; 

    // Detecting a person in the frame
    std::vector<cv::Rect> humans;
    human_cascade.detectMultiScale(frame, humans, 1.1, 2, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));

    // Calculating the distance from the camera to the person and updating the table
    for (const auto& human : humans) {
        double distance = (realHumanHeight * focalLength) / human.height; // Calculating the distance

        // Determining a person's position in the table
        int tableRow = (human.y + human.height / 2) / (frame.rows / row);
        int tableCol = (human.x + human.width / 2) / (frame.cols / col);
        tableData[tableRow][tableCol] = "1";
    }

    table.setTable(tableData);
    return table;
}
