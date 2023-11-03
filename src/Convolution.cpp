#include <iostream>

#include "Convolution.h"

// Default constructor 
Convolution::Convolution()
        : customKernel(nullptr), kernelHeight(0), kernelWidth(0), stride(1), padding(false) {}

// Parametrized constructor for custom kernel and other parameters
Convolution::Convolution(double** customKernel, int kernelHeight, int kernelWidth, int stride, bool padding)
        : customKernel(customKernel), kernelHeight(kernelHeight), kernelWidth(kernelWidth), stride(stride), padding(padding) {}


// Destructor
Convolution::~Convolution() {
/*    // Deallocate memory
    if (customKernel != nullptr) {
        for (int i = 0; i < kernelHeight; ++i) {
            delete[] customKernel[i];
        }
        delete[] customKernel;
    }*/
}

// Copy constructor
Convolution::Convolution(const Convolution &other){
    // Check if customKernel has been allocated
    if (other.customKernel != nullptr) {
        // Allocate memory for the customKernel in the new object
        kernelHeight = other.kernelHeight;
        kernelWidth = other.kernelWidth;
        customKernel = new double*[kernelHeight];
        for (int i = 0; i < kernelHeight; i++) {
            customKernel[i] = new double[kernelWidth];
            for (int j = 0; j < kernelWidth; j++) {
                customKernel[i][j] = other.customKernel[i][j];
            }
        }

        // Copy other properties
        stride = other.stride;
        padding = other.padding;
    }
}


// Copy assignment operator
Convolution& Convolution::operator=(const Convolution &other) {
    if (this == &other) {
        return *this;
    }

    // Check if customKernel has been allocated
    if (customKernel != nullptr) {
        // Deallocate old memory
        for (int i = 0; i < kernelHeight; ++i) {
            delete[] customKernel[i];
        }
        delete[] customKernel;

    }

    // Copy from other
    if (other.customKernel != nullptr) {
        kernelHeight = other.kernelHeight;
        kernelWidth = other.kernelWidth;
        stride = other.stride;
        padding = other.padding;

        // Allocate new memory and perform a deep copy
        customKernel = new double*[kernelHeight];
        for (int i = 0; i < kernelHeight; i++) {
            customKernel[i] = new double[kernelWidth];
            for (int j = 0; j < kernelWidth; j++) {
                customKernel[i][j] = other.customKernel[i][j];
            }
        }
    }

    return *this;
}



// Convolve Function: Responsible for convolving the input image with a kernel and return the convolved image.
ImageMatrix Convolution::convolve(const ImageMatrix& input_image) const {
    int inputHeight = input_image.get_height();
    int inputWidth = input_image.get_width();

    // Calculate the dimensions of the output image
    int outputHeight = (inputHeight - kernelHeight + (padding ? 2 : 0)) / stride + 1;
    int outputWidth = (inputWidth - kernelWidth + (padding ? 2 : 0)) / stride + 1;

    // Create an empty output image
    ImageMatrix outputImage(outputHeight, outputWidth);

    if(padding){
        // Create a new image with padding
        ImageMatrix paddedImage(inputHeight + 2, inputWidth + 2);
        for(int i = 0; i < inputHeight; i++){
            for(int j = 0; j < inputWidth; j++){
                paddedImage.set_data(i + 1, j + 1, input_image.get_data(i, j));
            }
        }
        // Pad the top and bottom rows
        for(int j = 0; j < inputWidth; j++){
            paddedImage.set_data(0, j + 1, 0);
            paddedImage.set_data(inputHeight + 1, j + 1, 0);
        }
        // Pad the left and right columns
        for(int i = 0; i < inputHeight + 2; i++){
            paddedImage.set_data(i, 0, 0);
            paddedImage.set_data(i, inputWidth + 1, 0);
        }

        // Convolve the padded image
        int x,y;
        for(int i = 0; i < outputHeight; i++){
            for(int j = 0; j < outputWidth; j++){
                x=i*stride;
                y=j*stride;
                double sum = 0;
                for(int k = 0; k < kernelHeight; k++){
                    for(int l = 0; l < kernelWidth; l++){
                        sum += paddedImage.get_data(x, y) * customKernel[k][l];
                        y++;
                    }
                    x++;
                    y=j*stride;
                }
                outputImage.set_data(i, j, sum);
            }
        }
    }
    else{
        // Convolve the no pad image
        int x,y;
        for(int i = 0; i < outputHeight; i++){
            for(int j = 0; j < outputWidth; j++){
                x=i*stride;
                y=j*stride;
                double sum = 0;
                for(int k = 0; k < kernelHeight; k++){
                    for(int l = 0; l < kernelWidth; l++){
                        sum += input_image.get_data(x, y) * customKernel[k][l];
                        y++;
                    }
                    x++;
                    y=j*stride;
                }
                outputImage.set_data(i, j, sum);
                sum=0;
            }
        }
    }

    return outputImage;

}
