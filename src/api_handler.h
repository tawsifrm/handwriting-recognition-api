#ifndef API_HANDLER_H
#define API_HANDLER_H

#include <string>

class APIHandler {
public:
    APIHandler();
    ~APIHandler();

    std::string handleRequest(const std::string& request);
};

#endif // API_HANDLER_H
