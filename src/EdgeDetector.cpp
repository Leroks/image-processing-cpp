// EdgeDetector.cpp

#include "EdgeDetector.h"
#include <cmath>

#include "EdgeDetector.h"
#include <cmath>

// Default constructor
EdgeDetector::EdgeDetector() {

}

// Destructor
EdgeDetector::~EdgeDetector() {

}

// Detect Edges using the given algorithm
std::vector<std::pair<int, int>> EdgeDetector::detectEdges(const ImageMatrix& input_image) {
    // Initialize the Sobel operators
    double** Gx = new double*[3];
    double** Gy = new double*[3];
    for (int i = 0; i < 3; i++) {
        Gx[i] = new double[3];
        Gy[i] = new double[3];
    }
    Gx[0][0] = -1; Gx[0][1] = 0; Gx[0][2] = 1;
    Gx[1][0] = -2; Gx[1][1] = 0; Gx[1][2] = 2;
    Gx[2][0] = -1; Gx[2][1] = 0; Gx[2][2] = 1;
    Gy[0][0] = -1; Gy[0][1] = -2; Gy[0][2] = -1;
    Gy[1][0] = 0; Gy[1][1] = 0; Gy[1][2] = 0;
    Gy[2][0] = 1; Gy[2][1] = 2; Gy[2][2] = 1;

    // Create Convolution objects for the Sobel operators
    Convolution convGx(Gx, 3, 3, 1, true);
    Convolution convGy(Gy, 3, 3, 1, true);

    // Convolve the input image with the Sobel operators
    ImageMatrix Ix = convGx.convolve(input_image);
    ImageMatrix Iy = convGy.convolve(input_image);

    // Calculate the magnitude of the gradient at each pixel
    ImageMatrix magnitude(input_image.get_height(), input_image.get_width());
    for (int i = 0; i < input_image.get_height(); i++) {
        for (int j = 0; j < input_image.get_width(); j++) {
            magnitude.set_data(i, j, std::sqrt(Ix.get_data(i, j) * Ix.get_data(i, j) + Iy.get_data(i, j) * Iy.get_data(i, j)));
        }
    }

    // Find the threshold value
    double threshold = 0;
    for (int i = 0; i < input_image.get_height(); i++) {
        for (int j = 0; j < input_image.get_width(); j++) {
            threshold += magnitude.get_data(i, j);
        }
    }
    threshold /= (input_image.get_height() * input_image.get_width());

    // Append all pixels with a gradient above the threshold to the list of edge pixels
    std::vector<std::pair<int, int>> edgePixels;
    for (int i = 0; i < input_image.get_height(); i++) {
        for (int j = 0; j < input_image.get_width(); j++) {
            if (magnitude.get_data(i, j) > threshold) {
                edgePixels.push_back(std::make_pair(i, j));
            }
        }
    }

    return edgePixels;

}

