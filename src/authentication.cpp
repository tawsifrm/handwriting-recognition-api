#include "authentication.h"
#include <random>
#include <iostream>

// Authentication class handles API key generation and validation.
Authentication::Authentication() {
    // Constructor implementation
}

Authentication::~Authentication() {
    // Destructor implementation
}

// Generates a random API key and stores it in the apiKeys map.
std::string Authentication::generateApiKey() {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    int len = 32;
    std::string apiKey;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, sizeof(alphanum) - 2);

    for (int i = 0; i < len; ++i) {
        apiKey += alphanum[dis(gen)];
    }

    apiKeys[apiKey] = true;
    return apiKey;
}

// Validates the given API key by checking if it exists in the apiKeys map.
bool Authentication::validateApiKey(const std::string& apiKey) {
    if (apiKeys.find(apiKey) == apiKeys.end()) {
        std::cerr << "Invalid API key: " << apiKey << std::endl;
        return false;
    }
    return true;
}
