#include "ImageMatrix.h"
#include <iostream>


// Default constructor
ImageMatrix::ImageMatrix(){
    // Initialize all the values to 0
    height = 0;
    width = 0;
    data = nullptr;
    
}


// Parameterized constructor for creating a blank image of given size
ImageMatrix::ImageMatrix(int imgHeight, int imgWidth) : height(imgHeight), width(imgWidth) {
    // Allocate memory for the matrix
    data = new double*[imgHeight];
    for (int i = 0; i < imgHeight; ++i) {
        data[i] = new double[imgWidth];
    }

    // Initialize all the values to 0
    for (int i = 0; i < imgHeight; ++i) {
        for (int j = 0; j < imgWidth; j++) {
            data[i][j] = 0;
        }
    }

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
    for (int i = 0; i < height; ++i) {
        delete[] data[i];
    }
    delete[] data;
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
    // Get the dimensions of the input image
    height = other.height;
    width = other.width;

    // Allocate memory for the matrix - deep copy
    data = new double*[height];
    for (int i = 0; i < height; ++i) {
        data[i] = new double[width];
    }

    // Copy data from other to data
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; j++) {
            data[i][j] = other.data[i][j];
        }
    }
}

// Copy assignment operator
ImageMatrix& ImageMatrix::operator=(const ImageMatrix &other) {
    if (this == &other) {
        return *this;
    }

    // Deallocate old memory
    if (data != nullptr) {
        for (int i = 0; i < height; ++i) {
            delete[] data[i];
        }
        delete[] data;
    }

    // Deep copy
    height = other.height;
    width = other.width;
    data = new double*[height];
    for (int i = 0; i < height; ++i) {
        data[i] = new double[width];
        for (int j = 0; j < width; j++) {
            data[i][j] = other.data[i][j];
        }
    }

    return *this;
    
}



// Overloaded operators

// Overloaded operator + to add two matrices
ImageMatrix ImageMatrix::operator+(const ImageMatrix &other) const {
    if (height != other.height || width != other.width) {
        std::cout << "Error"<< std::endl;
        exit(1);
    }

    // Create a new matrix for the result
    ImageMatrix result(height, width);

    // Add the two matrices
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; j++) {
            result.data[i][j] = data[i][j] + other.data[i][j];
        }
    }

    return result;
}

// Overloaded operator - to subtract two matrices
ImageMatrix ImageMatrix::operator-(const ImageMatrix &other) const {
    if (height != other.height || width != other.width) {
        std::cout << "Error" << std::endl;
        exit(1);
    }

    // Create a new matrix for the result
    ImageMatrix result(height, width);

    // Subtract the two matrices
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; j++) {
            result.data[i][j] = data[i][j] - other.data[i][j];
        }
    }

    return result;
}

// Overloaded operator * to multiply a matrix with a scalar
ImageMatrix ImageMatrix::operator*(const double &scalar) const {
    // Create a new matrix to store the result
    ImageMatrix result(height, width);

    // Multiply the matrix with the scalar
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; j++) {
            result.data[i][j] = data[i][j] * scalar;
        }
    }

    return result;
}


// Getter function to access the data in the matrix
double** ImageMatrix::get_data() const {
    return data;
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

void ImageMatrix::set_data(int i, int j, double d) {
    data[i][j] = d;
}

