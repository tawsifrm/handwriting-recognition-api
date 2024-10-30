#include "api_handler.h"
#include "handwriting_recognizer.h"
#include <opencv2/opencv.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/algorithm/string.hpp>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <unordered_map>

// RateLimiter class implementation
RateLimiter::RateLimiter(int maxTokens, int refillRate)
    : maxTokens(maxTokens), refillRate(refillRate) {}

bool RateLimiter::allowRequest(const std::string& apiKey) {
    auto now = std::chrono::steady_clock::now();
    auto& tokens = this->tokens[apiKey];
    auto& lastRefill = this->lastRefillTime[apiKey];

    if (tokens < maxTokens) {
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - lastRefill).count();
        tokens += duration * refillRate;
        if (tokens > maxTokens) {
            tokens = maxTokens;
        }
        lastRefill = now;
    }

    if (tokens > 0) {
        --tokens;
        return true;
    }

    return false;
}

// APIHandler class handles incoming API requests and routes them to the appropriate handler functions.
APIHandler::APIHandler() : rateLimiter(100, 1) {
    // Constructor implementation
}

APIHandler::~APIHandler() {
    // Destructor implementation
}

// Handles the incoming request and routes it to the appropriate handler function based on the endpoint.
std::string APIHandler::handleRequest(const std::string& request) {
    std::istringstream requestStream(request);
    boost::property_tree::ptree requestTree;
    boost::property_tree::read_json(requestStream, requestTree);

    std::string apiKey = requestTree.get<std::string>("api_key");
    if (isRateLimited(apiKey)) {
        return generateErrorResponse("Rate limit exceeded");
    }

    std::string endpoint = requestTree.get<std::string>("endpoint");
    std::string response;

    if (endpoint == "/api/upload") {
        response = handleUpload(requestTree);
    } else if (endpoint == "/api/recognize") {
        response = handleRecognize(requestTree);
    } else {
        response = generateErrorResponse("Invalid endpoint");
    }

    return response;
}

// Checks if the request is rate limited based on the API key.
bool APIHandler::isRateLimited(const std::string& apiKey) {
    return !rateLimiter.allowRequest(apiKey);
}

// Handles the image upload request, decodes the image data, and stores it for later recognition.
std::string APIHandler::handleUpload(const boost::property_tree::ptree& requestTree) {
    std::string imageData = requestTree.get<std::string>("image_data");
    std::vector<uchar> data(imageData.begin(), imageData.end());
    cv::Mat image = cv::imdecode(data, cv::IMREAD_COLOR);

    if (image.empty()) {
        return generateErrorResponse("Invalid image data");
    }

    // Store the image for later recognition
    storedImage = image;

    return generateSuccessResponse("Image uploaded successfully");
}

// Handles the text recognition request, processes the stored image, and returns the recognized text.
std::string APIHandler::handleRecognize(const boost::property_tree::ptree& requestTree) {
    if (storedImage.empty()) {
        return generateErrorResponse("No image uploaded");
    }

    HandwritingRecognizer recognizer;
    std::string recognizedText = recognizer.recognizeText(storedImage);

    boost::property_tree::ptree responseTree;
    responseTree.put("recognized_text", recognizedText);

    std::ostringstream responseStream;
    boost::property_tree::write_json(responseStream, responseTree);

    return responseStream.str();
}

// Generates an error response with the given message.
std::string APIHandler::generateErrorResponse(const std::string& message) {
    boost::property_tree::ptree responseTree;
    responseTree.put("status", "error");
    responseTree.put("message", message);

    std::ostringstream responseStream;
    boost::property_tree::write_json(responseStream, responseTree);

    return responseStream.str();
}

// Generates a success response with the given message.
std::string APIHandler::generateSuccessResponse(const std::string& message) {
    boost::property_tree::ptree responseTree;
    responseTree.put("status", "success");
    responseTree.put("message", message);

    std::ostringstream responseStream;
    boost::property_tree::write_json(responseStream, responseTree);

    return responseStream.str();
}
