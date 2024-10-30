#include "authentication.h"
#include <gtest/gtest.h>

class AuthenticationTest : public ::testing::Test {
protected:
    Authentication auth;

    virtual void SetUp() {
        // Code here will be called immediately after the constructor (right before each test).
    }

    virtual void TearDown() {
        // Code here will be called immediately after each test (right before the destructor).
    }
};

TEST_F(AuthenticationTest, GenerateApiKey) {
    std::string apiKey = auth.generateApiKey();
    EXPECT_EQ(apiKey.length(), 32);
}

TEST_F(AuthenticationTest, ValidateApiKey) {
    std::string apiKey = auth.generateApiKey();
    EXPECT_TRUE(auth.validateApiKey(apiKey));
    EXPECT_FALSE(auth.validateApiKey("invalid_api_key"));
}

TEST_F(AuthenticationTest, GenerateMultipleApiKeys) {
    std::string apiKey1 = auth.generateApiKey();
    std::string apiKey2 = auth.generateApiKey();
    EXPECT_NE(apiKey1, apiKey2);
}

TEST_F(AuthenticationTest, ValidateMultipleApiKeys) {
    std::string apiKey1 = auth.generateApiKey();
    std::string apiKey2 = auth.generateApiKey();
    EXPECT_TRUE(auth.validateApiKey(apiKey1));
    EXPECT_TRUE(auth.validateApiKey(apiKey2));
    EXPECT_FALSE(auth.validateApiKey("invalid_api_key"));
}

TEST_F(AuthenticationTest, ValidateEmptyApiKey) {
    EXPECT_FALSE(auth.validateApiKey(""));
}

TEST_F(AuthenticationTest, ValidateNullApiKey) {
    std::string nullApiKey;
    EXPECT_FALSE(auth.validateApiKey(nullApiKey));
}
