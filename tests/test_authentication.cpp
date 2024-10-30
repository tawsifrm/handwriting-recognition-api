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
