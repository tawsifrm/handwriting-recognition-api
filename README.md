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
