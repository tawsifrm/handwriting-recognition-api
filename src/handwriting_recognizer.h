#ifndef HANDWRITING_RECOGNIZER_H
#define HANDWRITING_RECOGNIZER_H

#include <string>
#include <opencv2/opencv.hpp>

class HandwritingRecognizer {
public:
    HandwritingRecognizer();
    ~HandwritingRecognizer();

    std::string recognizeText(const cv::Mat& image);
};

#endif // HANDWRITING_RECOGNIZER_H
