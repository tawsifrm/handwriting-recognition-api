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

    EXPECT_EQ(responseTree.get<std::string>("recognized_text"), "Recognized text");
}
