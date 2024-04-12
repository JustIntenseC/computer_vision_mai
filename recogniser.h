#pragma once
#include <opencv2/opencv.hpp>
#include <table.h>

class Recogniser {
protected:
    Table table; 
public:
    Recogniser(int rows, int cols) : table(rows, cols, {}) {}
    virtual Table recogniser(cv::Mat frame) = 0;
};

class FooRecogniser : public Recogniser {
public:
    FooRecogniser(int rows, int cols) : Recogniser(rows, cols) {}
    Table recogniser(cv::Mat frame) override;
};
