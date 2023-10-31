#include "ImageMatrix.h"
#include <iostream>


// Default constructor
ImageMatrix::ImageMatrix(){
    
}


// Parameterized constructor for creating a blank image of given size
ImageMatrix::ImageMatrix(int imgHeight, int imgWidth) : height(imgHeight), width(imgWidth) {

}

// Parameterized constructor for loading image from file. PROVIDED FOR YOUR CONVENIENCE
ImageMatrix::ImageMatrix(const std::string &filepath) {
    // Create an ImageLoader object and load the image
    ImageLoader imageLoader(filepath);

    // Get the dimensions of the loaded image
    height = imageLoader.getHeight();
    width = imageLoader.getWidth();

    // Allocate memory for the matrix
    data = new double*[height];
    for (int i = 0; i < height; ++i) {
        data[i] = new double[width];
    }

    // Copy data from imageLoader to data
    double** imageData = imageLoader.getImageData();
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; j++) {
            data[i][j] = imageData[i][j];
        }
    }
}



// Destructor
ImageMatrix::~ImageMatrix() {
}

// Parameterized constructor - direct initialization with 2D matrix
ImageMatrix::ImageMatrix(const double** inputMatrix, int imgHeight, int imgWidth){
    // Get the dimensions of the input image
    height = imgHeight;
    width = imgWidth;

    // Allocate memory for the matrix
    data = new double*[imgHeight];
    for (int i = 0; i < imgHeight; ++i) {
        data[i] = new double[imgWidth];
    }

    // Copy data from inputMatrix to data
    for (int i = 0; i < imgHeight; ++i) {
        for (int j = 0; j < imgWidth; j++) {
            data[i][j] = inputMatrix[i][j];
        }}
}

// Copy constructor
ImageMatrix::ImageMatrix(const ImageMatrix &other) {
    
}

// Copy assignment operator
ImageMatrix& ImageMatrix::operator=(const ImageMatrix &other) {
    
}



// Overloaded operators

// Overloaded operator + to add two matrices
ImageMatrix ImageMatrix::operator+(const ImageMatrix &other) const {
    
}

// Overloaded operator - to subtract two matrices
ImageMatrix ImageMatrix::operator-(const ImageMatrix &other) const {

}

// Overloaded operator * to multiply a matrix with a scalar
ImageMatrix ImageMatrix::operator*(const double &scalar) const {

}


// Getter function to access the data in the matrix
double** ImageMatrix::get_data() const {

}

// Getter function to access the data at the index (i, j)
double ImageMatrix::get_data(int i, int j) const {
    return data[i][j];
}

// Getter function to access the height of the matrix
int ImageMatrix::get_height() const {
    return height;
}

// Getter function to access the width of the matrix
int ImageMatrix::get_width() const {
    return width;
}

