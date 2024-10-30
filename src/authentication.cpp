#include "authentication.h"
#include <random>

Authentication::Authentication() {
    // Constructor implementation
}

Authentication::~Authentication() {
    // Destructor implementation
}

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

bool Authentication::validateApiKey(const std::string& apiKey) {
    return apiKeys.find(apiKey) != apiKeys.end();
}
