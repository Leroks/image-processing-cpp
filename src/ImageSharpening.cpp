#include "ImageSharpening.h"

// Default constructor
ImageSharpening::ImageSharpening() {

}

ImageSharpening::~ImageSharpening(){
}

ImageMatrix ImageSharpening::sharpen(const ImageMatrix& input_image, double k) {
    // Define the blurring kernel
    double** kernel = new double*[3];
    for (int i = 0; i < 3; i++) {
        kernel[i] = new double[3];
        for (int j = 0; j < 3; j++) {
            kernel[i][j] = 1.0 / 9.0;
        }
    }

    // Create a Convolution object with the blurring kernel
    Convolution blurConv(kernel, 3, 3, 1, true);

    // Convolve the input image with the blurring kernel
    ImageMatrix blurredImage = blurConv.convolve(input_image);

    // Subtract the blurred image from the original image
    ImageMatrix diffImage = input_image - blurredImage;

    // Multiply the difference image by the sharpening factor
    diffImage = diffImage * k;

    // Add the result to the original image to get the sharpened image
    ImageMatrix sharpenedImage = input_image + diffImage;

    return sharpenedImage;

}
