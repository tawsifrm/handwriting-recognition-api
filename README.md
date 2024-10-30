# Handwriting Recognition API

## Description

This project is a RESTful API that accepts handwritten text images and returns the recognized text. It provides endpoints for uploading images, processing them, and returning the recognized text in various formats (e.g., JSON, plain text). The API includes authentication and rate limiting to ensure secure and efficient usage.

## Setup and Running Instructions

### Prerequisites

- C++ compiler (e.g., GCC, Clang)
- CMake
- OpenCV library
- Boost library

### Building the Project

1. Clone the repository:
   ```sh
   git clone https://github.com/githubnext/workspace-blank.git
   cd workspace-blank
   ```

2. Create a build directory and navigate to it:
   ```sh
   mkdir build
   cd build
   ```

3. Run CMake to configure the project:
   ```sh
   cmake ..
   ```

4. Build the project:
   ```sh
   make
   ```

### Running the Server

1. Navigate to the build directory (if not already there):
   ```sh
   cd build
   ```

2. Run the server:
   ```sh
   ./handwriting_recognition_api
   ```

## API Documentation

### Authentication

The API uses token-based authentication. To access the endpoints, include the following header in your requests:
```
Authorization: Bearer <your_token>
```

### Endpoints

#### Upload Image

- **URL:** `/api/upload`
- **Method:** `POST`
- **Headers:**
  - `Authorization: Bearer <your_token>`
  - `Content-Type: multipart/form-data`
- **Body:**
  - `image`: The handwritten text image file to be uploaded.
- **Response:**
  - `200 OK`: The image was successfully uploaded and processed.
  - `400 Bad Request`: The request was invalid or the image could not be processed.
  - `401 Unauthorized`: Authentication failed.

#### Get Recognized Text

- **URL:** `/api/recognize`
- **Method:** `GET`
- **Headers:**
  - `Authorization: Bearer <your_token>`
- **Response:**
  - `200 OK`: The recognized text in the requested format.
  - `400 Bad Request`: The request was invalid.
  - `401 Unauthorized`: Authentication failed.

### Rate Limiting

The API implements rate limiting using a token bucket algorithm to ensure fair usage and prevent abuse. Each API key is allocated a certain number of tokens, which are replenished at a fixed rate. When a request is made, a token is consumed. If no tokens are available, the request is rate limited and an error response is returned.

#### Rate Limit Exceeded Response

- **Response:**
  - `429 Too Many Requests`: The rate limit has been exceeded. The response will include a message indicating that the rate limit has been exceeded.

## Usage Examples

### Uploading an Image

To upload an image, use the following `curl` command:

```sh
curl -X POST http://localhost:8080/api/upload \
  -H "Authorization: Bearer <your_token>" \
  -F "image=@path_to_your_image_file"
```

### Recognizing Text

To recognize text from the uploaded image, use the following `curl` command:

```sh
curl -X GET http://localhost:8080/api/recognize \
  -H "Authorization: Bearer <your_token>"
```

## Troubleshooting

### Common Issues

1. **Invalid API Key**: Ensure that you are using a valid API key in the `Authorization` header.
2. **Invalid Image Data**: Ensure that the image file is in a supported format and not corrupted.
3. **Server Not Running**: Ensure that the server is running and accessible at the specified URL and port.

### Debugging Tips

- Check the server logs for any error messages or stack traces.
- Use tools like `curl` or Postman to test the API endpoints and verify the responses.
- Ensure that all dependencies (e.g., OpenCV, Boost) are correctly installed and configured.

## Contributing

We welcome contributions to improve the Handwriting Recognition API. To contribute, please follow these guidelines:

1. Fork the repository and create a new branch for your feature or bugfix.
2. Write clear and concise commit messages.
3. Ensure that your code follows the project's coding standards and passes all tests.
4. Submit a pull request with a detailed description of your changes.

## Code of Conduct

We are committed to fostering a welcoming and inclusive community. Please read and follow our [Code of Conduct](CODE_OF_CONDUCT.md) to ensure a positive experience for all contributors and users.
