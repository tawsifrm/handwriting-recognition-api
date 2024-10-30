#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include <string>
#include <unordered_map>

class Authentication {
public:
    Authentication();
    ~Authentication();

    std::string generateApiKey();
    bool validateApiKey(const std::string& apiKey);

private:
    std::unordered_map<std::string, bool> apiKeys;
};

#endif // AUTHENTICATION_H
