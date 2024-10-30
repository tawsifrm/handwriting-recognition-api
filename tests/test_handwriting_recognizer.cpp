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
    cv::Mat testImage = cv::Mat::zeros(100, 100, CV_8UC1); // Create a dummy image
    std::string recognizedText = recognizer.recognizeText(testImage);
    EXPECT_EQ(recognizedText, "Recognized text");
}

TEST_F(HandwritingRecognizerTest, RecognizeEmptyImage) {
    cv::Mat emptyImage;
    std::string recognizedText = recognizer.recognizeText(emptyImage);
    EXPECT_EQ(recognizedText, "Error: Empty image");
}

TEST_F(HandwritingRecognizerTest, RecognizeNonEmptyImage) {
    cv::Mat nonEmptyImage = cv::Mat::ones(100, 100, CV_8UC1); // Create a non-empty dummy image
    std::string recognizedText = recognizer.recognizeText(nonEmptyImage);
    EXPECT_EQ(recognizedText, "Recognized text");
}

TEST_F(HandwritingRecognizerTest, RecognizeInvalidImage) {
    cv::Mat invalidImage = cv::Mat::zeros(0, 0, CV_8UC1); // Create an invalid image
    std::string recognizedText = recognizer.recognizeText(invalidImage);
    EXPECT_EQ(recognizedText, "Error: Empty image");
}

TEST_F(HandwritingRecognizerTest, RecognizeLargeImage) {
    cv::Mat largeImage = cv::Mat::ones(1000, 1000, CV_8UC1); // Create a large dummy image
    std::string recognizedText = recognizer.recognizeText(largeImage);
    EXPECT_EQ(recognizedText, "Recognized text");
}

TEST_F(HandwritingRecognizerTest, RecognizeColoredImage) {
    cv::Mat coloredImage = cv::Mat::ones(100, 100, CV_8UC3); // Create a colored dummy image
    std::string recognizedText = recognizer.recognizeText(coloredImage);
    EXPECT_EQ(recognizedText, "Recognized text");
}
