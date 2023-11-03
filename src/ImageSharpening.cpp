#include "ImageSharpening.h"

// Default constructor
ImageSharpening::ImageSharpening() {

}

ImageSharpening::~ImageSharpening(){
}

ImageMatrix ImageSharpening::sharpen(const ImageMatrix& input_image, double k) {
    // Define and allocate the blurring kernel
    double** kernel = new double*[3];
    for (int i = 0; i < 3; i++) {
        kernel[i] = new double[3];
        for (int j = 0; j < 3; j++) {
            kernel[i][j] = 1.0 / 9.0;
        }
    }

    //Create object with blurring kernel
    Convolution blurConv(kernel, 3, 3, 1, true);

    // Convolve input image with blurring kernel
    ImageMatrix blurredImage = blurConv.convolve(input_image);

    // Subtract blurred image from original image
    ImageMatrix diffImage = input_image - blurredImage;

    // Multiply diff image with sharpening factor
    diffImage = diffImage * k;

    // Add result to original image to get sharpened image
    ImageMatrix sharpenedImage = input_image + diffImage;

    return sharpenedImage;
}
