#include "handwriting_recognizer.h"
#include <iostream>
#include <opencv2/text.hpp>

// Constructor implementation
HandwritingRecognizer::HandwritingRecognizer() {
    // Constructor implementation
}

// Destructor implementation
HandwritingRecognizer::~HandwritingRecognizer() {
    // Destructor implementation
}

// Recognizes text from the given image using OpenCV and other necessary libraries
std::string HandwritingRecognizer::recognizeText(const cv::Mat& image) {
    if (image.empty()) {
        std::cerr << "Error: Empty image provided for text recognition" << std::endl;
        return "Error: Empty image";
    }

    // Convert the image to grayscale
    cv::Mat grayImage;
    cv::cvtColor(image, grayImage, cv::COLOR_BGR2GRAY);

    // Use OpenCV's OCR (Optical Character Recognition) to recognize text
    cv::Ptr<cv::text::OCRTesseract> ocr = cv::text::OCRTesseract::create();
    std::string recognizedText;
    ocr->run(grayImage, recognizedText);

    return recognizedText;
}
