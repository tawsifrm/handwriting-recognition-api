#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include <string>
#include <unordered_map>

// The Authentication class handles API key generation and validation.
class Authentication {
public:
    Authentication();
    ~Authentication();

    // Generates a random API key and stores it in the apiKeys map.
    std::string generateApiKey();

    // Validates the given API key by checking if it exists in the apiKeys map.
    bool validateApiKey(const std::string& apiKey);

private:
    // Stores the generated API keys.
    std::unordered_map<std::string, bool> apiKeys;
};

#endif // AUTHENTICATION_H
