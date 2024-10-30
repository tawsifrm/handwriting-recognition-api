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
    EXPECT_EQ(recognizedText, "Recognized text");
}

TEST_F(HandwritingRecognizerTest, RecognizeNonEmptyImage) {
    cv::Mat nonEmptyImage = cv::Mat::ones(100, 100, CV_8UC1); // Create a non-empty dummy image
    std::string recognizedText = recognizer.recognizeText(nonEmptyImage);
    EXPECT_EQ(recognizedText, "Recognized text");
}
