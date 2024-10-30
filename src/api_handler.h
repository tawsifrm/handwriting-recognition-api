#ifndef API_HANDLER_H
#define API_HANDLER_H

#include <string>
#include <boost/property_tree/ptree.hpp>
#include <opencv2/opencv.hpp>
#include <unordered_map>
#include <chrono>

// The RateLimiter class handles rate limiting logic using a token bucket algorithm.
class RateLimiter {
public:
    RateLimiter(int maxTokens, int refillRate);
    bool allowRequest(const std::string& apiKey);

private:
    int maxTokens;
    int refillRate;
    std::unordered_map<std::string, int> tokens;
    std::unordered_map<std::string, std::chrono::steady_clock::time_point> lastRefillTime;
};

// The APIHandler class handles incoming API requests and routes them to the appropriate handler functions.
class APIHandler {
public:
    APIHandler();
    ~APIHandler();

    // Handles the incoming request and routes it to the appropriate handler function based on the endpoint.
    std::string handleRequest(const std::string& request);

    // Checks if the request is rate limited based on the API key.
    bool isRateLimited(const std::string& apiKey);

private:
    // Handles the image upload request, decodes the image data, and stores it for later recognition.
    std::string handleUpload(const boost::property_tree::ptree& requestTree);

    // Handles the text recognition request, processes the stored image, and returns the recognized text.
    std::string handleRecognize(const boost::property_tree::ptree& requestTree);

    // Generates an error response with the given message.
    std::string generateErrorResponse(const std::string& message);

    // Generates a success response with the given message.
    std::string generateSuccessResponse(const std::string& message);

    // Stores the uploaded image for later recognition.
    cv::Mat storedImage;

    // Instance of the RateLimiter class to handle rate limiting.
    RateLimiter rateLimiter;
};

#endif // API_HANDLER_H
