#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include "api_handler.h"

using namespace boost::asio;
using ip::tcp;

// Main function to start the server and handle incoming requests
int main() {
    try {
        io_service io_service;
        tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 8080));

        std::cout << "Server started on port 8080" << std::endl;

        for (;;) {
            tcp::socket socket(io_service);
            acceptor.accept(socket);

            std::string message;
            boost::system::error_code error;
            read_until(socket, boost::asio::dynamic_buffer(message), "\n", error);

            if (!error) {
                APIHandler apiHandler;
                std::string apiKey = "your_api_key"; // Replace with actual API key extraction logic
                if (apiHandler.isRateLimited(apiKey)) {
                    std::string response = apiHandler.generateErrorResponse("Rate limit exceeded");
                    write(socket, buffer(response), error);
                } else {
                    std::string response = apiHandler.handleRequest(message);
                    write(socket, buffer(response), error);
                }
            } else {
                std::cerr << "Error reading request: " << error.message() << std::endl;
            }
        }
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
