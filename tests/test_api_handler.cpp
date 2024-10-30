#include "api_handler.h"
#include <gtest/gtest.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

class APIHandlerTest : public ::testing::Test {
protected:
    APIHandler apiHandler;

    virtual void SetUp() {
        // Code here will be called immediately after the constructor (right before each test).
    }

    virtual void TearDown() {
        // Code here will be called immediately after each test (right before the destructor).
    }
};

TEST_F(APIHandlerTest, HandleUpload) {
    boost::property_tree::ptree requestTree;
    requestTree.put("endpoint", "/api/upload");
    requestTree.put("image_data", "dummy_image_data");

    std::ostringstream requestStream;
    boost::property_tree::write_json(requestStream, requestTree);

    std::string response = apiHandler.handleRequest(requestStream.str());

    boost::property_tree::ptree responseTree;
    std::istringstream responseStream(response);
    boost::property_tree::read_json(responseStream, responseTree);

    EXPECT_EQ(responseTree.get<std::string>("status"), "success");
    EXPECT_EQ(responseTree.get<std::string>("message"), "Image uploaded successfully");
}

TEST_F(APIHandlerTest, HandleRecognize) {
    // First, upload an image
    boost::property_tree::ptree uploadRequestTree;
    uploadRequestTree.put("endpoint", "/api/upload");
    uploadRequestTree.put("image_data", "dummy_image_data");

    std::ostringstream uploadRequestStream;
    boost::property_tree::write_json(uploadRequestStream, uploadRequestTree);

    apiHandler.handleRequest(uploadRequestStream.str());

    // Then, recognize the uploaded image
    boost::property_tree::ptree recognizeRequestTree;
    recognizeRequestTree.put("endpoint", "/api/recognize");

    std::ostringstream recognizeRequestStream;
    boost::property_tree::write_json(recognizeRequestStream, recognizeRequestTree);

    std::string response = apiHandler.handleRequest(recognizeRequestStream.str());

    boost::property_tree::ptree responseTree;
    std::istringstream responseStream(response);
    boost::property_tree::read_json(responseStream, responseTree);

    EXPECT_NE(responseTree.get<std::string>("recognized_text"), "Recognized text");
}

TEST_F(APIHandlerTest, HandleInvalidEndpoint) {
    boost::property_tree::ptree requestTree;
    requestTree.put("endpoint", "/api/invalid");

    std::ostringstream requestStream;
    boost::property_tree::write_json(requestStream, requestTree);

    std::string response = apiHandler.handleRequest(requestStream.str());

    boost::property_tree::ptree responseTree;
    std::istringstream responseStream(response);
    boost::property_tree::read_json(responseStream, responseTree);

    EXPECT_EQ(responseTree.get<std::string>("status"), "error");
    EXPECT_EQ(responseTree.get<std::string>("message"), "Invalid endpoint");
}

TEST_F(APIHandlerTest, HandleEmptyImageUpload) {
    boost::property_tree::ptree requestTree;
    requestTree.put("endpoint", "/api/upload");
    requestTree.put("image_data", "");

    std::ostringstream requestStream;
    boost::property_tree::write_json(requestStream, requestTree);

    std::string response = apiHandler.handleRequest(requestStream.str());

    boost::property_tree::ptree responseTree;
    std::istringstream responseStream(response);
    boost::property_tree::read_json(responseStream, responseTree);

    EXPECT_EQ(responseTree.get<std::string>("status"), "error");
    EXPECT_EQ(responseTree.get<std::string>("message"), "Invalid image data");
}

TEST_F(APIHandlerTest, HandleRecognizeWithoutUpload) {
    boost::property_tree::ptree requestTree;
    requestTree.put("endpoint", "/api/recognize");

    std::ostringstream requestStream;
    boost::property_tree::write_json(requestStream, requestTree);

    std::string response = apiHandler.handleRequest(requestStream.str());

    boost::property_tree::ptree responseTree;
    std::istringstream responseStream(response);
    boost::property_tree::read_json(responseStream, responseTree);

    EXPECT_EQ(responseTree.get<std::string>("status"), "error");
    EXPECT_EQ(responseTree.get<std::string>("message"), "No image uploaded");
}

TEST_F(APIHandlerTest, HandleRecognizeValidImage) {
    // First, upload a valid image
    boost::property_tree::ptree uploadRequestTree;
    uploadRequestTree.put("endpoint", "/api/upload");
    uploadRequestTree.put("image_data", "valid_image_data");

    std::ostringstream uploadRequestStream;
    boost::property_tree::write_json(uploadRequestStream, uploadRequestTree);

    apiHandler.handleRequest(uploadRequestStream.str());

    // Then, recognize the uploaded image
    boost::property_tree::ptree recognizeRequestTree;
    recognizeRequestTree.put("endpoint", "/api/recognize");

    std::ostringstream recognizeRequestStream;
    boost::property_tree::write_json(recognizeRequestStream, recognizeRequestTree);

    std::string response = apiHandler.handleRequest(recognizeRequestStream.str());

    boost::property_tree::ptree responseTree;
    std::istringstream responseStream(response);
    boost::property_tree::read_json(responseStream, responseTree);

    EXPECT_NE(responseTree.get<std::string>("recognized_text"), "");
}

TEST_F(APIHandlerTest, RateLimitExceeded) {
    boost::property_tree::ptree requestTree;
    requestTree.put("endpoint", "/api/upload");
    requestTree.put("image_data", "dummy_image_data");
    requestTree.put("api_key", "test_api_key");

    std::ostringstream requestStream;
    boost::property_tree::write_json(requestStream, requestTree);

    for (int i = 0; i < 101; ++i) {
        apiHandler.handleRequest(requestStream.str());
    }

    std::string response = apiHandler.handleRequest(requestStream.str());

    boost::property_tree::ptree responseTree;
    std::istringstream responseStream(response);
    boost::property_tree::read_json(responseStream, responseTree);

    EXPECT_EQ(responseTree.get<std::string>("status"), "error");
    EXPECT_EQ(responseTree.get<std::string>("message"), "Rate limit exceeded");
}

TEST_F(APIHandlerTest, RateLimitNotExceeded) {
    boost::property_tree::ptree requestTree;
    requestTree.put("endpoint", "/api/upload");
    requestTree.put("image_data", "dummy_image_data");
    requestTree.put("api_key", "test_api_key");

    std::ostringstream requestStream;
    boost::property_tree::write_json(requestStream, requestTree);

    for (int i = 0; i < 100; ++i) {
        apiHandler.handleRequest(requestStream.str());
    }

    std::string response = apiHandler.handleRequest(requestStream.str());

    boost::property_tree::ptree responseTree;
    std::istringstream responseStream(response);
    boost::property_tree::read_json(responseStream, responseTree);

    EXPECT_EQ(responseTree.get<std::string>("status"), "success");
    EXPECT_EQ(responseTree.get<std::string>("message"), "Image uploaded successfully");
}
