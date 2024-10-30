#ifndef HANDWRITING_RECOGNIZER_H
#define HANDWRITING_RECOGNIZER_H

#include <string>
#include <opencv2/opencv.hpp>

// The HandwritingRecognizer class provides functionality to recognize text from handwritten images.
class HandwritingRecognizer {
public:
    // Constructor
    HandwritingRecognizer();

    // Destructor
    ~HandwritingRecognizer();

    // Recognizes text from the given image using OpenCV and other necessary libraries.
    // @param image The input image containing handwritten text.
    // @return The recognized text as a string.
    std::string recognizeText(const cv::Mat& image);
};

#endif // HANDWRITING_RECOGNIZER_H
