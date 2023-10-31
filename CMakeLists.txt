cmake_minimum_required(VERSION 3.26)
project(pa1)

set(CMAKE_CXX_STANDARD 11)

add_executable(pa1
        src/main.cpp
        src/Convolution.cpp
        src/DecodeMessage.cpp
        src/EdgeDetector.cpp
        src/EncodeMessage.cpp
        src/ImageLoader.cpp
        src/ImageMatrix.cpp
        src/ImageProcessor.cpp
        src/ImageSharpening.cpp)
