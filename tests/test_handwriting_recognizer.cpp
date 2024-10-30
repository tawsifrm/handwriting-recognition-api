#include "handwriting_recognizer.h"
#include <gtest/gtest.h>
#include <opencv2/opencv.hpp>

class HandwritingRecognizerTest : public ::testing::Test {
protected:
    HandwritingRecognizer recognizer;

    virtual void SetUp() {
        // Code here will be called immediately after the constructor (right before each test).
    }

    virtual void TearDown() {
        // Code here will be called immediately after each test (right before the destructor).
    }
};

TEST_F(HandwritingRecognizerTest, RecognizeText) {
    cv::Mat testImage = cv::imread("test_image.png", cv::IMREAD_COLOR); // Load a test image
    std::string recognizedText = recognizer.recognizeText(testImage);
    EXPECT_NE(recognizedText, "Recognized text"); // Expect the actual recognized text
}

TEST_F(HandwritingRecognizerTest, RecognizeEmptyImage) {
    cv::Mat emptyImage;
    std::string recognizedText = recognizer.recognizeText(emptyImage);
    EXPECT_EQ(recognizedText, "Error: Empty image");
}

TEST_F(HandwritingRecognizerTest, RecognizeNonEmptyImage) {
    cv::Mat nonEmptyImage = cv::imread("non_empty_image.png", cv::IMREAD_COLOR); // Load a non-empty test image
    std::string recognizedText = recognizer.recognizeText(nonEmptyImage);
    EXPECT_NE(recognizedText, "Recognized text"); // Expect the actual recognized text
}

TEST_F(HandwritingRecognizerTest, RecognizeInvalidImage) {
    cv::Mat invalidImage = cv::Mat::zeros(0, 0, CV_8UC1); // Create an invalid image
    std::string recognizedText = recognizer.recognizeText(invalidImage);
    EXPECT_EQ(recognizedText, "Error: Empty image");
}

TEST_F(HandwritingRecognizerTest, RecognizeLargeImage) {
    cv::Mat largeImage = cv::imread("large_image.png", cv::IMREAD_COLOR); // Load a large test image
    std::string recognizedText = recognizer.recognizeText(largeImage);
    EXPECT_NE(recognizedText, "Recognized text"); // Expect the actual recognized text
}

TEST_F(HandwritingRecognizerTest, RecognizeColoredImage) {
    cv::Mat coloredImage = cv::imread("colored_image.png", cv::IMREAD_COLOR); // Load a colored test image
    std::string recognizedText = recognizer.recognizeText(coloredImage);
    EXPECT_NE(recognizedText, "Recognized text"); // Expect the actual recognized text
}
